//
//  Message.h
//  R-TypeServer
//
//  Created by Zhou Fong on 11/1/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Message__
#define __R_TypeServer__Message__

#include <iostream>

#include "Defines.hpp"

class Message {
public:
    eMessageType messageType;
    eType entity;
    int id;
    int time;
    bool response;
    char msg[MSG_SIZE];
    bool isAlive;
    int posX;
    int posY;

public:
    Message();
    Message(Message const & rhs);
    ~Message();
    
    Message & operator=(Message const & rhs);
    Message & operator=(char * rhs);
    
    void copyMessage(char const * str);
};

#endif /* defined(__R_TypeServer__Message__) */
