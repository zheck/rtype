//
//  ClockManager.h
//  xCodeClient
//
//  Created by mo_r on 03/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__ClockManager__
#define __xCodeClient__ClockManager__

#include <iostream>
#include <SFML/Graphics.hpp>
class ClockManager
{
    sf::Clock _clock;
    
public:
    ClockManager();
    ~ClockManager();
    ClockManager(ClockManager const & clock);
    ClockManager & operator=(ClockManager const & clock);
    
    float getElapsedTime() const;
};

#endif /* defined(__xCodeClient__ClockManager__) */
