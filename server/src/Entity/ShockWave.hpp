//
//  ShockWave.h
//  R-TypeServer
//
//  Created by Zhou Fong on 11/19/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__ShockWave__
#define __R_TypeServer__ShockWave__

#include <iostream>

#include "Entity.hpp"

class ShockWave : public Entity
{
    Vect2 _direction;
    
public:
    ShockWave(Vect2 const & position , Vect2 const & direction);
    ShockWave(ShockWave const & rhs);
    virtual ~ShockWave();
    
    ShockWave & operator=(ShockWave const & rhs);
    
    virtual void update(int gameTime);
    virtual void attack(Entity * e, int gameTime);
    virtual void takeDamage(int gameTime);
};

#endif /* defined(__R_TypeServer__ShockWave__) */
