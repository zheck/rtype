//
//  MinionRender.cpp
//  xCodeClient
//
//  Created by Zhou Fong on 11/16/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "MinionRender.hpp"

#include "ResourcePath.hpp"
#include "Defines.hpp"
#include "SoundManager.hpp"

MinionRender::MinionRender() :
_deathTime(0)
{}

MinionRender::~MinionRender()
{}

void MinionRender::init(sf::RenderWindow * window)
{
    _window = window;
    if (!_minionImg.loadFromFile(resourcePath() + "r-typesheet12.gif") ||
        !_deathImg.loadFromFile(resourcePath() + "r-typesheet44-2.gif")) {
        std::cout << "Minion image not found" << std::endl;
    }
    int x = 0;
    for (int i = 0; i < 3; ++i) {
        sf::IntRect rect(x, 0, MINION1_WIDTH, MINION1_HEIGHT);
        _minionSpriteRect.push_back(rect);
        x += MINION1_WIDTH;
    }
    _minionImg.setSmooth(true);
    _minionSprite.setTexture(_minionImg);
    _minionSprite.setTextureRect(_minionSpriteRect[0]);
    _deathSprite.setTexture(_deathImg);
    
    x = 0;
    for (int i = 0; i < 5; ++i) {
        sf::IntRect rect(x, 44, EXPLOSION_SIZE, EXPLOSION_SIZE);
        _deathRect.push_back(rect);
        x += EXPLOSION_SIZE;
    }
}

void MinionRender::draw(Entity const & e)
{
    if (e.isAlive() == false &&  e.deathTime < 1000) {
        int index = e.deathTime * 5 / 1000;
        _deathSprite.setPosition(static_cast<float>(e.position.x), static_cast<float>(e.position.y));
        _deathSprite.setTextureRect(_deathRect[index]);
        _window->draw(_deathSprite);
    }
    else if (e.isAlive() == true) {
        _minionSprite.setPosition(static_cast<float>(e.position.x), static_cast<float>(e.position.y));
        _window->draw(_minionSprite);
    }
}