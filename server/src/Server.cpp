//
//  Server.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include <cstdlib>
#include <ctime>
#include <sstream>

#include "Server.hpp"

Server::Server() :
_threadPool(7)
{
    _funcs[MSG_CONNECT] = &Server::createPlayer;
    _funcs[MSG_DISCONNECT] = &Server::disconnectPlayer;
    _funcs[MSG_CREAT_ROOM] = &Server::createRoom;
    _funcs[MSG_JOIN_ROOM] = &Server::joinRoom;
    _funcs[MSG_LEAVE_ROOM] = &Server::leaveRoom;
    _funcs[MSG_START_GAME] = &Server::startGame;
    _funcs[MSG_ROOM_LIST] = &Server::roomList;
}

Server::~Server()
{
    release();
}

void Server::init(const std::string &port)
{
    _running = true;
    _socket = new Socket();
    _socket->init(port);
    _threadPool.init();
	Room * r = new Room("New Game");
	_rooms.push_back(r);
}

void Server::release()
{
    _threadPool.release();
    for (std::list<Player *>::iterator it = _players.begin(); it != _players.end(); ++it) {
        delete *it;
    }
    for (std::list<Room *>::iterator it = _rooms.begin(); it != _rooms.end(); ++it) {
        delete *it;
    }
    _players.clear();
    _rooms.clear();
}

void Server::run()
{
    Message msg;
    std::string ip;
    while (_running) {
        ip = "";
        msg.messageType = MSG_IDDLE;
        _socket->recvMsg(msg, ip);
        if (_funcs.find(msg.messageType) != _funcs.end()) {
            (this->*_funcs[msg.messageType])(msg, ip);
        }
    }
}

void Server::startGame(Message &msg, const std::string &ip)
{
    msg.messageType = MSG_START_GAME;
    msg.response = true;
    Player * p = findPlayerByIp(ip);
    if (p == NULL) {
        std::cerr << "cannot find player" << std::endl;
    }
    Room * room = p->currentRoom;
    if (room == NULL || room->isPlaying()) {
        msg.response = false;
        _socket->sendMsg(msg);
        return ;
    }
    room->startGame(_threadPool);
    std::list<Player *> playerList = room->getPlayerList();
    for (std::list<Player *>::iterator it = playerList.begin(); it != playerList.end(); ++it) {
        msg.id = (*it)->getPlayerId();
        _socket->sendMsg(msg);
    }
    msg.messageType = MSG_DELETE_ROOM;
    msg.copyMessage(room->getRoomName().c_str());
    for (std::list<Player *>::iterator it = _players.begin(); it != _players.end(); ++it) {
        if ((*it)->currentRoom == NULL) {
            msg.id = (*it)->getPlayerId();
            _socket->sendMsg(msg);
        }
    }
    _rooms.remove(room);
}

void Server::joinRoom(Message &msg, const std::string &ip)
{
    msg.messageType = MSG_JOIN_ROOM;
    msg.response = true;
    Player * p = findPlayerByIp(ip);
    Room * room = findRoomByName(msg.msg);
    if (room == NULL) {
        msg.response = false;
        _socket->sendMsg(msg);
    }
    if (room->getPlayerList().size() >= 4 || room->isPlaying() == true) {
        msg.response = false;
        _socket->sendMsg(msg);
    }
    else {
        p->currentRoom = room;
        std::list<Player *> playerList = room->getPlayerList();
        _socket->sendMsg(msg);
        
        msg.messageType = MSG_PLAYER_LIST;
        msg.copyMessage(p->getPlayerIp().c_str());
        for (std::list<Player *>::iterator it = playerList.begin(); it != playerList.end(); ++it) {
            msg.id = (*it)->getPlayerId();
            _socket->sendMsg(msg);
        }
        room->addPlayer(p);
        msg.id = p->getPlayerId();
        for (std::list<Player *>::iterator it = room->getPlayerList().begin(); it != room->getPlayerList().end(); ++it) {
            msg.copyMessage((*it)->getPlayerIp().c_str());
            _socket->sendMsg(msg);
        }
    }
    msg.messageType = MSG_IDDLE;
}

void Server::leaveRoom(Message &msg, const std::string &ip)
{
    msg.messageType = MSG_LEAVE_ROOM;
    msg.response = true;
    _socket->sendMsg(msg);
    Player * p = findPlayerByIp(ip);
    Room * room = p->currentRoom;
    p->currentRoom = NULL;
    if (room == NULL) {
        msg.response = false;
        _socket->sendMsg(msg);
        return ;
    }
    std::list<Player *> playerList = room->getPlayerList();
    for (std::list<Player *>::iterator it = playerList.begin(); it != playerList.end(); ++it) {
        msg.id = (*it)->getPlayerId();
        msg.copyMessage(p->name.c_str());
        _socket->sendMsg(msg);
    }
    msg.id = p->getPlayerId();
    msg.messageType = MSG_ROOM_LIST;
    for (std::list<Room *>::iterator it = _rooms.begin(); it != _rooms.end(); ++it) {
        msg.copyMessage((*it)->getRoomName().c_str());
        _socket->sendMsg(msg);
    }
}

void Server::createRoom(Message & msg, std::string const & ip)
{
    msg.messageType = MSG_ROOM_LIST;
    msg.response = true;
    
    if (_rooms.size() >= MAX_ROOM || (findRoomByName(msg.msg) != NULL)) {
        std::cerr << "Cannot creat room" << std::endl;
        Player * p = findPlayerByIp(ip);
        if (p == NULL)
            return ;
        msg.id = p->getPlayerId();
        msg.response = false;
        _socket->sendMsg(msg);
    }
    else {
        Room * r = new Room(msg.msg);
        _rooms.push_back(r);
        for (std::list<Player *>::iterator it = _players.begin(); it != _players.end(); ++it) {
            if ((*it)->currentRoom == NULL) {
                msg.id = (*it)->getPlayerId();
                msg.copyMessage(r->getRoomName().c_str());
                _socket->sendMsg(msg);
            }
        }
    }
}

void Server::createNewPlayer(Message &msg, const std::string &ip)
{
    if (_players.size() >= MAX_PLAYER) {
        msg.response = false;
        _socket->sendMsg(msg);
        return ;
    }
    std::string port = generateNewClientPort();
    Player * p = new Player(msg.id, ip, port);
    p->currentRoom = NULL;
    msg.posX = p->port;
    _socket->sendMsg(msg);
    msg.messageType = MSG_ROOM_LIST;
    for (std::list<Room *>::iterator it = _rooms.begin(); it != _rooms.end(); ++it) {
        msg.copyMessage((*it)->getRoomName().c_str());
        _socket->sendMsg(msg);
    }
    _players.push_back(p);
}

void Server::createPlayer(Message &msg, std::string const & ip)
{
    msg.messageType = MSG_CONNECT;
    msg.response = true;
    Player * p = findPlayerByIp(ip);
    if (p == NULL) {
        createNewPlayer(msg, ip);
    }
    else {
        p->setPlayerId(msg.id);
        _socket->sendMsg(msg);
        msg.messageType = MSG_ROOM_LIST;
        for (std::list<Room *>::iterator it = _rooms.begin(); it != _rooms.end(); ++it) {
            msg.copyMessage((*it)->getRoomName().c_str());
            _socket->sendMsg(msg);
        }
    }
}

void Server::roomList(Message &msg, const std::string &ip)
{
    (void)ip;
    msg.id = MSG_ROOM_LIST;
    for (std::list<Room *>::iterator it = _rooms.begin(); it != _rooms.end(); ++it) {
        msg.copyMessage((*it)->getRoomName().c_str());
        _socket->sendMsg(msg);
    }
}

void Server::disconnectPlayer(Message &msg, const std::string &ip)
{
    (void)msg;
    Player * p = findPlayerByIp(ip);
    if (p->currentRoom != NULL) {
        p->currentRoom->removePlayer(p);
        p->setAlive(false);
    }
}

Room * Server::findRoomByName(const std::string &name)
{
    for (std::list<Room *>::iterator it = _rooms.begin(); it != _rooms.end(); ++it) {
        if ((*it)->getRoomName() == name)
            return *it;
    }
    return NULL;
}

Player * Server::findPlayerByIp(const std::string &ip)
{
    for (std::list<Player *>::iterator it = _players.begin(); it != _players.end(); ++it) {
        if ((*it)->getPlayerIp() == ip) {
            return *it;
        }
    }
    return NULL;
}

std::string Server::generateNewClientPort()
{
    std::stringstream ss;
    std::list<Player *>::iterator it;
    int port;
    bool isTaken = true;
    srand((unsigned)time(NULL));
    while (isTaken == true) {
        port = rand() % 7000 + 1000;
        isTaken = false;
        for (it = _players.begin(); it != _players.end(); ++it) {
            if ((*it)->port == port) {
                isTaken = true;
            }
        }
    }
    ss << port;
    return ss.str();
}


