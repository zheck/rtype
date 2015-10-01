//
//  Asteroid.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/20/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "Asteroid.hpp"

Asteroid::Asteroid(Vect2 const & position, Vect2 const & direction) :
Entity(position, ASTEROID, Vect2(100, 50)),
_direction(direction)
{}

Asteroid::~Asteroid()
{}

void Asteroid::attack(Entity *e, int gameTime)
{
    e->takeDamage(gameTime);
}

void Asteroid::takeDamage(int gameTime)
{
    (void)gameTime;
}

void Asteroid::update(int gameTime)
{
    (void)gameTime;
    setPosition(posX() + _direction.x, posY() + _direction.y);
}