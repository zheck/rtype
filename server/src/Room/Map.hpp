//
//  Map.h
//  R-TypeServer
//
//  Created by Zhou Fong on 11/8/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Map__
#define __R_TypeServer__Map__

#include <iostream>
#include <list>
#include <map>

#include "defines.hpp"
#include "Entity.hpp"

class Game;

class Map
{
    std::list<std::pair<int, std::string> > _monsterList;
    Game * _delegate;
    std::map<std::string, Entity * (Map::*)() > _funcs;
    
public:
    Map();
    Map(Map const & rhs);
    ~Map();
    
    Map & operator=(Map const & rhs);
    void test();
    void init();
    void setDelegate(Game * g);
    std::list<std::pair<int, std::string> > getSpawnList();
    void addSpawn(int timeElapsed);
    Entity * spaceShip();
    Entity * spaceShip2();
    Entity * shockWave();
    Entity * boss();
    Entity * asteroid();
};

#endif /* defined(__R_TypeServer__Map__) */
