//
//  SocketWindows.h
//  R-TypeServer
//
//  Created by Zhou Fong on 10/28/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__SocketWindows__
#define __R_TypeServer__SocketWindows__

#include <iostream>

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <list>
#include <Shlwapi.h>
#include <map>

#pragma comment(lib,"ws2_32.lib")

#include "Exception.hpp"
#include "Message.hpp"
#include "ISocket.hpp"

class Socket : public ISocket
{
	int _listener;
	int _fdmax;
	FD_SET _readfd;
	FD_SET _master;
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
	sockaddr_in _cliaddr;

public:
    SocketUdp();
    SocketUdp(SocketUdp const & rhs);
    virtual ~SocketUdp();
    
    SocketUdp & operator=(SocketUdp const & rhs);
    
    virtual void init(std::string const & port);
    virtual void recvMsg(Message & msg, std::string & ip);
    virtual void sendMsg(Message const & msg);
};

#endif /* defined(__R_TypeServer__SocketWindows__) */
