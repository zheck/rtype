//
//  BulletRender.h
//  xCodeClient
//
//  Created by Zhou Fong on 11/16/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__BulletRender__
#define __xCodeClient__BulletRender__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class BulletRender
{
    sf::RenderWindow *_window;
    sf::Texture _bulletImg;
    sf::Sprite _bulletSprite;
    std::vector<sf::IntRect> _bulletSpriteRect;

public:
    BulletRender();
    BulletRender(BulletRender const & rhs);
    ~BulletRender();
    
    BulletRender & operator=(BulletRender const & rhs);
    
    void init(sf::RenderWindow * window);
    void draw(Entity const & e);
};

#endif /* defined(__xCodeClient__BulletRender__) */
