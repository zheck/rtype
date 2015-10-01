//
//  MegaAttack.h
//  R-TypeServer
//
//  Created by mo_r on 23/11/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__MegaAttack__
#define __R_TypeServer__MegaAttack__

#include <iostream>

#include "Entity.hpp"

class MegaAttack : public Entity
{
    Vect2 _direction;
    
public:
    MegaAttack(Vect2 const & position , Vect2 const & direction);
    MegaAttack(MegaAttack const & rhs);
    virtual ~MegaAttack();
    
    MegaAttack & operator=(MegaAttack const & rhs);
    
    virtual void update(int gameTime);
    virtual void attack(Entity * e, int gameTime);
    virtual void takeDamage(int gameTime);
};

#endif /* defined(__R_TypeServer__MegaAttack__) */
