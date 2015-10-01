//
//  SocketUnix.h
//  R-TypeServer
//
//  Created by Zhou Fong on 10/28/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__SocketUnix__
#define __R_TypeServer__SocketUnix__

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <map>

#include "ISocket.hpp"

class Socket : public ISocket
{
    fd_set _master;
    fd_set _readfds;
    int _fdmax;
    int _listener;
    std::map<int, std::string> _clients;
    
public:
    Socket();
    Socket(Socket const & rhs);
    virtual ~Socket();
    
    Socket & operator=(Socket const & rhs);
    
    virtual void init(std::string const & port);
    virtual void recvMsg(Message & msg, std::string & ip);
    virtual void sendMsg(Message const & msg);
    
private:
    void readMsg(Message & msg, int fd);
};

class SocketUdp : public ISocket
{
    int _sockfd;
    struct sockaddr_in _cliaddr;
    
public:
    SocketUdp();
    SocketUdp(SocketUdp const & rhs);
    virtual ~SocketUdp();
    
    SocketUdp & operator=(SocketUdp const & rhs);
    
    virtual void init(std::string const & port);
    virtual void recvMsg(Message & msg, std::string & ip);
    virtual void sendMsg(Message const & msg);
};

#endif /* defined(__R_TypeServer__SocketUnix__) */
