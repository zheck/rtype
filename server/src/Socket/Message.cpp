//
//  Message.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 11/1/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "Message.hpp"

Message::Message()
{}

Message::~Message()
{}

Message & Message::operator=(const Message &rhs)
{
    messageType = rhs.messageType;
    id = rhs.id;
    time = rhs.time;
    response = rhs.response;
    isAlive = rhs.isAlive;
    posX = rhs.posX;
    posY = rhs.posY;

    return *this;
}

Message & Message::operator=(char * rhs)
{
    Message * msg = reinterpret_cast<Message *>(rhs);
    *this = *msg;
    return *this;
}

void Message::copyMessage(const char * str)
{
    strcpy(msg, str);
}