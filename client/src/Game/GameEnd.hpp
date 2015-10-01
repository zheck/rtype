//
//  GameEnd.h
//  xCodeClient
//
//  Created by Zhou Fong on 11/18/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__GameEnd__
#define __xCodeClient__GameEnd__

#include <iostream>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "Defines.hpp"
#include "ClockManager.hpp"
#include "Message.hpp"

class GameEnd
{
    eSelection _selection;
    eGameState _gameStat;
    float _time;
    sf::IntRect _startGameRect;
    std::list<std::string> _listPlayer;
    
public:
    GameEnd();
    GameEnd(GameEnd const & rhs);
    ~GameEnd();
    
    GameEnd & operator=(GameEnd const & rhs);
    
    void init();
    void clear();
    void update(sf::Event const & event, ClockManager const & clock, Message & msg);
    std::list<std::string> getListPlayer() const;
    sf::IntRect getStartGameRect() const;
};

#endif /* defined(__xCodeClient__GameEnd__) */
