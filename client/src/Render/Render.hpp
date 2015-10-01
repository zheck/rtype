//
//  Render.h
//  R-Type
//
//  Created by mo_r on 21/10/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_Type__Render__
#define __R_Type__Render__

#include "Menu.hpp"
#include "RoomSelection.hpp"
#include "InRoom.hpp"
#include "Game.hpp"
#include "MenuRender.hpp"
#include "RoomSelectionRender.hpp"
#include "RoomRender.hpp"
#include "GameRender.hpp"
#include "GameEndRender.hpp"

class Render
{
    MenuRender _menuRender;
    RoomSelectionRender _roomSelectionRender;
    RoomRender _roomRender;
    GameRender _gameRender;
    GameEndRender _gameEndRender;
    
public:
    Render();
    Render(Render const & rhs);
    ~Render();
    
    Render & operator=(Render const & render);
    
    void init(sf::RenderWindow * window, RoomSelection const & roomSelection);
    void drawMenu(Menu const & menu);
    void drawRoomSelection(RoomSelection const & roomSelection);
    void drawRoom(InRoom & inRoom);
    void drawGame(std::map<int, Entity *> & entities);
    void drawGameEnd(eGameState const & gameState);
};

#endif /* defined(__R_Type__Render__) */
