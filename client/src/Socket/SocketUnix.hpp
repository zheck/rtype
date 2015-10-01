//
//  Socket.h
//  R-Type
//
//  Created by mo_r on 17/10/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_Type__Socket__
#define __R_Type__Socket__

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <list>

#include "Message.hpp"
#include "ISocket.hpp"

class Socket : public ISocket
{
    short _port;
    std::string _ip;
    int _fd;
    struct timeval _tv;
    fd_set _fdRead;
    fd_set _fdWrite;
    int _fdMax;
    
public:
    Socket();
    Socket(Socket const & socket);
    virtual ~Socket();
    
    Socket & operator=(Socket const & socket);
    
    virtual void init(std::string const & ip, bool &connexion, short port);
    virtual void recvMsg(Message & msg);
    virtual void sendMsg(Message const & msg);
};

class SocketUdp : public ISocket
{
    int _sockfd;
    struct sockaddr_in _servaddr;
    
public:
    SocketUdp();
    SocketUdp(SocketUdp const & rhs);
    virtual ~SocketUdp();
    
    SocketUdp & operator=(SocketUdp const & rhs);
    
    virtual void init(std::string const & ip, bool &connexion, short port);
    virtual void recvMsg(Message & msg);
    virtual void sendMsg(Message const & msg);
};

#endif /* defined(__R_Type__Socket__) */
