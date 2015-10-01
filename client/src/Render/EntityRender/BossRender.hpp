//
//  BossRender.h
//  xCodeClient
//
//  Created by Zhou Fong on 11/20/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__BossRender__
#define __xCodeClient__BossRender__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class BossRender
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
    BossRender();
    BossRender(BossRender const & rhs);
    ~BossRender();
    
    BossRender & operator=(BossRender const & rhs);
    
    void init(sf::RenderWindow * window);
    void draw(Entity const & e);
};

#endif /* defined(__xCodeClient__BossRender__) */
