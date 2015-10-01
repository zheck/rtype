//
//  GameTime.h
//  R-TypeServer
//
//  Created by Zhou Fong on 11/16/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__GameTime__
#define __R_TypeServer__GameTime__

#include <iostream>
#include <sys/time.h>

class GameTime
{
    long int _beginSec;
    int _beginUsec;
    struct timeval _t;
    
public:
    GameTime();
    GameTime(GameTime const & rhs);
    ~GameTime();
    
    GameTime & operator=(GameTime const & rhs);
    
    void reset();
    long int getElapsedTime();
};

#endif /* defined(__R_TypeServer__GameTime__) */
