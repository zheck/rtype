//
//  Entity.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "Entity.hpp"

Entity::Entity(Vect2 const & position, eType type, Vect2 const & size) :
_position(position),
_size(size),
_type(type)
{
    _isAlive = true;
}

Entity::~Entity()
{}

Vect2 & Entity::getPosition()
{
    return _position;
}

Vect2 & Entity::getSize()
{
    return _size;
}

void Entity::setPosition(int px, int py)
{
    _position.x = px;
    _position.y = py;
}

bool Entity::isAlive() const
{
    return _isAlive;
}

void Entity::setDeathTime(int t)
{
    _deathTime = t;
}

long int Entity::getDeathTime() const
{
    return _deathTime;
}

void Entity::setAlive(bool b)
{
    _isAlive = b;
}

eType Entity::getType() const
{
    return _type;
}

int Entity::getId() const
{
    return _id;
}

void Entity::setId(int id)
{
    _id = id;
}

int Entity::width() const
{
    return _size.x;
}

int Entity::height() const
{
    return _size.y;
}

int Entity::posX() const
{
    return _position.x;
}

int Entity::posY() const
{
    return _position.y;
}
