//
//  Boss.h
//  R-TypeServer
//
//  Created by Zhou Fong on 11/19/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Boss__
#define __R_TypeServer__Boss__

#include <iostream>
#include <list>

#include "Entity.hpp"
#include "Game.hpp"

class Boss : public Entity
{
    int _life;
    Game * _delegate;
    Vect2 _direction;
    std::list<int> _behaviours;
    int _cooldown;
    int _lastFired;
    int _lifeTime;
    int _movedTime;
    
public:
    Boss(Vect2 const & position, Game * delegate);
    Boss(Boss const & rhs);
    virtual ~Boss();
    
    Boss & operator=(Boss const & rhs);
    
    virtual void update(int gameTime);
    virtual void attack(Entity * e, int gameTime);
    virtual void takeDamage(int gameTime);
};

#endif /* defined(__R_TypeServer__Boss__) */
