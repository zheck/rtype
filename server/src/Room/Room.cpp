//
//  Room.cpp
//  R-TypeServer
//
//  Created by Zhou Fong on 10/14/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "Room.hpp"

Room::Room(std::string const & roomName) :
_roomName(roomName),
_game(roomName),
_playing(false)
{}

Room::~Room()
{
    _game.release();
}
void Room::startGame(ThreadPool & tp)
{
    _game.init(_playerList);
    _game.setDelegate(this);
    _playing = true;
    tp.addTask(new Task(&runGame, &_game));
}

void Room::addPlayer(Player *p)
{
    _playerList.push_back(p);
}

void Room::removePlayer(Player *p)
{
    _playerList.remove(p);
    p->currentRoom = NULL;
}

std::string & Room::getRoomName()
{
    return _roomName;
}

std::list<Player *> & Room::getPlayerList()
{
    return _playerList;
}

bool Room::isPlaying() const
{
    return _playing;
}

void runGame(void * data)
{
    Game * game = static_cast<Game *>(data);
    game->start();
}
