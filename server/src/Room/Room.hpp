//
//  Room.h
//  R-TypeServer
//
//  Created by Zhou Fong on 10/14/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Room__
#define __R_TypeServer__Room__

#include <iostream>
#include <list>

#include "Game.hpp"
#include "Player.hpp"
#include "ThreadPool.hpp"

class Room
{
    std::string _roomName;
    std::list<Player *> _playerList;
    Game _game;
    bool _playing;
    
public:
    Room(std::string const & roomName);
    Room(Room const & rhs);
    ~Room();
    
    Room & operator=(Room const & rhs);
    
    void startGame(ThreadPool & tp);
    std::string & getRoomName();
    std::list<Player *> & getPlayerList();
    void addPlayer(Player * p);
    void removePlayer(Player * p);
    bool isPlaying() const;
};

void runGame(void * data);

#endif /* defined(__R_TypeServer__Room__) */
