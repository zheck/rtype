//
//  GameRender.h
//  xCodeClient
//
//  Created by mo_r on 13/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__GameRender__
#define __xCodeClient__GameRender__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "PlayerRender.hpp"
#include "BulletRender.hpp"
#include "MinionRender.hpp"
#include "ShockWaveRender.hpp"
#include "MegaAttackRender.hpp"
#include "BossRender.hpp"
#include "AsteroidRender.hpp"
#include "Minion2Render.hpp"

class GameRender
{
    sf::RenderWindow * _window;
    sf::Texture _bgImg;
    sf::Texture _bgImg2;
    int _bgScrollingX;
    sf::Sprite _bgSprite1;
    sf::Sprite _bgSprite2;
    sf::Sprite _bgSprite3;
    sf::Sprite _bgSprite4;
    int _bgSprite2InitX;
    
    PlayerRender _player;
    BulletRender _bullet;
    MinionRender _minion;
    ShockWaveRender _shockWave;
    MegaAttackRender _megaAttack;
    BossRender _bossRender;
    AsteroidRender _asteroidRender;
    Minion2Render _minion2;
    std::map<eType, void(GameRender::*)(Entity const & e)> _drawFuncs;
    
public:
    GameRender();
    GameRender(GameRender const & rhs);
    ~GameRender();

    GameRender & operator=(GameRender const & rhs);
    
    void init(sf::RenderWindow *window);
    void draw(std::map<int, Entity *> & entities);
    
    void drawPlayer(Entity const & e);
    void drawBullet(Entity const & e);
    void drawShockWave(Entity const & e);
    void drawMegaAttack(Entity const &e);
    void drawMinion(Entity const & e);
    void drawBoss(Entity const & e);
    void drawAsteroid(Entity const & e);
    void drawMinion2(Entity const & e);
};

#endif /* defined(__xCodeClient__GameRender__) */
