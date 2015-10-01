//
//  Game.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 10/13/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "Game.hpp"
#include "GameTime.hpp"
#include "QuadTree.hpp"

Game::Game(std::string const & gameName) :
_gameName(gameName)
{}

Game::~Game()
{
    release();
}

void Game::init(std::list<Player *> & playerList)
{
    std::cout << "Initialiazing game" << std::endl;
    int pos = 100;
    _playerList.clear();
    _missiles.clear();
    _ennemies.clear();
    _entities.clear();
    for (std::list<Player *>::iterator it = playerList.begin(); it != playerList.end(); ++it) {
        (*it)->reinit(this);
        (*it)->setPosition(100, pos);
        (*it)->setId((*it)->getPlayerId());
        (*it)->setAlive(true);
        _playerList.push_back(*it);
        std::cout << "player with id: " << (*it)->getPlayerId() <<std::endl;
        pos += 100;
        if (_entities.find(_unitId) != _entities.end()) {
            std::cerr << "conflit on players" << std::endl;
        }
        _entities[(*it)->getPlayerId()] = *it;
    }
    _unitId = 100;
    _gameState = GAME_PLAYING;
    _gameTime = 0;
    _numberOfBossAlive = 1;

}

void Game::release()
{
    std::cout << "Releasing game: " << std::endl;
    for (std::list<Entity *>::iterator it = _ennemies.begin(); it != _ennemies.end(); ++it) {
        delete *it;
    }
    for (std::list<Entity *>::iterator it = _missiles.begin(); it != _missiles.end(); ++it) {
        delete *it;
    }
    for (std::list<Player *>::iterator it = _playerList.begin(); it != _playerList.end(); ++it) {
        (*it)->currentRoom = NULL;
        (*it)->reinit(NULL);
    }
    _playerList.clear();
    _missiles.clear();
    _ennemies.clear();
    _entities.clear();
}

void Game::setDelegate(Room * room)
{
    _delegate = room;
}

void Game::start()
{
    GameTime t;
    t.reset();
    _gameTime = t.getElapsedTime();
    _map.init();
    _map.setDelegate(this);
    _numberOfPlayerAlive = _playerList.size();
    Message msg;
    while (stillPlaying()) {
        while (t.getElapsedTime() - _gameTime < TIME_UNIT) {
            getPlayerActions(msg);
        }
        _gameTime = t.getElapsedTime();
        addSpawn();
        updateMap();
        sendMap(msg);
    }
    
    _gameEnd = _gameTime;
    while (msg.time - _gameTime < 100) {
        msg.messageType = (_gameState == GAME_WON) ? MSG_WON : MSG_LOST;
        msg.time = t.getElapsedTime();
        sendAll(msg);
        getPlayerActions(msg);
    }
    while (msg.time - _gameTime < 100) {
        for (std::list<Player *>::iterator it = _playerList.begin(); it != _playerList.end(); ++it) {
            (*it)->recvMsg(msg);
        }
    }
    release();
}

void Game::getPlayerActions(Message &msg)
{
    _numberOfPlayerAlive = 0;
    for (std::list<Player *>::iterator it = _playerList.begin(); it != _playerList.end(); ++it) {
        if ((*it)->isAlive()) {
            ++_numberOfPlayerAlive;
        }
        msg.messageType = MSG_IDDLE;
        msg.entity = PLAYER;
        (*it)->recvMsg(msg);
    }
}

Player * Game::getPlayerById(int id)
{
    for (std::list<Player *>::iterator it = _playerList.begin(); it != _playerList.end(); ++it) {
        if ((*it)->getPlayerId() == id) {
            return *it;
        }
    }
    return NULL;
}

void Game::addSpawn()
{
    _map.addSpawn(_gameTime);
}

void Game::updateMap()
{
    updateBullets();
    updateMinions();
    
    QuadTree q(Vect2(0, 0), Vect2(800, 600), _gameTime);
    q.createInfluenceTree(_ennemies);
    
    for (std::list<Player *>::iterator it = _playerList.begin(); it != _playerList.end(); ++it) {
        if ((*it)->isAlive()) {
            q.insert(*it);
        }
    }
    for (std::list<Entity *>::iterator it = _missiles.begin(); it != _missiles.end(); ++it) {
        if ((*it)->isAlive()) {
            q.insert(*it);
        }
    }
}

void Game::updateBullets()
{
    for (std::list<Entity *>::iterator it = _missiles.begin(); it != _missiles.end(); ++it) {
        if ((*it)->isAlive()) {
            (*it)->update(_gameTime);
            if ((*it)->posX() > 810 && (*it)->isAlive() == true) {
                (*it)->setAlive(false);
                (*it)->setDeathTime(_gameTime);
            }
        }
        if ((*it)->isAlive() == false) {
            if (_gameTime - (*it)->getDeathTime() > 1200) { // set to 5000
                delete *it;
                it = _missiles.erase(it);
            }
        }
    }
}

void Game::updateMinions()
{
    for (std::list<Entity *>::iterator it = _ennemies.begin(); it != _ennemies.end(); ++it) {
        if ((*it)->isAlive()) {
            (*it)->update(_gameTime);
            if ((*it)->posX() < -50 && (*it)->isAlive()  == true) {
                (*it)->setAlive(false);
                (*it)->setDeathTime(_gameTime);
            }
        }
        if ((*it)->isAlive() == false) {
            if (_gameTime - (*it)->getDeathTime() > 1200) {
                delete *it;
                it = _ennemies.erase(it);
            }
        }
    }
}

void Game::sendMap(Message &msg)
{
    for (std::list<Player *>::iterator it = _playerList.begin(); it != _playerList.end(); ++it) {
        sendEntity(msg, **it);
    }
    for (std::list<Entity *>::iterator it = _missiles.begin(); it != _missiles.end(); ++it) {
        sendEntity(msg, **it);
    }
    for (std::list<Entity *>::iterator it = _ennemies.begin(); it != _ennemies.end(); ++it) {
        sendEntity(msg, **it);
    }
}

void Game::sendEntity(Message &msg, const Entity &e)
{
    msg.messageType = MSG_GAME;
    msg.entity = e.getType();
    msg.id = e.getId();
    msg.isAlive = e.isAlive();
    msg.posX = e.posX();
    msg.posY = e.posY();
    msg.time = _gameTime;
    sendAll(msg);
}

void Game::sendAll(Message const &msg)
{
    for (std::list<Player *>::iterator it = _playerList.begin(); it != _playerList.end(); ++it) {
        (*it)->sendMsg(msg);
    }
}

bool Game::stillPlaying()
{
    if (_map.getSpawnList().size() <= 0 && _ennemies.size() <= 0) {
        _gameState = GAME_WON;
        return  false;
    }
    else if (_numberOfPlayerAlive <= 0) {
        _gameState = GAME_LOST;
        return false;
    }
    return true;
}

void Game::addMissile(Entity *e)
{
    ++_unitId;
    while (_entities.find(_unitId) != _entities.end()) {
        ++_unitId;
    }
    e->setId(_unitId);
    e->setAlive(true);
    _entities[_unitId] = e;
    _missiles.push_back(e);
}

void Game::addEntity(Entity * e)
{
    ++_unitId;
    while (_entities.find(_unitId) != _entities.end()) {
        ++_unitId;
    }
    e->setId(_unitId);
    e->setAlive(true);
    _entities[_unitId] = e;
    _ennemies.push_back(e);
}