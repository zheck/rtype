//
//  ISocket.h
//  R-TypeServer
//
//  Created by Zhou Fong on 10/14/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef R_TypeServer_ISocket_h
#define R_TypeServer_ISocket_h

#include "Message.hpp"

class ISocket
{
public:
    virtual ~ISocket() {}
    
    virtual void init(std::string const & port) = 0;
    virtual void recvMsg(Message & msg, std::string & ip) = 0;
    virtual void sendMsg(Message const & msg) = 0;
};

#ifdef _WIN32
# include "SocketWindows.hpp"
#else
# include "SocketUnix.hpp"
#endif

#endif
