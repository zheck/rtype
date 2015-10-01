//
//  Player.cpp
//  xCodeClient
//
//  Created by Zhou Fong on 11/15/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "Player.hpp"
#include "KeyManager.hpp"
#include "SoundManager.hpp"

Player::Player() :
Entity(Vect2(0, 0), PLAYER)
{
    _lastFired = 0;
    _lastMoved = 0;
    posx = 100;
    posy = 100;
    _lastFired = 0;
    _weaponCooldown = 0.3;
}

Player::~Player()
{}

void Player::init()
{
    posx = 100;
    posy = 100;
    _lastFired = 0;
    lastUpdate = 0;
    setAlive(true);
}

void Player::update(ClockManager const & clock, Message & msg)
{
    
    msg.messageType = MSG_GAME;
    msg.entity = PLAYER;
    if (KeyManager::getInstance().isKeyPressed(Keyboard::Up)) {
        if (posy > 10) {
            posy -= 3;
        }
    }
    if (KeyManager::getInstance().isKeyPressed(Keyboard::Down)) {
        if (posy < WINY - 50) { // ship.height
            posy += 3;
        }
    }
    if (KeyManager::getInstance().isKeyPressed(Keyboard::Left)) {
        if (posx > 10) {
            posx -= 3;
        }
    }
    if (KeyManager::getInstance().isKeyPressed(Keyboard::Right)) {
        if (posx < WINX - 50) { // ship.width
            posx += 3;
        }
    }
    if (KeyManager::getInstance().isKeyPressed(Keyboard::Space)) {
        if (clock.getElapsedTime() - _lastFired > _weaponCooldown) {
            _lastFired = clock.getElapsedTime();
            msg.entity = BULLET;
            SoundManager::getInstance().playFire();
        }
    }
    msg.posX = posx;
    msg.posY = posy;
}
