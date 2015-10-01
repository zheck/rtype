//
//  SpaceShip.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "SpaceShip.hpp"
#include "Bullet.hpp"
#include "Bonus.hpp"

SpaceShip::SpaceShip(Vect2 const & position, eType type, Game * delegate) :
Entity(position, type, Vect2(17, 36))
{
    _bonus = MINION;
    _delegate = delegate;
    _direction.x = -2;
    _direction.y = 0;
    _lastFired = 0;
    int dir;
    for (int i = 1; i < 7; ++i) {
        dir = rand() % 3 - 1;
        _behaviours.push_back(std::make_pair(i * 100, dir));
    }
    _cooldown = 4000;
}

SpaceShip::~SpaceShip()
{}

void SpaceShip::update(int gameTime)
{
    if (_behaviours.size() > 0 && posX() < _behaviours.back().first) {
        _direction.y = _behaviours.back().second;
        _behaviours.pop_back();
    }
    else {
        int dir = 0;
        if ((posY() + _direction.y > 150) && (posY() + _direction.y < 500)) {
            dir = _direction.y;
        }
        setPosition(posX() + _direction.x, posY() + dir);
    }
    if (gameTime - _lastFired > _cooldown && posX() > 200) {
        _lastFired = gameTime;
        if (_delegate != NULL) {
            Entity * e = new Bullet(Vect2(posX() - 2, posY()), Vect2(-5, 0));
            _delegate->addEntity(e);
        }
    }
}

void SpaceShip::attack(Entity *e, int gameTime)
{
    takeDamage(gameTime);
    e->takeDamage(gameTime);
}

void SpaceShip::takeDamage(int gameTime)
{
    if (isAlive() == true) {
        setAlive(false);
        setDeathTime(gameTime);
        if (_bonus != MINION && _delegate != NULL) {
            Entity * e = new Bonus(_bonus, getPosition(), Vect2(0, 0));
            _delegate->addEntity(e);
        }
    }
}

void SpaceShip::setBonus(eType bonusType)
{
    _bonus = bonusType;
}