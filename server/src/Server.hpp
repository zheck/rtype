//
//  Server.h
//  R-TypeServer
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Server__
#define __R_TypeServer__Server__

#include <iostream>
#include <list>
#include <map>

#include "Room.hpp"
#include "Player.hpp"
#include "ISocket.hpp"
#include "ThreadPool.hpp"

class Server
{
    std::list<Room *> _rooms;
    std::list<Player *> _players;
    bool _running;
    ISocket * _socket;
    std::map<eMessageType, void (Server::*)(Message & msg, std::string const & ip)> _funcs;
    ThreadPool _threadPool;
    
public:
    Server();
    Server(Server const & rhs);
    ~Server();
    
    Server & operator=(Server const & rhs);
    
    void init(std::string const & port);
    void run();
    void release();
    
private:
    void createRoom(Message & msg, std::string const & ip);
    void createPlayer(Message & msg, std::string const & ip);
    void disconnectPlayer(Message & msg, std::string const & ip);
    void joinRoom(Message & msg, std::string const & ip);
    void leaveRoom(Message & msg, std::string const & ip);
    void startGame(Message & msg, std::string const & ip);
    void createNewPlayer(Message & msg, std::string const & ip);
    void roomList(Message & msg, std::string const & ip);
    
    std::string generateNewClientPort();
    Player * findPlayerByIp(std::string const & ip);
    Room * findRoomByName(std::string const & name);
};

#endif /* defined(__R_TypeServer__Server__) */
