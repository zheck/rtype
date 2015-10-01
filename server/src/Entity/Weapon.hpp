//
//  Weapon.h
//  R-TypeServer
//
//  Created by Zhou Fong on 11/20/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Weapon__
#define __R_TypeServer__Weapon__

#include <iostream>
#include <map>

#include "defines.hpp"
#include "Vect2.hpp"
#include "Entity.hpp"

class Game;

class Weapon
{
    Game * _delegate;
    eType _bulletType;
    int _ammo;
    int _lastFired;
    int _cooldown;
    std::map<eType, Entity * (Weapon::*)(Vect2 const &, Vect2 const &)> _missile;
    
public:
    Weapon();
    Weapon(Weapon const & rhs);
    ~Weapon();
    
    Weapon & operator=(Weapon const & rhs);
    
    void reinit();
    void setDelegate(Game * g);
    bool setBulletType(eType bulletType);
    void fire(eType bulletType, Vect2 const & position, Vect2 const & direction);
    Entity * bullet(Vect2 const & position, Vect2 const & direction);
    Entity * shockWave(Vect2 const & position, Vect2 const & direction);
    Entity * megaAttack(Vect2 const & position, Vect2 const & direction);
};

#endif /* defined(__R_TypeServer__Weapon__) */
