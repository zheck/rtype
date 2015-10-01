//
//  Bonus.h
//  R-TypeServer
//
//  Created by Zhou Fong on 11/20/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Bonus__
#define __R_TypeServer__Bonus__

#include <iostream>

#include "Vect2.hpp"
#include "Entity.hpp"
#include "defines.hpp"

class Bonus : public Entity
{
    Vect2 _direction;
    
public:
    Bonus(eType bonusType, Vect2 const & position , Vect2 const & direction);
    Bonus(Bonus const & rhs);
    virtual ~Bonus();
    
    Bonus & operator=(Bonus const & rhs);
    
    virtual void update(int gameTime);
    virtual void attack(Entity * e, int gameTime);
    virtual void takeDamage(int gameTime);
};

#endif /* defined(__R_TypeServer__Bonus__) */
