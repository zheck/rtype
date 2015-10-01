//
//  RoomRender.h
//  xCodeClient
//
//  Created by mo_r on 13/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__RoomRender__
#define __xCodeClient__RoomRender__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Vect2f.hpp"
#include "InRoom.hpp"

class RoomRender
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
    Vect2f _startGameTitlePos;
    sf::Text _startGameTitle;
    Vect2f _playerListTitlePos;
    sf::Text _playerListTitle;
    Vect2f _playerNamePos;
    sf::Text _playerName;
    
    sf::Text username;
    sf::Text username2;
    sf::Text username3;
    sf::Text username4;
    
    std::vector<sf::Text *> _usernameList;

public:
    RoomRender();
    ~RoomRender();
    RoomRender(RoomRender const & RoomRender);
    RoomRender & operator=(RoomRender const & RoomRender);
    
    void init(sf::RenderWindow *window);
    void draw(InRoom & Room);
};

#endif /* defined(__xCodeClient__RoomRender__) */
