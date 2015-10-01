//
//  BulletRender.cpp
//  xCodeClient
//
//  Created by Zhou Fong on 11/16/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "BulletRender.hpp"

#include "ResourcePath.hpp"
#include "Defines.hpp"

BulletRender::BulletRender()
{}

BulletRender::~BulletRender()
{}

void BulletRender::init(sf::RenderWindow * window)
{
    int x = 136;
    int y = 4;
    _window = window;
    if (!_bulletImg.loadFromFile(resourcePath() + "r-typesheet43.gif")) {
        std::cout << "bullet sprite not found" << std::endl;
    }
    for (int i = 0; i < 8; ++i) {
        sf::IntRect rect(x, y, BULLET_SIZE, BULLET_SIZE);
        _bulletSpriteRect.push_back(rect);
        x += (BULLET_SIZE * 2);
    }
    _bulletImg.setSmooth(true);
    _bulletSprite.setTexture(_bulletImg);
    _bulletSprite.setTextureRect(_bulletSpriteRect[1]);
}

void BulletRender::draw(Entity const & e)
{
    if (e.isAlive()) {
        _bulletSprite.setPosition(e.position.x, e.position.y);
        _window->draw(_bulletSprite);
    }
}