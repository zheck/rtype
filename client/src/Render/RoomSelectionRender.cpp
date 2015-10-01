//
//  RoomSelectionRender.cpp
//  xCodeClient
//
//  Created by mo_r on 13/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "ResourcePath.hpp"
#include "RoomSelectionRender.hpp"

RoomSelectionRender::RoomSelectionRender()
{}

RoomSelectionRender::~RoomSelectionRender()
{}

void RoomSelectionRender::init(sf::RenderWindow *window, RoomSelection const & roomSelection)
{
    _window = window;
    
    sf::Color orange(221,170,50);
    _roomSelectionBgPos.x = -500;
    _roomSelectionBgPos.y = WINY/5;
    if (!_starcraftTtf.loadFromFile(resourcePath() + "starcraft.ttf") ||
        !_sansationTtf.loadFromFile(resourcePath() + "sansation.ttf") ||
        !_bgImg.loadFromFile(resourcePath() + "space.png") ||
        !_roomSelectionBgImg.loadFromFile(resourcePath() + "room.png") ||
        !_inputDisabledImg.loadFromFile(resourcePath() + "unselectedArea.png") ||
        !_inputEnabledImg.loadFromFile(resourcePath() + "selectedArea.png") ||
        !_createButtonImg.loadFromFile(resourcePath() + "enabledButton.png") ||
        !_roomUnselectedImg.loadFromFile(resourcePath() + "unselectedArea.png") ||
        !_joinImg.loadFromFile(resourcePath() + "enabledButton.png") ||
        !_disabledButtonImg.loadFromFile(resourcePath() + "disabledButton.png") ||
        !_enabledButtonImg.loadFromFile(resourcePath() + "enabledButton.png"))
    {
        std::cerr << "can't find room image" << std::endl;
        return;
    }

    sf::Sprite bgSprite(_bgImg);
    _bgSprite = bgSprite;
    
    _title.setString("R-TYPE");
    _title.setFont(_starcraftTtf);
    _title.setCharacterSize(50);
    _title.setColor(sf::Color::White);
    _title.setPosition(WINX/2 - 110, 20);
    
    sf::Sprite roomSelectionBgSprite(_roomSelectionBgImg);
    _roomSelectionBgSprite = roomSelectionBgSprite;
    _roomSelectionBgSprite.setPosition(_roomSelectionBgPos.x, _roomSelectionBgPos.y);
    _createPos.x = -182;
    _createPos.y = WINY/3;
    _createButtonSprite.setTexture(_createButtonImg);
    _createButtonSprite.setPosition(_createPos.x, _createPos.y);
    
    _createTitle.setString("Create Room");
    _createTitle.setFont(_starcraftTtf);
    _createTitle.setCharacterSize(10);
    _createTitle.setColor(sf::Color::Black);
    
    _roomCreationTitlePos.x = -390;
    _roomCreationTitlePos.y = WINY/3 - 25;
    _roomCreationTitle.setString("Room creation");
    _roomCreationTitle.setFont(_starcraftTtf);
    _roomCreationTitle.setColor(sf::Color::White);
    _roomCreationTitle.setCharacterSize(15);
    
    _roomListTitlePos.x = -390;
    _roomListTitlePos.y = WINY/3 + 45;
    _roomListTitle.setString("Room list");
    _roomListTitle.setFont(_starcraftTtf);
    _roomListTitle.setColor(sf::Color::White);
    _roomListTitle.setCharacterSize(15);
    
    
    _inputPos.x = -390;
    _inputPos.y = WINY/3;
    _inputSprite.setTexture(_inputDisabledImg);
    _inputSprite.setTextureRect(roomSelection.getRect(INPUT_RECT));
    _inputSprite.setPosition(_inputPos.x, _inputPos.y);
    
     
    _createRoomName.setFont(_sansationTtf);
    _createRoomName.setCharacterSize(15);
    _createRoomName.setColor(sf::Color::Black);
    _createRoomName.setPosition(WINX/4 + 70, _inputPos.y);
    
    
    _roomSelectionPos.x = -390;
    _roomSelectionPos.y = WINY/3 + 30;
    _roomSelectionSprite.setTexture(_inputDisabledImg);
    _roomSelectionSprite.setTextureRect(roomSelection.getRect(ROOM1_RECT));
    
    for (int i=0; i < 4; ++i)
    {
        _roomSelectionPos.y = _roomSelectionPos.y + 40;
        _roomSelectionSprite.setPosition(_roomSelectionPos.x, _roomSelectionPos.y);
        _listRoom.push_back(_roomSelectionSprite);
    }

    _joinPos.x = -182;
    _joinPos.y = _roomSelectionPos.y;
    _joinSprite.setTexture(_joinImg);
    
    _joinTitle.setString("Join Room");
    _joinTitle.setFont(_starcraftTtf);
    _joinTitle.setCharacterSize(10);
    _joinTitle.setColor(sf::Color::Black);
    
    _roomSelectionTitlePos.x = -355;
    _roomSelectionTitlePos.y = 450;
    
    _roomSelectionTitle.setString("Room Selection");
    _roomSelectionTitle.setFont(_starcraftTtf);
    _roomSelectionTitle.setCharacterSize(20);
    _roomSelectionTitle.setColor(orange);
}

void RoomSelectionRender::roomSelectionDrawSet(RoomSelection const & roomSelection)
{
    if (_roomSelectionBgPos.x < (WINX/5 - 10))
    {
        _roomSelectionBgPos.x += SCROLL_SPEED;
        _roomSelectionBgSprite.setPosition(_roomSelectionBgPos.x, _roomSelectionBgPos.y);
    }
    if (_createPos.x < 450)
    {
        _createPos.x += SCROLL_SPEED;
        _createButtonSprite.setPosition(_createPos.x, _createPos.y);
        _createTitle.setPosition(_createPos.x + 5, _createPos.y + 3);
        _joinPos.x += SCROLL_SPEED;
        _joinSprite.setPosition(_joinPos.x, _joinPos.y);
        _joinTitle.setPosition(_joinPos.x + 15, _joinPos.y + 3);
    }
    
    if (_inputPos.x < WINX/4 + 60)
    {
        _roomCreationTitlePos.x += SCROLL_SPEED;
        _inputPos.x += SCROLL_SPEED;
        _roomListTitlePos.x += SCROLL_SPEED;
        _roomCreationTitle.setPosition(_inputPos.x, _inputPos.y - 25);
        _inputSprite.setPosition(_inputPos.x, _inputPos.y);
        //        _roomListTitle.setPosition(_roomListTitlePos.x, _roomListTitlePos.y);
        _roomListTitle.setPosition(_inputPos.x, 245);
        for (int i=0; i < 4; ++i)
        {
            float y = _listRoom[i].getPosition().y;
            _listRoom[i].setPosition(_inputPos.x, y);
        }
    }
    if (_roomSelectionTitlePos.x < 295)
    {
        _roomSelectionTitlePos.x += SCROLL_SPEED;
        _roomSelectionTitle.setPosition(_roomSelectionTitlePos.x, _roomSelectionTitlePos.y);
    }
    
    if (roomSelection.getSelection() == CREATE_ROOM_INPUT)
        _inputSprite.setTexture(_inputEnabledImg);
    else
        _inputSprite.setTexture(_inputDisabledImg);
    if (roomSelection.getSelection() >= SELECTION_ROOM1 &&
        roomSelection.getSelection() <= SELECTION_ROOM4 &&
        _listRoom[static_cast<int>(roomSelection.getSelection() - 2)].getTexture() == &_inputEnabledImg) {
        _joinSprite.setTexture(_enabledButtonImg);
    }
    else {
        _joinSprite.setTexture(_disabledButtonImg);
    }
    if (roomSelection.getCreateRoomName().empty()) {
        _createButtonSprite.setTexture(_disabledButtonImg);
    }
    else {
        _createButtonSprite.setTexture(_enabledButtonImg);
    }
    _createRoomName.setString(roomSelection.getCreateRoomName());
}

void RoomSelectionRender::draw(const RoomSelection &roomSelection)
{
    this->roomSelectionDrawSet(roomSelection);
    _window->draw(_bgSprite);
    _window->draw(_title);
    _window->draw(_roomSelectionBgSprite);
    _window->draw(_roomCreationTitle);
    _window->draw(_inputSprite);
    _window->draw(_roomListTitle);
    _window->draw(_createButtonSprite);
    _window->draw(_createRoomName);
    _window->draw(_joinSprite);
    _window->draw(_createTitle);
    _window->draw(_joinTitle);
    for (int i=0; i < 4; ++i) {
        _listRoom[i].setTexture(_inputDisabledImg);
        _window->draw(_listRoom[i]);
    }
    std::list<std::string> listRoom = roomSelection.getListRoom();
    if (!listRoom.empty())
    {
        std::list<std::string>::iterator it;
        
        Vect2f roomNamePos(WINX/4, WINY/3);
        
        int i = 2;
        for (it = listRoom.begin(); it != listRoom.end(); ++it)
        {
            sf::Text roomName;
            
            if (i == roomSelection.getSelection()) {
                _listRoom[i - 2].setTexture(_inputEnabledImg);
            }
            else
                _listRoom[i - 2].setTexture(_inputDisabledImg);
            roomName.setString(*it);
            roomName.setFont(_sansationTtf);
            roomName.setCharacterSize(15);
            roomName.setColor(sf::Color::Black);
            roomName.setPosition(_listRoom[i - 2].getPosition().x + 10, _listRoom[i - 2].getPosition().y);
            _window->draw(_listRoom[i - 2]);
            _window->draw(roomName);
            ++i;
            roomNamePos.y += 15;
        }
    }
    _window->draw(_roomSelectionTitle);
}
