//
//  Socket.cpp
//  R-Type
//
//  Created by mo_r on 17/10/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include <unistd.h>
#include <csignal>
#include <strings.h>
#include "sstream"
#include "SocketUnix.hpp"
#include "Message.hpp"


Socket::Socket()
{}

Socket::~Socket()
{
    close(_fd);
    shutdown(_fd, 2);
}

void connect_alarm(int sig)
{
  (void)sig;
}

void Socket::init(std::string const & ip, bool & connexion, short port)
{
    struct protoent *pe;
    struct sockaddr_in sin;
    
    _ip = ip;
    _port = port;
    pe = getprotobyname("TCP");
    if (!pe) {
        std::cerr << "Failed to getprotobyname" << std::endl;
        return;
    }
    _fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
    if (_fd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return;
    }
    sin.sin_family = AF_INET;
    sin.sin_port = htons(_port);
    sin.sin_addr.s_addr = inet_addr(_ip.c_str());

    signal( SIGALRM, connect_alarm );
    alarm(1);
    int status = connect(_fd, (struct sockaddr *)&sin, sizeof(sin));
    if (status == -1) {
        if (close(_fd) == -1) {
            std::cerr << "failed to close socket" << std::endl;
        }
        std::cerr << "Failed to connect to server" << std::endl;
        return ;
    }
    connexion = true;
}

void Socket::recvMsg(Message & msg)
{
    int fds;
    int ret;
    
    _tv.tv_sec = 0;
    _tv.tv_usec = 1;
    fds = 0;
    FD_ZERO(&_fdWrite);
    FD_ZERO(&_fdRead);
    FD_SET(0, &_fdRead);
    FD_SET(_fd, &_fdRead);
    if (_fd > fds)
        fds = _fd;
    FD_SET(_fd, &_fdWrite);
    if ((ret = select(fds + 1, &_fdRead, &_fdWrite, NULL, &_tv)) == -1) {
        std::cerr << "client select failed "<< std::endl;
        return ;
    }
    if (FD_ISSET(_fd, &_fdRead)) {
        recv(_fd, (&msg), sizeof(msg), 0);
    }
}

void Socket::sendMsg(Message const & msg)
{
    if (FD_ISSET(_fd, &_fdWrite)) {
        send(_fd, &msg, sizeof(msg), 0);
    }
}

SocketUdp::SocketUdp()
{}

SocketUdp::~SocketUdp()
{
    close(_sockfd);
    shutdown(_sockfd, 2);
}

void SocketUdp::init(const std::string &ip, bool &connexion, short port)
{
  (void)connexion;
    _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&_servaddr, sizeof(_servaddr));
    _servaddr.sin_family = AF_INET;
    _servaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    _servaddr.sin_port = htons(port);
    
    int flags = fcntl(_sockfd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(_sockfd, F_SETFL, flags);
}

void SocketUdp::recvMsg(Message &msg)
{
    int ret;
    ret = recvfrom(_sockfd, &msg, sizeof(msg),0,NULL,NULL);
    
    static int i = 0;
    if (ret > 0) {
            ++i;
    }
}

void SocketUdp::sendMsg(const Message &msg)
{
    sendto(_sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&_servaddr,sizeof(_servaddr));
    
    static int i = 0;
    ++i;
}
