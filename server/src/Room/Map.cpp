//
//  Map.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/8/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include <fstream>
#include <stdio.h>
#include <string>

#include "Map.hpp"
#include "Exception.hpp"
#include "SpaceShip.hpp"
#include "Game.hpp"
#include "Boss.hpp"
#include "Asteroid.hpp"

Map::Map()
{
    _funcs["MINION"] = &Map::spaceShip;
    _funcs["MINION2"] = &Map::spaceShip2;
    _funcs["SHOCKWAVE"] = &Map::shockWave;
    _funcs["BOSS"] = &Map::boss;
    _funcs["ASTEROID"] = &Map::asteroid;
}

Map::~Map()
{}

void Map::init()
{
    std::string str;
    int nb;
    size_t pos;
    std::fstream myfile("ressources/lvl2.strings");
    if (!myfile.is_open()) {
        std::cerr << "cannot open file" << std::endl;
        return ;
    }
    while (std::getline(myfile, str)) {
        if ((pos = str.find("=")) != std::string::npos) {
            nb = atoi(str.substr(0, pos).c_str());
            _monsterList.push_back(std::make_pair(nb, str.substr(pos + 1)));
        }
    }
}

void Map::setDelegate(Game *g)
{
    _delegate = g;
}

void Map::addSpawn(int timeElapsed)
{
    while (_monsterList.size() > 0 &&  _monsterList.front().first < timeElapsed && _delegate != NULL) {
        std::pair<int, std::string> e = _monsterList.front();
          if (_funcs.find(_monsterList.front().second) != _funcs.end()) {
         Entity * e = (this->*_funcs[_monsterList.front().second])();
          _delegate->addEntity(e);
        }
        _monsterList.pop_front();
    }
}

Entity * Map::boss()
{
    Entity * e = new Boss(Vect2(700, 300), _delegate);
    return e;
}

Entity * Map::asteroid()
{
    int posy = rand() % 450 + 100;
    Entity * e = new Asteroid(Vect2(800, posy), Vect2(-1, 0));
    return e;
}

Entity * Map::shockWave()
{
    int posy = rand() % 500 + 50;
    Entity * monster = new SpaceShip(Vect2(800, posy), MINION, _delegate);
    static_cast<SpaceShip *>(monster)->setBonus(SHOCK_WAVE);
    return monster;
}

Entity * Map::spaceShip()
{
    int posy = rand() % 500 + 50;
    Entity * monster = new SpaceShip(Vect2(800, posy), MINION, _delegate);
    return monster;
}

Entity * Map::spaceShip2()
{
    int posy = rand() % 500 + 50;
    Entity * monster = new SpaceShip(Vect2(800, posy), MINION2, _delegate);
    return monster;
}

std::list<std::pair<int, std::string> > Map::getSpawnList()
{
    return _monsterList;
}