//
//  Menu.h
//  xCodeClient
//
//  Created by mo_r on 22/10/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__Menu__
#define __xCodeClient__Menu__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ClockManager.hpp"
#include "Message.hpp"
#include "Defines.hpp"
#include "Vect2f.hpp"

class Menu
{
public:
    eGameState gameState;
    
private:
    std::string _userName;
    std::string _serverAdress;
    Vect2f _cursorPos;
    eINPUTSTATE _inputState;
    float _lastUpdateTime;
    bool _playPressed;
    
public:
    Menu();
    ~Menu();
    Menu(Menu const & rhs);
    
    Menu & operator=(Menu const & rhs);
    
    void init();
    void update(sf::Event const & event, ClockManager const & clock, Message & msg);
    
    std::string getInputIp() const;
    std::string getInputUser() const;
    Vect2f getCursorPos() const;
    
private:
    void updateIp(std::string const & str);
    void updateUsername(std::string const & str);
    void switchInput();
};

#endif /* defined(__xCodeClient__Menu__) */
