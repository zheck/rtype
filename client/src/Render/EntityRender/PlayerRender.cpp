//
//  PlayerRender.cpp
//  xCodeClient
//
//  Created by Zhou Fong on 11/15/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "PlayerRender.hpp"
#include "ResourcePath.hpp"
#include "Defines.hpp"

PlayerRender::PlayerRender()
{}

PlayerRender::~PlayerRender()
{}

void PlayerRender::init(sf::RenderWindow * window)
{
    _window = window;
    _imgSwapTime = 0;
    for (int i = 0; i < 12; ++i) {
        sf::Texture texture;
        _fireImg.push_back(texture);
    }
    if (!_playerImg.loadFromFile(resourcePath() + "r-typesheet23.gif") ||
        !_deathImg.loadFromFile(resourcePath() + "r-typesheet44-2.gif") ||
        !_fireImg[0].loadFromFile(resourcePath() + "fire-1.png") ||
        !_fireImg[1].loadFromFile(resourcePath() + "fire-2.png") ||
        !_fireImg[2].loadFromFile(resourcePath() + "fire-3.png") ||
        !_fireImg[3].loadFromFile(resourcePath() + "fire-4.png") ||
        !_fireImg[4].loadFromFile(resourcePath() + "fire-5.png") ||
        !_fireImg[5].loadFromFile(resourcePath() + "fire-6.png") ||
        !_fireImg[6].loadFromFile(resourcePath() + "fire-7.png") ||
        !_fireImg[7].loadFromFile(resourcePath() + "fire-8.png") ||
        !_fireImg[8].loadFromFile(resourcePath() + "fire-9.png") ||
        !_fireImg[9].loadFromFile(resourcePath() + "fire-10.png") ||
        !_fireImg[10].loadFromFile(resourcePath() + "fire-11.png") ||
        !_fireImg[11].loadFromFile(resourcePath() + "fire-12.png")) {
         std::cerr << "An error occured while loading image from file." << std::endl;
     }
    int x = 0;
    for (int i=0; i < 8; ++i) {
        sf::IntRect rect(x, PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE);
        _playerSpriteRect.push_back(rect);
        x += PLAYER_SIZE;
    }
    _playerImg.setSmooth(true);
    _playerSprite.setTexture(_playerImg);
    _playerSprite.setTextureRect(_playerSpriteRect[5]);
    
    _deathSprite.setTexture(_deathImg);
    
    x = 0;
    for (int i = 0; i < 5; ++i) {
        sf::IntRect rect(x, 44, EXPLOSION_SIZE, EXPLOSION_SIZE);
        _deathRect.push_back(rect);
        x += EXPLOSION_SIZE;
    }
}

void PlayerRender::draw(Entity const & e)
{
    if (e.isAlive() == false &&  e.deathTime < 1000) {
        int index = e.deathTime * 5 / 1000;
        _deathSprite.setPosition(static_cast<float>(e.position.x), static_cast<float>(e.position.y));
        _deathSprite.setTextureRect(_deathRect[index]);
        _window->draw(_deathSprite);
    }
    else if (e.isAlive() == true) {
        if (_imgSwapTime >= 60)
            _imgSwapTime = 0;
        int i = _imgSwapTime * 6 / 60;
        _fireSprite.setTexture(_fireImg[i]);
        _fireSprite.setPosition(static_cast<float>(e.position.x) - 29, static_cast<float>(e.position.y));
        _playerSprite.setPosition(static_cast<float>(e.position.x), static_cast<float>(e.position.y));
        _window->draw(_fireSprite);
        _window->draw(_playerSprite);
        ++_imgSwapTime;
    }
}
