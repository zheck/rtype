//
//  ShockWave.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/19/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "ShockWave.hpp"

ShockWave::ShockWave(Vect2 const & position, Vect2 const & direction) :
Entity(position, SHOCK_WAVE, Vect2(82, 15)),
_direction(direction)
{}

ShockWave::~ShockWave()
{}

void ShockWave::attack(Entity *e, int gameTime)
{
    e->takeDamage(gameTime);
    if (e->getType() == BOSS || e->getType() == ASTEROID) {
        setAlive(false);
        setDeathTime(gameTime);
    }
    else if (e->getType() == SHOCK_WAVE) {
        setAlive(false);
        setDeathTime(gameTime);
        e->setAlive(false);
        e->setDeathTime(gameTime);
    }
}

void ShockWave::takeDamage(int gameTime)
{
    (void)gameTime;
}

void ShockWave::update(int gameTime)
{
    (void)gameTime;
    setPosition(posX() + _direction.x, posY() + _direction.y);
}