//
//  GameEndRender.cpp
//  xCodeClient
//
//  Created by Zhou Fong on 11/23/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "ResourcePath.hpp"
#include "GameEndRender.hpp"

GameEndRender::GameEndRender()
{}

GameEndRender::~GameEndRender()
{}

void GameEndRender::init(sf::RenderWindow *window)
{
    _window = window;
    _roomBgPos.x = -500;
    _roomBgPos.y = WINY/5;
    if (!_starcraftTtf.loadFromFile(resourcePath() + "starcraft.ttf") ||
        !_sansationTtf.loadFromFile(resourcePath() + "sansation.ttf") ||
        !_bgImg.loadFromFile(resourcePath() + "space.png") ||
        !_roomBgImg.loadFromFile(resourcePath() + "room.png") ||
        !_startGameImg.loadFromFile(resourcePath() + "startGameButton.png") ||
        !_youLostImg.loadFromFile(resourcePath() + "youLost.png") ||
        !_victoryImg.loadFromFile(resourcePath() + "victory.png")) {
        std::cerr << "can't find end game images" << std::endl;
        return;
    }
    
    sf::Sprite bgSprite(_bgImg);
    _bgSprite = bgSprite;
    _title.setString("R-TYPE");
    _title.setFont(_starcraftTtf);
    _title.setCharacterSize(50);
    _title.setColor(sf::Color::White);
    _title.setPosition(WINX/2 - 110, 20);
    
    sf::Sprite roomBgSprite(_roomBgImg);
    _roomBgSprite = roomBgSprite;
    _roomBgSprite.setPosition(_roomBgPos.x, _roomBgPos.y);
    
    
    _startGamePos.x = 300;
    _startGamePos.y = 400;
    _startGameSprite.setTexture(_startGameImg);
    _startGameSprite.setPosition(_startGamePos.x, _startGamePos.y);
    
    _restartTitle.setString("R E S T A R T");
    _restartTitle.setFont(_starcraftTtf);
    _restartTitle.setCharacterSize(20);
    _restartTitle.setColor(sf::Color::Black);
    _restartTitle.setPosition(_startGamePos.x + 15, _startGamePos.y + 6);

    
    sf::Color orange(221,170,50);
    _playerListTitlePos.x = -350;
    _playerListTitlePos.y = 100;
    _playerListTitle.setString("Player    list");
    _playerListTitle.setColor(orange);
    _playerListTitle.setFont(_starcraftTtf);
    _playerListTitle.setPosition(_playerListTitlePos.x, _playerListTitlePos.y);
    _playerListTitle.setCharacterSize(20);
    
    _playerNamePos.x = -250;
    _playerNamePos.y = 240;
    _playerName.setColor(sf::Color::White);
    _playerName.setFont(_sansationTtf);
    _playerName.setCharacterSize(15);
    
    _endGameSprite.setPosition(170, 200);
}

void GameEndRender::draw(eGameState const & gameState)
{
    gameState == GAME_LOST? _endGameSprite.setTexture(_youLostImg): _endGameSprite.setTexture(_victoryImg);
    _window->draw(_startGameSprite);
    _window->draw(_restartTitle);
    _window->draw(_endGameSprite);
}
