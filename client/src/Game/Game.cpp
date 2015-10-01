//
//  Game.cpp
//  xCodeClient
//
//  Created by mo_r on 26/10/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "Game.hpp"
#include "ResourcePath.hpp"
#include "KeyManager.hpp"
#include "SoundManager.hpp"

Game::Game()
{}

Game::~Game()
{
    release();
}

void Game::release()
{
    _entities.erase(_playerId);
    for (std::map<int, Entity *>::iterator it = _entities.begin(); it != _entities.end(); ++it) {
        delete it->second;
    }
    _entities.clear();
}

void Game::init(int id)
{
    _p.init();
    release();
    _playerId = id;
    _entities[id] = &_p;
}

void Game::update(const sf::Event &event, ClockManager const & clock, Message & msg)
{
    (void)event;
    msg.posX = -100;
    msg.posY = -100;
    if (_p.isAlive()) {
        _p.update(clock, msg);
    }
    msg.id = _playerId;
    msg.posX = _p.posx;
    msg.posY = _p.posy;
    msg.messageType = MSG_GAME;
}

void Game::updateMap(const Message &msg)
{
    if (msg.isAlive == false) {
        handleDeath(msg);
    }
    else if (_entities.find(msg.id) != _entities.end()) {
        Entity * e = _entities[msg.id];
        if (msg.time > e->lastUpdate) {
            e->lastUpdate = msg.time;
            e->position.x = msg.posX;
            e->position.y = msg.posY;
        }
    }
    else {
        Entity * e = new Entity(Vect2(msg.posX, msg.posY), msg.entity);
        _entities[msg.id] = e;
        e->id = msg.id;
    }
}

void Game::handleDeath(const Message &msg)
{
    if (_entities.find(msg.id) != _entities.end()) {
        Entity * e = _entities[msg.id];
        if (e->isAlive() == false) {
            if (msg.time - e->lastUpdate > e->deathTime) {
                e->position.x = msg.posX;
                e->position.y = msg.posY;
                e->deathTime = msg.time - e->lastUpdate;
                if (e->deathTime > 1000 && msg.id != _playerId) {
                    delete e;
                    _entities.erase(msg.id);
                }
            }
        }
        else {
            if (e->id == 0) {
                return ;
            }
            e->position.x = msg.posX;
            e->position.y = msg.posY;
            e->setAlive(false);
            e->lastUpdate = msg.time;
            e->deathTime = 0;
            if ((msg.entity == MINION || msg.entity == MINION2 || msg.entity == BOSS) && msg.posX > 0) {
                SoundManager::getInstance().playExplosion();
                if (msg.entity == BOSS)
                    SoundManager::getInstance().playVictory();
            }
            else if (msg.entity == PLAYER) {
                SoundManager::getInstance().playExplosion();
                SoundManager::getInstance().playEndGame(true);
            }
        }
    }
}

std::map<int, Entity *> & Game::getEntities()
{
    return _entities;
}
