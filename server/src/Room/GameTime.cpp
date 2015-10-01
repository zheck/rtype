//
//  GameTime.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/16/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//
#include <time.h>

#include "GameTime.hpp"

GameTime::GameTime()
{}

GameTime::~GameTime()
{}

#ifdef _WIN32

#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
void getTimeOfDay(struct timeval * t)
{
    FILETIME ft;
    unsigned __int64 tmpres = 0;
    static int tzflag;
    
    GetSystemTimeAsFileTime(&ft);
    
    tmpres |= ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;
    
    tmpres /= 10;
    t->tv_sec = (long)(tmpres / 1000000UL);
    t->tv_usec = (long)(tmpres % 1000000UL);
}

#else

void getTimeOfDay(struct timeval * t)
{
	gettimeofday(t, NULL);
}

#endif

void GameTime::reset()
{
    getTimeOfDay(&_t);
    _beginSec = _t.tv_sec;
    _beginUsec = _t.tv_usec;
}

int GameTime::getElapsedTime()
{
    getTimeOfDay(&_t);
    long int res = _t.tv_sec - _beginSec;
    res = res * 1000 + _t.tv_usec / 1000;
    return (int)res;
	return 0;
}
