//
//  PlayerRender.h
//  xCodeClient
//
//  Created by Zhou Fong on 11/15/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__PlayerRender__
#define __xCodeClient__PlayerRender__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class PlayerRender
{
    sf::RenderWindow *_window;
    sf::Texture _playerImg;
    sf::Sprite _playerSprite;
    sf::Texture _deathImg;
    sf::Sprite _deathSprite;
    std::vector<sf::IntRect> _deathRect;
    sf::Texture _menuSpaceShipImg;
    sf::Sprite _menuSpaceShipSprite;
    std::vector<sf::IntRect> _playerSpriteRect;
    std::vector<sf::Texture> _fireImg;
    sf::Sprite _fireSprite;
    int _imgSwapTime;
    
public:
    PlayerRender();
    PlayerRender(PlayerRender const & rhs);
    ~PlayerRender();
    
    PlayerRender & operator=(PlayerRender const & rhs);
    
    void init(sf::RenderWindow * window);
    void draw(Entity const & e);
};

#endif /* defined(__xCodeClient__PlayerRender__) */
