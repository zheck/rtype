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

#include "IEntity.hpp"

class Entity : public IEntity
{
    Vect2 _position;
    Vect2 _size;
    Vect2 _direction;
    
    int _id;
    bool _isAlive;
    eType _type;
    int _deathTime;
    
public:
    Entity(Vect2 const & position, eType type, Vect2 const & size);
    Entity(Entity const & rhs);
    virtual ~Entity();
    
    Entity & operator=(Entity const & rhs);

    virtual void update(int gameTime) = 0;
    virtual void attack(Entity * e, int gameTime) = 0;
    virtual void takeDamage(int gameTime) = 0;
    virtual eType getType() const;
    virtual bool isAlive() const;
    virtual Vect2 & getPosition();
    virtual Vect2 & getSize();
    virtual void setPosition(int px, int py);
    virtual int getId() const;
    void setId(int id);
    void setAlive(bool b);
    void setDeathTime(int t);
    long int getDeathTime() const;
    int posX() const;
    int posY() const;
    int width() const;
    int height() const;
};

#endif /* defined(__R_TypeServer__Entity__) */
