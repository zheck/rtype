//
//  GameEndRender.h
//  xCodeClient
//
//  Created by Zhou Fong on 11/23/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__GameEndRender__
#define __xCodeClient__GameEndRender__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Vect2f.hpp"
#include "InRoom.hpp"

class GameEndRender
{
    sf::RenderWindow *_window;
    
    sf::Font _starcraftTtf;
    sf::Font _sansationTtf;
    sf::Sprite _bgSprite;
    sf::Text _title;
    sf::Texture _bgImg;
    Vect2f _roomBgPos;
    sf::Texture _roomBgImg;
    sf::Sprite _roomBgSprite;
    Vect2f _startGamePos;
    sf::Sprite _startGameSprite;
    sf::Texture _startGameImg;
    sf::Text _restartTitle;
    sf::Texture _youLostImg;
    sf::Texture _victoryImg;
    sf::Sprite _endGameSprite;
    Vect2f _playerListTitlePos;
    sf::Text _playerListTitle;
    Vect2f _playerNamePos;
    sf::Text _playerName;
    
public:
    GameEndRender();
    GameEndRender(GameEndRender const & rhs);
    ~GameEndRender();
    
    GameEndRender & operator=(GameEndRender const & rhs);
    
    void init(sf::RenderWindow *window);
    void draw(eGameState const & gameState);
};

#endif /* defined(__xCodeClient__GameEndRender__) */
