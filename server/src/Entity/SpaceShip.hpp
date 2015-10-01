//
//  SpaceShip.h
//  R-TypeServer
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__SpaceShip__
#define __R_TypeServer__SpaceShip__

#include <iostream>
#include <list>

#include "Entity.hpp"
#include "Game.hpp"

class SpaceShip : public Entity
{
    Vect2 _direction;
    std::list<std::pair<int, int> > _behaviours;
    int _cooldown;
    Game * _delegate;
    int _lastFired;
    eType _bonus;
    
public:
    SpaceShip(Vect2 const & position, eType type, Game * delegate);
    SpaceShip(SpaceShip const & rhs);
    virtual ~SpaceShip();
    
    SpaceShip & operator=(SpaceShip const & rhs);
    
    virtual void update(int gameTime);
    virtual void attack(Entity * e, int gameTime);
    virtual void takeDamage(int gameTime);
    void setBonus(eType);
};

#endif /* defined(__R_TypeServer__SpaceShip__) */
