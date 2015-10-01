//
//  MinionRender.h
//  xCodeClient
//
//  Created by Zhou Fong on 11/16/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__MinionRender__
#define __xCodeClient__MinionRender__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class MinionRender
{
    sf::RenderWindow *_window;
    sf::Texture _minionImg;
    sf::Texture _deathImg;
    sf::Sprite _minionSprite;
    sf::Sprite _deathSprite;
    std::vector<sf::IntRect> _minionSpriteRect;
    std::vector<sf::IntRect> _deathRect;
    int _deathTime;
    
public:
    MinionRender();
    MinionRender(MinionRender const & rhs);
    ~MinionRender();
    
    MinionRender & operator=(MinionRender const & rhs);
    
    void init(sf::RenderWindow * window);
    void draw(Entity const & e);
};

#endif /* defined(__xCodeClient__MinionRender__) */
