//
//  GameRender.cpp
//  xCodeClient
//
//  Created by mo_r on 13/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "ResourcePath.hpp"
#include "GameRender.hpp"

GameRender::GameRender() :
_bgScrollingX(0),
_bgSprite2InitX(WINX)
{
    _drawFuncs[PLAYER] = &GameRender::drawPlayer;
    _drawFuncs[BULLET] = &GameRender::drawBullet;
    _drawFuncs[MINION] = &GameRender::drawMinion;
    _drawFuncs[SHOCK_WAVE] = &GameRender::drawShockWave;
    _drawFuncs[BOSS] = &GameRender::drawBoss;
    _drawFuncs[ASTEROID] = &GameRender::drawAsteroid;
    _drawFuncs[MEGA_ATTACK] = &GameRender::drawMegaAttack;
    _drawFuncs[MINION2] = &GameRender::drawMinion2;
}

GameRender::~GameRender()
{}

void GameRender::init(sf::RenderWindow *window)
{
    _window = window;
    _player.init(window);
    _bullet.init(window);
    _minion.init(window);
    _shockWave.init(window);
    _megaAttack.init(window);
    _bossRender.init(window);
    _asteroidRender.init(window);
    _minion2.init(window);
    
    if (!_bgImg.loadFromFile(resourcePath() + "gameBackground3.png") ||
        !_bgImg2.loadFromFile(resourcePath() + "gameBackground2.png")) {
        std::cout << "can't find game render images" << std::endl;
    }
    sf::Sprite bgSprite(_bgImg);
    sf::Sprite bgSprite2(_bgImg2);
    _bgSprite1 = bgSprite;
    _bgSprite2 = bgSprite;
    _bgSprite3 = bgSprite2;
    _bgSprite4 = bgSprite2;
    _bgSprite2.setPosition(WINX, 0);
    _bgSprite4.setPosition(WINX, 0);
}

void GameRender::draw(std::map<int, Entity *> & entities) {
    if (_bgSprite1.getPosition().x <= -WINX) {
        _bgSprite1.setPosition(WINX, 0);
    }
    else {
        _bgSprite1.setPosition(_bgSprite1.getPosition().x - BACKGROUND_SCROLL_UNIT * 1.5, 0);
    }
    if (_bgSprite2.getPosition().x <= -WINX) {
        _bgSprite2.setPosition(WINX, 0);
    }
    else {
        _bgSprite2.setPosition(_bgSprite2.getPosition().x - BACKGROUND_SCROLL_UNIT * 1.5, 0);
    }
    
    if (_bgSprite3.getPosition().x == -WINX) {
        _bgSprite3.setPosition(WINX, 0);
    }
    else {
        _bgSprite3.setPosition(_bgSprite3.getPosition().x - (BACKGROUND_SCROLL_UNIT), 0);
    }
    if (_bgSprite4.getPosition().x == -WINX) {
        _bgSprite4.setPosition(WINX, 0);
    }
    else {
        _bgSprite4.setPosition(_bgSprite4.getPosition().x - (BACKGROUND_SCROLL_UNIT), 0);
    }
    _window->draw(_bgSprite3);
    _window->draw(_bgSprite4);
    _window->draw(_bgSprite1);
    _window->draw(_bgSprite2);

    for (std::map<int, Entity *>::iterator it = entities.begin(); it != entities.end(); ++it) {
        if (_drawFuncs.find(it->second->getType()) != _drawFuncs.end()) {
            (this->*_drawFuncs[it->second->getType()])(*(it->second));
        }
    }
}

void GameRender::drawAsteroid(const Entity &e)
{
    _asteroidRender.draw(e);
}

void GameRender::drawBoss(const Entity &e)
{
    _bossRender.draw(e);
}

void GameRender::drawBullet(const Entity &e)
{
    _bullet.draw(e);
}

void GameRender::drawShockWave(const Entity &e)
{
    _shockWave.draw(e);
}

void GameRender::drawMegaAttack(const Entity &e)
{
    _megaAttack.draw(e);
}

void GameRender::drawPlayer(const Entity &e)
{
    _player.draw(e);
}

void GameRender::drawMinion(const Entity &e)
{
    _minion.draw(e);
}

void GameRender::drawMinion2(const Entity &e)
{
    _minion2.draw(e);
}

