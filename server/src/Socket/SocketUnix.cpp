//
//  SocketUnix.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 10/28/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include <unistd.h>
#include <fcntl.h>

#include "SocketUnix.hpp"
#include "Exception.hpp"

Socket::Socket()
{
    for (int i = 0; i < MAX_PLAYER; ++i) {
        _clients[i] = "";
    }
}

Socket::~Socket()
{
    close(_listener);
    shutdown(_listener, 2);
}

void Socket::init(const std::string &port)
{
    FD_ZERO(&_master);
    FD_ZERO(&_readfds);

    struct addrinfo hints;
    struct addrinfo * ai;
    struct addrinfo * p;
    int yes = 1;
    int rv;
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, port.c_str(), &hints, &ai)) != 0) {
        throw Exception("Cannot get addr info");
    }
    for (p = ai; p != NULL; p = p->ai_next) {
        _listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (_listener < 0) {
            continue;
        }
        setsockopt(_listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        if (bind(_listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(_listener);
            continue;
        }
        break;
    }
    if (p == NULL) {
        throw Exception("Cannot bind");
    }
    freeaddrinfo(ai);
    if (listen(_listener, 10) == -1) {
        throw Exception("Cannot listen");
    }
    FD_SET(_listener, &_master);
    _fdmax = _listener;
}

void Socket::recvMsg(Message &msg, std::string &ip)
{
    struct sockaddr_in remoteaddr;
    socklen_t addrlen;
    int newfd;
    
    _readfds = _master;
    if (select(_fdmax + 1, &_readfds, NULL, NULL, NULL) == -1) {
        throw Exception("Cannot select");
    }
    for(int i = 0; i <= _fdmax; ++i) {
        if (FD_ISSET(i, &_readfds)) {
            if (i == _listener) {
                addrlen = sizeof(remoteaddr);
                newfd = accept(_listener, (struct sockaddr *)&remoteaddr, &addrlen);
                if (newfd == -1) {
                    std::cerr << "Cannot accept more player" << std::endl;
                    return ;
                }
                if (newfd > _fdmax) {
                    _fdmax = newfd;
                }
                msg.copyMessage(inet_ntoa(remoteaddr.sin_addr));
                _clients[newfd] = msg.msg;
                ip = msg.msg;
                msg.messageType = MSG_CONNECT;
                msg.id = newfd;
                FD_SET(newfd, &_master);
            }
            else {
                ip = _clients[i];
                msg.id = i;
                readMsg(msg, i);
            }
        }
    }
}

void Socket::sendMsg(Message const &msg)
{
    send(msg.id, &msg, sizeof(msg), 0);
}

void Socket::readMsg(Message &msg, int fd)
{
    long nbytes;
    
    nbytes = recv(fd, &msg, sizeof(msg), 0);
    if (nbytes <= 0) {
        msg.messageType = MSG_DISCONNECT;
        close(fd);
        FD_CLR(fd, &_master);
    }
}


SocketUdp::SocketUdp()
{}

SocketUdp::~SocketUdp()
{}

void SocketUdp::init(const std::string &port)
{
    struct sockaddr_in servaddr;
    
    _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(atoi(port.c_str()));
    bind(_sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    int flags = fcntl(_sockfd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(_sockfd, F_SETFL, flags);
}

void SocketUdp::recvMsg(Message &msg, std::string &ip)
{
    socklen_t len = sizeof(_cliaddr);
    long n;
    n = recvfrom(_sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&_cliaddr, &len);
    (void)ip;
    if (n > 0) {
        msg.messageType = MSG_GAME;
    }
}

void SocketUdp::sendMsg(const Message & msg)
{
    sendto(_sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&_cliaddr, sizeof(_cliaddr));
}
