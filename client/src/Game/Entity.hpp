//
//  Entity.h
//  R-TypeServer
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Entity__
#define __R_TypeServer__Entity__

#include <iostream>

#include "Defines.hpp"
#include "Vect2.hpp"

class Entity
{
public:
    int lastUpdate;
    int deathTime;
    int id;
    Vect2 position;

protected:
    bool _isAlive;
    eType _type;
    
public:
    Entity(Vect2 const & position, eType type);
    Entity(Entity const & entity);
    ~Entity();
    
    Entity & operator=(Entity const & entity);
    
    bool isAlive() const;
    void setAlive(bool b);
    eType getType() const;
};

#endif /* defined(__R_TypeServer__Entity__) */
