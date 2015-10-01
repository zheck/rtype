//
//  Minion2Render.cpp
//  xCodeClient
//
//  Created by mo_r on 24/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "Minion2Render.hpp"
#include "ResourcePath.hpp"
#include "Defines.hpp"
#include "SoundManager.hpp"

Minion2Render::Minion2Render() :
_deathTime(0)
{}

Minion2Render::~Minion2Render()
{}

void Minion2Render::init(sf::RenderWindow * window)
{
    _window = window;
    if (!_minionImg.loadFromFile(resourcePath() + "r-typesheet11.gif") ||
        !_deathImg.loadFromFile(resourcePath() + "r-typesheet44-2.gif")) {
        std::cout << "Minion image not found" << std::endl;
    }

    sf::IntRect rect(0, 0, 33, 33);
    _minionSpriteRect.push_back(rect);

    _minionImg.setSmooth(true);
    _minionSprite.setTexture(_minionImg);
    _minionSprite.setTextureRect(_minionSpriteRect[0]);
    _deathSprite.setTexture(_deathImg);
    
    int x = 0;
    for (int i = 0; i < 5; ++i) {
        sf::IntRect rect(x, 44, EXPLOSION_SIZE, EXPLOSION_SIZE);
        _deathRect.push_back(rect);
        x += EXPLOSION_SIZE;
    }
}

void Minion2Render::draw(Entity const & e)
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