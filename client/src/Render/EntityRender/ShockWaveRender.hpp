//
//  ShockWave.h
//  xCodeClient
//
//  Created by Zhou Fong on 11/19/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__ShockWave__
#define __xCodeClient__ShockWave__

#include <iostream>

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class ShockWaveRender
{
    sf::RenderWindow *_window;
    sf::Texture _ShockWaveImg;
    sf::Sprite _ShockWaveSprite;
    std::vector<sf::IntRect> _ShockWaveSpriteRect;
    int _animation;
    
public:
    ShockWaveRender();
    ShockWaveRender(ShockWaveRender const & rhs);
    ~ShockWaveRender();
    
    ShockWaveRender & operator=(ShockWaveRender const & rhs);
    
    void init(sf::RenderWindow * window);
    void draw(Entity const & e);
};

#endif /* defined(__xCodeClient__ShockWave__) */
