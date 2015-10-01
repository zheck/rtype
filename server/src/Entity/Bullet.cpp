//
//  Bullet.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 10/14/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "Bullet.hpp"

Bullet::Bullet(Vect2 const & position, Vect2 const & direction) :
Entity(position, BULLET, Vect2(8, 8)),
_direction(direction)
{}

Bullet::~Bullet()
{}

void Bullet::attack(Entity *e, int gameTime)
{
    takeDamage(gameTime);
    e->takeDamage(gameTime);
}

void Bullet::takeDamage(int gameTime)
{
    setAlive(false);
    setDeathTime(gameTime);
}

void Bullet::update(int gameTime)
{
    (void)gameTime;
    setPosition(posX() + _direction.x, posY() + _direction.y);
}