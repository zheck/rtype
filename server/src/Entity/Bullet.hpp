//
//  Bullet.h
//  R-TypeServer
//
//  Created by Zhou Fong on 10/14/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Bullet__
#define __R_TypeServer__Bullet__

#include <iostream>

#include "Entity.hpp"

class Bullet : public Entity
{
    Vect2 _direction;
    
public:
    Bullet(Vect2 const & position , Vect2 const & direction);
    Bullet(Bullet const & rhs);
    virtual ~Bullet();
    
    Bullet & operator=(Bullet const & rhs);
    
    virtual void update(int gameTime);
    virtual void attack(Entity * e, int gameTime);
    virtual void takeDamage(int gameTime);
};

#endif /* defined(__R_TypeServer__Bullet__) */
