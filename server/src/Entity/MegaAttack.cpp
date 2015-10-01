//
//  MegaAttack.cpp
//  R-TypeServer
//
//  Created by mo_r on 23/11/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "MegaAttack.hpp"

MegaAttack::MegaAttack(Vect2 const & position, Vect2 const & direction) :
Entity(position, MEGA_ATTACK, Vect2(54, 50)),
_direction(direction)
{}

MegaAttack::~MegaAttack()
{}

void MegaAttack::attack(Entity *e, int gameTime)
{
    e->takeDamage(gameTime);
    if (e->getType() == BOSS || e->getType() == ASTEROID) {
        setAlive(false);
        setDeathTime(gameTime);
    }
    else if (e->getType() == MEGA_ATTACK) {
        setAlive(false);
        setDeathTime(gameTime);
        e->setAlive(false);
        e->setDeathTime(gameTime);
    }
}

void MegaAttack::takeDamage(int gameTime)
{
    (void)gameTime;
}

void MegaAttack::update(int gameTime)
{
    (void)gameTime;
    setPosition(posX() + _direction.x, posY() + _direction.y);
}