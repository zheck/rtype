//
//  File.cpp
//  xCodeClient
//
//  Created by mo_r on 23/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "MegaAttackRender.hpp"

#include "MegaAttackRender.hpp"

#include "ResourcePath.hpp"
#include "Defines.hpp"

MegaAttackRender::MegaAttackRender() :
_animation(0)
{
}

MegaAttackRender::~MegaAttackRender()
{}

void MegaAttackRender::init(sf::RenderWindow * window)
{
    _window = window;
    if (!_ShockWaveImg.loadFromFile(resourcePath() + "r-typesheet1.gif")) {
        std::cout << "ShockWave sprite not found" << std::endl;
    }
    sf::IntRect rect5(208, 190, 55, 50);
    _ShockWaveSpriteRect.push_back(rect5);
    _ShockWaveImg.setSmooth(true);
    _ShockWaveSprite.setTexture(_ShockWaveImg);
    _ShockWaveSprite.setTextureRect(_ShockWaveSpriteRect[0]);
}

void MegaAttackRender::draw(Entity const & e)
{
    if (e.isAlive()) {
        _ShockWaveSprite.setPosition(e.position.x, e.position.y);
        _window->draw(_ShockWaveSprite);
    }
}