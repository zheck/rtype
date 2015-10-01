//
//  GameEnd.cpp
//  xCodeClient
//
//  Created by Zhou Fong on 11/18/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "GameEnd.hpp"

#include "GameEnd.hpp"
#include "KeyManager.hpp"
#include "SoundManager.hpp"

GameEnd::GameEnd()
{}

GameEnd::~GameEnd()
{}

void GameEnd::init()
{
    sf::IntRect startGame(300, 400, 200, 40);
    _startGameRect = startGame;
    _time = 0;
}

void GameEnd::clear()
{
    _listPlayer.clear();
}

void GameEnd::update(const sf::Event &event, const ClockManager &clock, Message &msg)
{
    (void)event;
    if (clock.getElapsedTime() - _time < 0.10) {
        return ;
    }
    msg.messageType = MSG_IDDLE;
    if (KeyManager::getInstance().isMouseButtonPressed(_startGameRect)) {
        _time = clock.getElapsedTime();
        msg.messageType = MSG_ROOM_LIST;
        SoundManager::getInstance().playClick();
        SoundManager::getInstance().playMenu(true);
        SoundManager::getInstance().playEndGame(false);
    }
}

std::list<std::string> GameEnd::getListPlayer() const
{
    return _listPlayer;
}

sf::IntRect GameEnd::getStartGameRect() const
{
    return _startGameRect;
}
