//
//  Entity.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "Entity.hpp"

Entity::Entity(Vect2 const & position, eType type) :
position(position),
_isAlive(true),
_type(type)
{
    lastUpdate = 0;
    deathTime = 0;
    _isAlive = true;
}

Entity::~Entity()
{}

bool Entity::isAlive() const
{
    return _isAlive;
}

void Entity::setAlive(bool b)
{
    _isAlive = b;
}

eType Entity::getType() const
{
    return _type;
}
