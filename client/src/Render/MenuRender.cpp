//
//  MenuRender.cpp
//  xCodeClient
//
//  Created by mo_r on 13/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "ResourcePath.hpp"
#include "MenuRender.hpp"

MenuRender::MenuRender()
{}

MenuRender::~MenuRender()
{}

void MenuRender::init(sf::RenderWindow * window)
{
    _window = window;
    if (!_bgImg.loadFromFile(resourcePath() + "space.png") ||
        !_loginImg.loadFromFile(resourcePath() + "login.png") ||
        !_menuSpaceShipImg.loadFromFile(resourcePath() + "menuSpaceShip.png"))
    {
        std::cerr << "can't find" << std::endl;
        return;
    }
    
    sf::Sprite bgSprite(_bgImg);
    sf::Sprite loginSprite(_loginImg);
    sf::Sprite menuSpaceShipSprite(_menuSpaceShipImg);
    _bgSprite = bgSprite;
    _loginSprite = loginSprite;
    _loginSprite.setPosition(WINX/4, WINY/4);
    _menuSpaceShipSprite = menuSpaceShipSprite;
    _menuSpaceShipSprite.setPosition(WINX/4 + 5, WINY/4 + 93);
    if (!_starcraftTtf.loadFromFile(resourcePath() + "starcraft.ttf") ||
        !_sansationTtf.loadFromFile(resourcePath() + "sansation.ttf"))
    {
        return;
    }
    _title.setString("R-TYPE");
    _title.setFont(_starcraftTtf);
    _title.setCharacterSize(50);
    _title.setColor(sf::Color::White);
    _title.setPosition(WINX/2 - 110, 20);
    
    _userName.setString("Username");
    _userName.setFont(_starcraftTtf);
    _userName.setCharacterSize(15);
    _userName.setColor(sf::Color::White);
    _userName.setPosition(WINX/4 + 58, WINY/4 + 70);
    
    _serverAdress.setString("Server Adress");
    _serverAdress.setFont(_starcraftTtf);
    _serverAdress.setCharacterSize(15);
    _serverAdress.setColor(sf::Color::White);
    _serverAdress.setPosition(WINX/4 + 58, WINY/2 + 5);
    
    _userNameInput.setFont(_sansationTtf);
    _userNameInput.setCharacterSize(20);
    _userNameInput.setColor(sf::Color::Black);
    _userNameInput.setPosition(WINX/4 + 65, WINY/4 + 100);
    
    _serverAdressInput.setFont(_sansationTtf);
    _serverAdressInput.setCharacterSize(20);
    _serverAdressInput.setColor(sf::Color::Black);
    _serverAdressInput.setPosition(WINX/4 + 64, WINY/2 + 33);
}

void MenuRender::draw(const Menu &menu)
{
    _userNameInput.setString(menu.getInputUser());
    _serverAdressInput.setString(menu.getInputIp());
    _menuSpaceShipSprite.setPosition(menu.getCursorPos().x, menu.getCursorPos().y);
    _window->draw(_bgSprite);
    _window->draw(_loginSprite);
    _window->draw(_menuSpaceShipSprite);
    _window->draw(_title);
    _window->draw(_userName);
    _window->draw(_serverAdress);
    _window->draw(_userNameInput);
    _window->draw(_serverAdressInput);
}
