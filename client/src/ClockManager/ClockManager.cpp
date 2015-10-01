//
//  ClockManager.cpp
//  xCodeClient
//
//  Created by mo_r on 03/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "ClockManager.hpp"

ClockManager::ClockManager()
{}

ClockManager::~ClockManager()
{}

float ClockManager::getElapsedTime() const
{
    return (_clock.getElapsedTime().asSeconds());
}