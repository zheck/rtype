//
//  Client.cpp
//  R-Type
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include <ctime>
#include <sstream>

#include "Client.hpp"
#include "KeyManager.hpp"
#include "SoundManager.hpp"

Client::Client(std::string const & port)
{
    std::stringstream ss;
    
    ss << port;
    ss >> _port;
    _connexionEstablished = false;
    _gameState = MENU;
     _window = new sf::RenderWindow(sf::VideoMode(800, 600), "R-Type", sf::Style::Default, sf::ContextSettings(32));
    _window->setVerticalSyncEnabled(true);
    
    _menu.init();
    _roomSelection.init();
    _inRoom.init();
    _gameEnd.init();
    _socket = new Socket();
    _socketUdp = new SocketUdp();
    _render.init(_window, _roomSelection);
    
    KeyManager::getInstance().init(_window);
    SoundManager::getInstance().init();
    SoundManager::getInstance().playMenu(true);
    _updateFuncs[MENU] = &Client::updateMenu;
    _updateFuncs[ROOM_SELECTION] = &Client::updateRoomSelection;
    _updateFuncs[ROOM] = &Client::updateInRoom;
    _updateFuncs[GAME] = &Client::updateGame;
    _updateFuncs[GAME_WON] = &Client::updateGameEnd;
    _updateFuncs[GAME_LOST] = &Client::updateGameEnd;
    _drawFuncs[MENU] = &Client::drawMenu;
    _drawFuncs[ROOM_SELECTION] = &Client::drawRoomSelection;
    _drawFuncs[ROOM] = &Client::drawInRoom;
    _drawFuncs[GAME] = &Client::drawGame;
    _drawFuncs[GAME_WON] = &Client::drawGameEnd;
    _drawFuncs[GAME_LOST] = &Client::drawGameEnd;
}

Client::~Client()
{
    release();
}

void Client::release()
{
}

void Client::run()
{
    while (_window->isOpen()) {
        _msg.messageType = MSG_IDDLE;
        if (_connexionEstablished && _gameState != GAME) {
            _socket->recvMsg(_msg);
        }
        update();
        if (_msg.messageType != MSG_IDDLE && _gameState != GAME) {
            if (_msg.messageType == MSG_CONNECT) {
                _socket->init(_menu.getInputIp(), _connexionEstablished, _port);
            }
            else {
                _socket->sendMsg(_msg);
            }
        }
        draw();
    }
}

void Client::update()
{
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed ||
            (sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))) {
            _window->close();
        }
    }
    if (_updateFuncs.find(_gameState) != _updateFuncs.end()) {
        (this->*_updateFuncs[_gameState])();
    }
}

void Client::draw()
{
    _window->clear();
    if (_drawFuncs.find(_gameState) != _drawFuncs.end()) {
        (this->*_drawFuncs[_gameState])();
    }
    _window->display();
}

void Client::updateMenu()
{
    if (_msg.messageType == MSG_CONNECT && _msg.response) {
        bool connexion;
        short port = _msg.posX;
        std::string ip = _menu.getInputIp();
        _socketUdp->init(ip, connexion, port);
        _clientId = _msg.id;
        _gameState = ROOM_SELECTION;
        _msg.messageType = MSG_IDDLE;
        SoundManager::getInstance().playFlip();
    }
    else {
        _menu.update(_event, _clock, _msg);
    }
}

void Client::updateRoomSelection()
{
    if (_msg.messageType == MSG_JOIN_ROOM && _msg.response) {
        _gameState = ROOM;
        _msg.messageType = MSG_IDDLE;
        SoundManager::getInstance().playFlip();
        _roomSelection.clear();
    }
    else {
        _roomSelection.update(_event, _clock, _msg);
    }
}

void Client::updateInRoom()
{
    if (_msg.messageType == MSG_START_GAME && _msg.response) {
        _inRoom.setUserInteraction(true);
        _gameState = GAME;
        _game.release();
        _game.init(_clientId);
        _msg.messageType = MSG_IDDLE;
        _gameTime = 0;
        _t.reset();
        _inRoom.clear();
        SoundManager::getInstance().playMenu(false);
        SoundManager::getInstance().playGame(true);
    }
    else if (_msg.messageType == MSG_LEAVE_ROOM && _msg.response) {
        _gameState = ROOM_SELECTION;
        _msg.messageType = MSG_IDDLE;
    }
    else {
        _inRoom.update(_event, _clock, _msg);
    }
}

void Client::updateGame()
{
    _msg.messageType = MSG_IDDLE;
    while (_t.getElapsedTime() - _gameTime < GAME_TIME_UNIT) {
        _socketUdp->recvMsg(_msg);
        if (_msg.messageType == MSG_WON || _msg.messageType == MSG_LOST) {
            _gameState = _msg.messageType == MSG_WON ? GAME_WON : GAME_LOST;
            SoundManager::getInstance().playGame(false);
            _lastGameDuration = _gameTime;
            _msg.messageType = MSG_IDDLE;
            return ;
        }
        _game.updateMap(_msg);
    }
    _msg.entity = PLAYER;
    _gameTime = _t.getElapsedTime();
    _game.update(_event, _clock, _msg);
    _msg.time = _gameTime;
    _socketUdp->sendMsg(_msg);
    _msg.messageType = MSG_IDDLE;
}

void Client::updateGameEnd()
{
    if (_t.getElapsedTime() - _lastGameDuration < 2000) {
        while (_t.getElapsedTime() - _gameTime < GAME_TIME_UNIT) {
            _socketUdp->recvMsg(_msg);
        }
    }
    else {
        _gameEnd.update(_event, _clock, _msg);
        if (_msg.messageType == MSG_ROOM_LIST) {
            _game.release();
            _msg.messageType = MSG_ROOM_LIST;
            _gameState = ROOM_SELECTION;
            return ;
        }
    }
    _gameTime = _t.getElapsedTime();
    _msg.messageType = MSG_IDDLE;
}

void Client::drawMenu()
{
    _render.drawMenu(_menu);
}

void Client::drawRoomSelection()
{
    _render.drawRoomSelection(_roomSelection);
}

void Client::drawInRoom()
{
    _render.drawRoom(_inRoom);
}

void Client::drawGame()
{
    _render.drawGame(_game.getEntities());
}

void Client::drawGameEnd()
{
    _render.drawGame(_game.getEntities());
    _render.drawGameEnd(_gameState);
}
