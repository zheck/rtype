//
//  Player.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include <cstdlib>

#include "Player.hpp"
#include "Room.hpp"

Player::Player(int playerId, std::string const & ip, std::string const & p) :
Entity(Vect2(0, 0), PLAYER, Vect2(33, 33)),
_playerId(playerId),
_playerIp(ip)
{
    _udpSocket = new SocketUdp();
    _udpSocket->init(p);
    port = atoi(p.c_str());
}

Player::~Player()
{
    delete _udpSocket;
}

void Player::update(int gameTime)
{
    (void)gameTime;
}

void Player::attack(Entity *e, int gameTime)
{
    if (_weapon.setBulletType(e->getType()) == false) {
        takeDamage(gameTime);
        e->takeDamage(gameTime);
    }
    else {
        e->setAlive(false);
        e->setDeathTime(gameTime);
    }
}

void Player::takeDamage(int gameTime)
{
    setAlive(false);
    setDeathTime(gameTime);
}

void Player::sendMsg(const Message &msg)
{
    _udpSocket->sendMsg(msg);
}

void Player::recvMsg(Message &msg)
{
    _udpSocket->recvMsg(msg, _playerIp);
    if (msg.messageType != MSG_IDDLE && msg.id == _playerId && msg.time > _lastUpdated) {
        if (isAlive()) {
            _weapon.fire(msg.entity, getPosition(), Vect2(5, 0));
        }
        _lastUpdated = msg.time;
        setPosition(msg.posX, msg.posY);
    }
}

int Player::getPlayerId() const
{
    return _playerId;
}

std::string Player::getPlayerIp()
{
    return _playerIp;
}

void Player::setPlayerId(int id)
{
    _playerId = id;
}

void Player::reinit(Game * g)
{
    _weapon.setDelegate(g);
    setPosition(100, 100);
    _lastUpdated = 0;
    _weapon.reinit();
    setAlive(true);
}
