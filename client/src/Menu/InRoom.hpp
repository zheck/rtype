//
//  InRoom.h
//  xCodeClient
//
//  Created by mo_r on 10/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__InRoom__
#define __xCodeClient__InRoom__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "Defines.hpp"
#include "ClockManager.hpp"
#include "Message.hpp"

class InRoom
{
    eSelection _selection;
    float _time;
    sf::IntRect _startGameRect;
    std::list<std::string> _listPlayer;
    bool _userInteractionEnabled;
    
public:
    InRoom();
    InRoom(InRoom const & rhs);
    ~InRoom();

    InRoom & operator=(InRoom const & rhs);
    
    void init();
    void clear();
    void update(sf::Event const & event, ClockManager const & clock, Message & msg);
    std::list<std::string> * getListPlayer();
    sf::IntRect getStartGameRect() const;
    void setUserInteraction(bool b);
};

#endif /* defined(__xCodeClient__InRoom__) */
