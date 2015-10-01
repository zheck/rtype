//
//  Socket.cpp
//  R-Type
//
//  Created by mo_r on 17/10/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include <csignal>
#include "sstream"
#include "SocketWindows.hpp"
#include "Message.hpp"


Socket::Socket()
{}

Socket::~Socket()
{
    closesocket(_fd);
    shutdown(_fd, 2);
}

void connect_alarm(int sig)
{
  (void)sig;
}

void Socket::init(std::string const & ip, bool & connexion, short port)
{
  struct addrinfo _addr;
  struct addrinfo * result = NULL, *ptr = NULL;
  WSADATA wsa;
  std::cout << ip << std::endl;
  if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
    std::cerr << "cannot startup" << std::endl;
  }
  ZeroMemory(&(_addr), sizeof(_addr));
  _addr.ai_family = AF_UNSPEC;
  _addr.ai_socktype = SOCK_STREAM;
  _addr.ai_protocol = IPPROTO_TCP;
  std::stringstream ss;
  std::string portStr;
  ss << port;
  ss >> portStr;

  int iResult = getaddrinfo(ip.c_str(), portStr.c_str(), &_addr, &result);
  if (iResult != 0) {
    printf("WSAStartup failed with error: %d\n", iResult);
    return ;
  }
  ptr = result;
  _fd = socket(ptr->ai_family, ptr->ai_socktype, 
	       ptr->ai_protocol);
  std::cout << "step 2" << std::endl;
  if (_fd == INVALID_SOCKET) {
    printf("socket failed with error: %ld\n", WSAGetLastError());
    WSACleanup();
    return ;
  }
  iResult = connect(_fd, ptr->ai_addr, (int)ptr->ai_addrlen);
  if (iResult == SOCKET_ERROR) {
    closesocket(_fd);
    _fd = INVALID_SOCKET;
    return ;
  }
  connexion = true;
}

void Socket::recvMsg(Message & msg)
{
  int ret;
    
  _tv.tv_sec = 0;
  _tv.tv_usec = 1;
  FD_ZERO(&_writefd);
  FD_ZERO(&_readfd);
  FD_SET(_fd, &_readfd);
  if ((ret = select(_fd, &_readfd, &_writefd, NULL, &_tv)) == -1) {
    std::cout << "client select failed "<< std::endl;
    return ;
  }
  if (FD_ISSET(_fd, &_readfd)) {
    recv(_fd, (char *)&msg, sizeof(msg), 0);
  }
}

void Socket::test()
{
    
}

void Socket::sendMsg(Message const & msg)
{
  send(_fd, (char *)&msg, sizeof(msg), 0);
}

SocketUdp::SocketUdp()
{}

SocketUdp::~SocketUdp()
{
}

void SocketUdp::init(const std::string &ip, bool &connexion, short port)
{
  (void)connexion;
}

void SocketUdp::recvMsg(Message &msg)
{
}

void SocketUdp::sendMsg(const Message &msg)
{

}
