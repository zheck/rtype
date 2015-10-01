//
//  Game.h
//  xCodeClient
//
//  Created by mo_r on 26/10/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__Game__
#define __xCodeClient__Game__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>

#include "Defines.hpp"
#include "Entity.hpp"
#include "ClockManager.hpp"
#include "Message.hpp"
#include "Player.hpp"

#define SPEED 13

class Game
{
    Player _p;
    int _playerId;
    std::map<int, Entity *> _entities;

public:
    Game();
    Game(Game const & rhs);
    ~Game();

    Game & operator=(Game const & rhs);
    
    void init(int id);
    void release();
    void update(sf::Event const & event, ClockManager const & clock, Message & msg);
    void updateMap(Message const & msg);
    void handleDeath(Message const & msg);
    std::map<int, Entity *> & getEntities();
};

#endif /* defined(__xCodeClient__Game__) */
