//
//  ShockWave.cpp
//  xCodeClient
//
//  Created by Zhou Fong on 11/19/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "ShockWaveRender.hpp"

#include "ResourcePath.hpp"
#include "Defines.hpp"

ShockWaveRender::ShockWaveRender() :
_animation(0)
{
}

ShockWaveRender::~ShockWaveRender()
{}

void ShockWaveRender::init(sf::RenderWindow * window)
{
    _window = window;
    if (!_ShockWaveImg.loadFromFile(resourcePath() + "r-typesheet1.gif")) {
        std::cout << "ShockWave sprite not found" << std::endl;
    }
    sf::IntRect rect5(183, 170, 82, 15);
    _ShockWaveSpriteRect.push_back(rect5);
    _ShockWaveImg.setSmooth(true);
    _ShockWaveSprite.setTexture(_ShockWaveImg);
    _ShockWaveSprite.setTextureRect(_ShockWaveSpriteRect[0]);	
}

void ShockWaveRender::draw(Entity const & e)
{
    if (e.isAlive()) {
        _ShockWaveSprite.setPosition(e.position.x, e.position.y);
        _window->draw(_ShockWaveSprite);
    }
}