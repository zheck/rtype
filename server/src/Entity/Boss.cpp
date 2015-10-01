//
//  Boss.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/19/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "defines.hpp"
#include "Boss.hpp"
#include "Bullet.hpp"
#include "Bonus.hpp"

Boss::Boss(Vect2 const & position, Game * delegate) :
Entity(position, BOSS, Vect2(50, 56))
{
    _delegate = delegate;
    _life = BOSS_LIFE;
    _cooldown = 1000;
    _lastFired = 0;
    _lifeTime = 0;
    
    _movedTime = 0;
    _direction.x = 0;
    _direction.y = 0;
    int dir;
    for (int i = 1; i < 100; ++i) {
        dir = rand() % 3 - 1;
        _behaviours.push_back(dir);
    }
}

Boss::~Boss()
{}

void Boss::update(int gameTime)
{
    if (_behaviours.size() > 0 && _movedTime >= 100) {
        _direction.y = _behaviours.back();
        _behaviours.pop_back();
        _movedTime = 0;
    }
    else {
        int dir = 0;
        if ((posY() + _direction.y > 150) && (posY() + _direction.y < 400)) {
            dir = _direction.y;
        }
        if (dir == 0)
            _movedTime += 10;
        ++_movedTime;
        setPosition(posX(), posY() + dir);
    }

    if (_delegate != NULL && gameTime - _lastFired > _cooldown) {
        _lastFired = gameTime;
        _lifeTime += 1000;
        Entity *e = new MegaAttack(getPosition(), Vect2(-5, 0));
        _delegate->addEntity(e);
    }
}

void Boss::attack(Entity *e, int gameTime)
{
    takeDamage(gameTime);
    e->takeDamage(gameTime);
}

void Boss::takeDamage(int gameTime)
{
    --_life;
    if (_life <= 0) {
        setAlive(false);
        setDeathTime(gameTime);
    }
}

