//
//  InRoom.cpp
//  xCodeClient
//
//  Created by mo_r on 10/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "InRoom.hpp"
#include "KeyManager.hpp"
#include "SoundManager.hpp"

InRoom::InRoom()
{
    _userInteractionEnabled = true;
}

InRoom::~InRoom()
{}

void InRoom::init()
{
    sf::IntRect startGame(310, 420, 200, 40);
    _startGameRect = startGame;
    _listPlayer.clear();
    _time = 0;
}

void InRoom::clear()
{
    _listPlayer.clear();
}

void InRoom::update(const sf::Event &event, const ClockManager &clock, Message &msg)
{
    (void)event;
    if (clock.getElapsedTime() - _time < 0.10) {
        return ;
    }
    if (msg.messageType == MSG_PLAYER_LIST) {
        for (std::list<std::string>::iterator it = _listPlayer.begin(); it != _listPlayer.end(); ++it) {
            if (*it == msg.msg) {
                break ;
            }
        }
        _listPlayer.push_back(msg.msg);
    }
    else if (msg.messageType == MSG_LEAVE_ROOM) {
        for (std::list<std::string>::iterator it = _listPlayer.begin(); it != _listPlayer.end(); ++it) {
            if (*it == msg.msg) {
                _listPlayer.erase(it);
            }
        }
    }
    msg.messageType = MSG_IDDLE;
    if (KeyManager::getInstance().isMouseButtonPressed(_startGameRect) && _userInteractionEnabled == true) {
        _userInteractionEnabled = false;
        _time = clock.getElapsedTime();
        SoundManager::getInstance().playClick();
        msg.messageType = MSG_START_GAME;
    }
    else if (KeyManager::getInstance().isKeyPressed(Keyboard::Escape)) {
        _time = clock.getElapsedTime();
        msg.messageType = MSG_LEAVE_ROOM;
    }
}

void InRoom::setUserInteraction(bool b)
{
    _userInteractionEnabled = b;
}

std::list<std::string> * InRoom::getListPlayer()
{
    return &_listPlayer;
}

sf::IntRect InRoom::getStartGameRect() const
{
    return _startGameRect;
}
