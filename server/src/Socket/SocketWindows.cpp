//
//  SocketWindows.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 10/28/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "SocketWindows.hpp"

Socket::Socket()
{
	for (int i = 0; i < MAX_PLAYER; ++i) {
		_clients[i] = "";
	}
	_fdmax = 10;

}

Socket::~Socket()
{
	closesocket(_listener);
	shutdown(_listener, 2);
}

void Socket::init(const std::string &port)
{
	WSADATA wsa;
	struct addrinfo _addr;
	struct addrinfo * ai;

	FD_ZERO(&_readfd);
	FD_ZERO(&_master);
	if (WSAStartup(0x0202, &wsa) != 0) {
		throw Exception("Cannot startup");
	}
	ZeroMemory(&(_addr), sizeof(_addr));
	_addr.ai_family = AF_INET;
	_addr.ai_socktype = SOCK_STREAM;
	_addr.ai_protocol = IPPROTO_TCP;
	_addr.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, port.c_str(), &(_addr), &(ai)) != 0) {
		throw Exception("cannot get addr info");
	}
	if ((_listener = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol)) == INVALID_SOCKET) {
		throw Exception("Cannot socket");
	}
	if ((bind(_listener, ai->ai_addr, ai->ai_addrlen)) == SOCKET_ERROR) {
		throw Exception("Cannot bind");
	}
	if (listen(_listener, 10) == SOCKET_ERROR) {
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

	_readfd = _master;
	if (select(_fdmax + 1, &(_readfd), NULL, NULL, NULL) == -1) {
		throw Exception("Cannot select");
	}
	for (int i = 0; i <= _fdmax; ++i) {
		if (FD_ISSET(i, &_readfd)) {
			if (i == _listener) {
				addrlen = sizeof(remoteaddr);

				newfd = accept(_listener, (struct sockaddr *)&remoteaddr, &addrlen);
				if (newfd == -1) {
					std::cerr << "Cannot accept more player" << std::endl;
					return;
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
	int ret = send(msg.id, (char *)&msg, sizeof(msg), 0);
	if (ret == -1) {
		printf("Oh dear, something went wrong with send()! %s\n", strerror(errno));
	}
}

void Socket::readMsg(Message &msg, int fd)
{
	int ret;
	ret = recv(fd, (char *)&msg, sizeof(msg), 0);
	if (ret <= 0) {
		FD_CLR(msg.id, &_readfd);
		shutdown(msg.id, SD_BOTH);
		--_fdmax;
	}
}

SocketUdp::SocketUdp()
{}

SocketUdp::~SocketUdp()
{}

void SocketUdp::init(const std::string &port)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
		throw Exception("Cannot start socket");
	}
	_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (_sockfd == INVALID_SOCKET) {
		throw Exception("Cannot socket");
	}
	_cliaddr.sin_family = AF_INET;
	_cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	_cliaddr.sin_port = htons(atoi(port.c_str()));

	if (bind(_sockfd, (SOCKADDR*)&_cliaddr, sizeof(_cliaddr)) == SOCKET_ERROR) {
		throw Exception("Cannot bind");
	}
	u_long nonblocking_enabled = TRUE;
	ioctlsocket(_sockfd, FIONBIO, &nonblocking_enabled);
}

void SocketUdp::recvMsg(Message &msg, std::string &ip)
{
	socklen_t len = sizeof(_cliaddr);
	long n;
	n = recvfrom(_sockfd, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&_cliaddr, &len);
	(void)ip;
	if (n > 0) {
		msg.messageType = MSG_GAME;
	}
}

void SocketUdp::sendMsg(const Message & msg)
{
	sendto(_sockfd, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&_cliaddr, sizeof(_cliaddr));
}
