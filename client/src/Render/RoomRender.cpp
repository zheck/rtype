//
//  RoomRender.cpp
//  xCodeClient
//
//  Created by mo_r on 13/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "ResourcePath.hpp"
#include "RoomRender.hpp"

RoomRender::RoomRender()
{}

RoomRender::~RoomRender()
{}

void RoomRender::init(sf::RenderWindow *window)
{
    _window = window;
    _roomBgPos.x = -500;
    _roomBgPos.y = WINY/5;
    if (!_starcraftTtf.loadFromFile(resourcePath() + "starcraft.ttf") ||
        !_sansationTtf.loadFromFile(resourcePath() + "sansation.ttf") ||
        !_bgImg.loadFromFile(resourcePath() + "space.png") ||
        
        !_roomBgImg.loadFromFile(resourcePath() + "room.png") ||
        !_startGameImg.loadFromFile(resourcePath() + "startGameButton.png")) {
        std::cerr << "can't find room image" << std::endl;
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
    
    _startGamePos.x = -350;
    _startGamePos.y = 420;
    _startGameSprite.setTexture(_startGameImg);
    _startGameSprite.setPosition(_startGamePos.x, _startGamePos.y);
    
    _startGameTitle.setString("Start Game");
    _startGameTitle.setFont(_starcraftTtf);
    _startGameTitle.setColor(sf::Color::Black);
    _startGameTitle.setCharacterSize(20);
    
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
    
    _usernameList.push_back(&username);
    _usernameList.push_back(&username2);
    _usernameList.push_back(&username3);
    _usernameList.push_back(&username4);
}

void RoomRender::draw(InRoom & inRoom)
{
    if (_roomBgPos.x < (WINX/5 - 10)) {
        _roomBgPos.x += SCROLL_SPEED;
        _roomBgSprite.setPosition(_roomBgPos.x, _roomBgPos.y);
    }
    
    if (_startGamePos.x < 300) {
        _startGamePos.x += SCROLL_SPEED;
        _startGameSprite.setPosition(_startGamePos.x, _startGamePos.y);
        _startGameTitle.setPosition(_startGamePos.x + 20, _startGamePos.y + 7);
        _playerListTitle.setPosition(_startGamePos.x, 180);
    }
    _window->draw(_bgSprite);
    _window->draw(_title);
    _window->draw(_roomBgSprite);
    _window->draw(_startGameSprite);
    _window->draw(_startGameTitle);
    _window->draw(_playerListTitle);

    username.setString("player 1");
    username2.setString("Player 2");
    username3.setString("player 3");
    username4.setString("Player 4");
    username.setFont(_sansationTtf);
    username2.setFont(_sansationTtf);
    username3.setFont(_sansationTtf);
    username4.setFont(_sansationTtf);
    username.setColor(sf::Color::White);
    username2.setColor(sf::Color::White);
    username3.setColor(sf::Color::White);
    username4.setColor(sf::Color::White);
    username.setCharacterSize(15);
    username2.setCharacterSize(15);
    username3.setCharacterSize(15);
    username4.setCharacterSize(15);
    
    if (_playerNamePos.x < 400) {
        _playerNamePos.x += SCROLL_SPEED;
        float diff = 3.5 * 8;
        float diff2 = 3.5 * 15;
        float diff3 = 3.5 * 20;
        username.setPosition(_playerNamePos.x - diff, 240);
        username2.setPosition(_playerNamePos.x - diff2, 270);
        username3.setPosition(_playerNamePos.x - diff3, 300);
        username4.setPosition(_playerNamePos.x - diff3, 330);
    }
    std::list<std::string> * playerList = inRoom.getListPlayer();
    int i = 0;
    for (std::list<std::string>::iterator it = playerList->begin(); it != playerList->end(); ++it) {
        _window->draw(*_usernameList[i++]);
    }
}
