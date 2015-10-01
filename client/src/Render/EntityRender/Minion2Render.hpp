//
//  Minion2Render.h
//  xCodeClient
//
//  Created by mo_r on 24/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__Minion2Render__
#define __xCodeClient__Minion2Render__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Minion2Render
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
    Minion2Render();
    Minion2Render(Minion2Render const & rhs);
    ~Minion2Render();
    
    Minion2Render & operator=(Minion2Render const & rhs);
    
    void init(sf::RenderWindow * window);
    void draw(Entity const & e);
};

#endif /* defined(__xCodeClient__Minion2Render__) */
