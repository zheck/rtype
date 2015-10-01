//
//  Bonus.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/20/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "Bonus.hpp"

Bonus::Bonus(eType bonusType, Vect2 const & position, Vect2 const & direction) :
Entity(position, bonusType, Vect2(20, 20)),
_direction(direction)
{
}

Bonus::~Bonus()
{}

void Bonus::attack(Entity *e, int gameTime)
{
    takeDamage(gameTime);
    e->takeDamage(gameTime);
}

void Bonus::takeDamage(int gameTime)
{
    (void)gameTime;
}

void Bonus::update(int gameTime)
{
    (void)gameTime;
    setPosition(posX() + _direction.x, posY() + _direction.y);
}