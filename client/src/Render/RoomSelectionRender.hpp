//
//  RoomSelectionRender.h
//  xCodeClient
//
//  Created by mo_r on 13/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__RoomSelectionRender__
#define __xCodeClient__RoomSelectionRender__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "RoomSelection.hpp"
#include "Vect2f.hpp"

class RoomSelectionRender
{
    sf::RenderWindow *_window;
    
    sf::Font _starcraftTtf;
    sf::Font _sansationTtf;
    sf::Sprite _bgSprite;
    sf::Text _title;
    sf::Texture _bgImg;
    Vect2f _roomSelectionTitlePos;
    sf::Text _roomSelectionTitle;
    Vect2f _roomCreationTitlePos;
    sf::Text _roomCreationTitle;
    Vect2f _roomListTitlePos;
    sf::Text _roomListTitle;
    sf::Text _createTitle;
    sf::Text _joinTitle;
    sf::Texture _disabledButtonImg;
    sf::Texture _enabledButtonImg;
    Vect2f _roomSelectionBgPos;
    sf::Texture _roomSelectionBgImg;
    sf::Sprite _roomSelectionBgSprite;
    Vect2f _createPos;
    sf::Texture _createButtonImg;
    sf::Sprite _createButtonSprite;
    sf::Texture _inputDisabledImg;
    sf::Sprite _inputDisabledSprite;
    Vect2f _inputPos;
    sf::Sprite _inputSprite;
    sf::Texture _inputEnabledImg;
    sf::Text _createRoomName;
    Vect2f _roomSelectionPos;
    sf::Sprite _roomSelectionSprite;
    sf::Texture _roomUnselectedImg;
    sf::Texture _roomSelectedImg;
    Vect2f _joinPos;
    sf::Sprite _joinSprite;
    sf::Texture _joinImg;    
    std::vector<sf::Sprite> _listRoom;
    
public:
    RoomSelectionRender();
    RoomSelectionRender(RoomSelectionRender const & rhs);
    ~RoomSelectionRender();

    RoomSelectionRender & operator=(RoomSelectionRender const & rhs);
    
    void init(sf::RenderWindow *window, RoomSelection const & roomSelection);
    void draw(RoomSelection const & roomSelection);
    void roomSelectionDrawSet(RoomSelection const & roomSelection);
};

#endif /* defined(__xCodeClient__RoomSelectionRender__) */
