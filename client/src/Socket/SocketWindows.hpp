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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <list>


#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <Shlwapi.h>

#pragma comment(lib,"ws2_32.lib")


#include "Message.hpp"
#include "ISocket.hpp"

class Socket : public ISocket
{
  short _port;
  std::string _ip;
  int _fd;
  struct timeval _tv;
  FD_SET _readfd;
  FD_SET _writefd;
  int _fdMax;
    
public:
    Socket();
    Socket(Socket const & socket);
    virtual ~Socket();
    
    Socket & operator=(Socket const & socket);
    
    virtual void init(std::string const & ip, bool &connexion, short port);
    virtual void recvMsg(Message & msg);
    virtual void sendMsg(Message const & msg);
    void test();
};

class SocketUdp : public ISocket
{
    int _sockfd;
//    struct sockaddr_in _servaddr;
    
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
