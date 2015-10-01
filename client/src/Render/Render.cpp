//
//  Render.cpp
//  R-Type
//
//  Created by mo_r on 21/10/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#include "Render.hpp"

Render::Render()
{}

Render::~Render()
{}

void Render::init(sf::RenderWindow * window, RoomSelection const & roomSelection)
{
    _menuRender.init(window);
    _roomSelectionRender.init(window, roomSelection);
    _roomRender.init(window);
    _gameRender.init(window);
    _gameEndRender.init(window);
}

void Render::drawMenu(Menu const & menu)
{
    _menuRender.draw(menu);
}

void Render::drawRoomSelection(RoomSelection const & roomSelection)
{
    _roomSelectionRender.draw(roomSelection);
}

void Render::drawRoom(InRoom & inRoom)
{
    _roomRender.draw(inRoom);
}

void Render::drawGameEnd(eGameState const & gameState) {
    _gameEndRender.draw(gameState);
}

void Render::drawGame(std::map<int, Entity *> & entities)
{
    _gameRender.draw(entities);
}
