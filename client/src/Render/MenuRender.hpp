//
//  MenuRender.h
//  xCodeClient
//
//  Created by mo_r on 13/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__MenuRender__
#define __xCodeClient__MenuRender__

#include <SFML/Graphics.hpp>

#include "Menu.hpp"
#include "Defines.hpp"

class MenuRender
{
    sf::RenderWindow * _window;
    sf::Texture _bgImg;
    sf::Texture _loginImg;
    sf::Texture _menuSpaceShipImg;
    sf::Sprite _bgSprite;
    sf::Sprite _loginSprite;
    sf::Sprite _menuSpaceShipSprite;
    sf::Text _title;
    sf::Font _starcraftTtf;
    sf::Font _sansationTtf;

    sf::Text _userName;
    sf::Text _userNameInput;
    sf::Text _serverAdress;
    sf::Text _serverAdressInput;
    std::string _serverAdressStr;
    std::string _userNameStr;

public:
    MenuRender();
    MenuRender(MenuRender const & rhs);
    ~MenuRender();

    MenuRender & operator=(MenuRender const & rhs);
    
    void init(sf::RenderWindow * window);
    void draw(Menu const & menu);
};

#endif /* defined(__xCodeClient__MenuRender__) */
