//
//  Client.h
//  R-Type
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_Type__Client__
#define __R_Type__Client__

#include <iostream>
#include <SFML/Window.hpp>
#include "ISocket.hpp"
#include "Message.hpp"
#include "Render.hpp"
#include "Menu.hpp"
#include "ClockManager.hpp"
#include "RoomSelection.hpp"
#include "InRoom.hpp"
#include "Game.hpp"
#include "GameTime.hpp"
#include "GameEnd.hpp"

#ifdef _WIN32
#include <SFML/Graphics/RenderWindow.hpp>
#endif

class Client {
    ISocket *_socket;
    ISocket *_socketUdp;
    sf::RenderWindow * _window;
    sf::Event _event;
    ClockManager _clock;
    Message _msg;
    eGameState _gameState;
    int _port;
    
    Render _render;
    Menu _menu;
    RoomSelection _roomSelection;
    InRoom _inRoom;
    Game _game;
    GameEnd _gameEnd;
    
    int _clientId;
    std::string _serverIp;
    int _gameTime;
    int _lastGameDuration;
    GameTime _t;
    
    std::map<eGameState, void(Client::*)()> _updateFuncs;
    std::map<eGameState, void(Client::*)()> _drawFuncs;
    bool _connexionEstablished;
    
public:
    Client(std::string const & port);
    Client(Client const & rhs);
    ~Client();
    
    Client & operator=(Client const & rhs);

    void release();
    void run();
    
private:
    void update();
    void draw();
    
    void updateMenu();
    void updateRoomSelection();
    void updateInRoom();
    void updateGame();
    void updateGameEnd();
    
    void drawMenu();
    void drawRoomSelection();
    void drawInRoom();
    void drawGame();
    void drawGameEnd();
};

#endif /* defined(__R_Type__Client__) */
