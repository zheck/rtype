//
//  Asteroid.h
//  R-TypeServer
//
//  Created by Zhou Fong on 11/20/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Asteroid__
#define __R_TypeServer__Asteroid__

#include <iostream>

#include "Entity.hpp"

class Asteroid : public Entity
{
    Vect2 _direction;
    
public:
    Asteroid(Vect2 const & position , Vect2 const & direction);
    Asteroid(Asteroid const & rhs);
    virtual ~Asteroid();
    
    Asteroid & operator=(Asteroid const & rhs);
    
    virtual void update(int gameTime);
    virtual void attack(Entity * e, int gameTime);
    virtual void takeDamage(int gameTime);
};

#endif /* defined(__R_TypeServer__Asteroid__) */
