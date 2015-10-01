//
//  GameTime.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/16/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "GameTime.hpp"

GameTime::GameTime()
{}

GameTime::~GameTime()
{}

void GameTime::reset()
{
    gettimeofday(&_t, NULL);
    _beginSec = _t.tv_sec;
    _beginUsec = _t.tv_usec;
}

long int GameTime::getElapsedTime()
{
    gettimeofday(&_t, NULL);
    long int res = _t.tv_sec - _beginSec;
    res = res * 1000 + _t.tv_usec / 1000;

    return res;
}
