//
//  Player.h
//  xCodeClient
//
//  Created by Zhou Fong on 11/15/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__Player__
#define __xCodeClient__Player__

#include <iostream>

#include "Entity.hpp"
#include "ClockManager.hpp"
#include "Message.hpp"

class Player : public Entity
{
public:
    int posx;
    int posy;
    
protected:
    float _lastFired;
    float _lastMoved;
    float _weaponCooldown;
    
public:
    Player();
    Player(Player const & rhs);
    ~Player();
    
    Player & operator=(Player const & rhs);
    
    void init();
    void update(ClockManager const & clock, Message & msg);
};

#endif /* defined(__xCodeClient__Player__) */
