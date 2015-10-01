//
//  File.h
//  xCodeClient
//
//  Created by mo_r on 23/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__File__
#define __xCodeClient__File__

#include <iostream>

#include <iostream>

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class MegaAttackRender
{
    sf::RenderWindow *_window;
    sf::Texture _ShockWaveImg;
    sf::Sprite _ShockWaveSprite;
    std::vector<sf::IntRect> _ShockWaveSpriteRect;
    int _animation;
    
public:
    MegaAttackRender();
    MegaAttackRender(MegaAttackRender const & rhs);
    ~MegaAttackRender();
    
    MegaAttackRender & operator=(MegaAttackRender const & rhs);
    
    void init(sf::RenderWindow * window);
    void draw(Entity const & e);
};


#endif /* defined(__xCodeClient__File__) */
