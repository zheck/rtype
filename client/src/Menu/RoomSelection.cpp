//
//  Room.cpp
//  xCodeClient
//
//  Created by mo_r on 23/10/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include <cstring>
#include "RoomSelection.hpp"
#include "ResourcePath.hpp"
#include "KeyManager.hpp"
#include "SoundManager.hpp"

RoomSelection::RoomSelection() :
_time(0),
_selection(NONE),
_selectedRoom(SELECTED_NONE)
{
    _clicking[CREATE_RECT] = &RoomSelection::clickOnCreateRoom;
    _clicking[ROOM1_RECT] = &RoomSelection::clickOnRoom;
    _clicking[ROOM2_RECT] = &RoomSelection::clickOnRoom;
    _clicking[ROOM3_RECT] = &RoomSelection::clickOnRoom;
    _clicking[ROOM4_RECT] = &RoomSelection::clickOnRoom;
    _clicking[JOIN_RECT] = &RoomSelection::clickOnJoin;
}

RoomSelection::~RoomSelection()
{}

void RoomSelection::init()
{
    sf::IntRect create(WINX/2 + 60, WINY/3 + 2, 100, 20);
    sf::IntRect input(WINX/4 + 60, WINY/3, 180, 20);

    _listRect.push_back(input);
    _listRect.push_back(create);
    int y = WINY/3 + 30;
    for (int i=0; i < 4; ++i) {
        y += 40;
        sf::IntRect room(WINX/4 + 60, y, 180, 20);
        _listRect.push_back(room);
    }
    sf::IntRect join(460, 390, 100, 20);
    _listRect.push_back(join);
    _userInteraction = true;
}

void RoomSelection::clear()
{
    _listRoom.clear();
    _userInteraction = true;
    _createRoomName = "";
}

void RoomSelection::clickOnCreateRoom(Message & msg)
{
    if (_userInteraction == false) {
        return ;
    }
    _userInteraction = false;
    if (!_createRoomName.empty()) {
        SoundManager::getInstance().playClick();
        Vect2 pos = KeyManager::getInstance().getMousePosition();
        KeyManager::getInstance().setMousePosition(pos.x + 0.2, pos.y + 0.2);
        _selection = CREATE_ROOM_BUTTON;
        msg.messageType = MSG_CREAT_ROOM;
        strcpy(msg.msg, _createRoomName.c_str());
    }
}

void RoomSelection::clickOnRoom(Message & msg)
{
    (void)msg;
    _userInteraction = true;
    _selectedRoom = static_cast<eSelectedRoom>(_selection);
}

void RoomSelection::clickOnJoin(Message & msg)
{
    if (_selectedRoom != SELECTED_NONE && !_listRoom.empty() && _userInteraction == true)
    {
        _userInteraction = false;
        SoundManager::getInstance().playClick();
        Vect2 pos = KeyManager::getInstance().getMousePosition();
        KeyManager::getInstance().setMousePosition(pos.x + 0.2, pos.y + 0.2);
        
        std::list<std::string>::iterator it;
        
        _selection = SELECTION_JOIN;
        msg.messageType = MSG_JOIN_ROOM;
        int i = 2;
        for (it = _listRoom.begin(); it != _listRoom.end(); ++it) {
            if (i == static_cast<int>(_selectedRoom)) {
                std::string str;
                str = *it;
                strcpy(msg.msg, str.c_str());
                return;
            }
            i++;
        }
    }
}

sf::IntRect RoomSelection::getRect(eRect const & rectType) const
{
    return (_listRect[rectType]);
}

eSelection RoomSelection::getSelection() const
{
    return _selection;
}

std::string RoomSelection::getCreateRoomName() const
{
    return _createRoomName;
}

std::list<std::string> RoomSelection::getListRoom() const
{
    return _listRoom;
}

void RoomSelection::update(sf::Event const & event,ClockManager const & clock, Message & msg)
{
    if (msg.messageType == MSG_ROOM_LIST && msg.response == true) {
        _userInteraction = true;
        _listRoom.push_back(msg.msg);
    }
    else if (msg.messageType == MSG_DELETE_ROOM) {
        _listRoom.remove(msg.msg);
    }
    msg.messageType = MSG_IDDLE;
    if (clock.getElapsedTime() - _time < 0.10) {
        return ;
    }
    Vect2 mouse = KeyManager::getInstance().getMousePosition();
    if (_listRect[INPUT_RECT].contains(mouse.x, mouse.y))
    {
        _selection = CREATE_ROOM_INPUT;
        if (KeyManager::getInstance().typeIsTextEntered(event) == true) {
            _time = clock.getElapsedTime();
            if (KeyManager::getInstance().isKeyPressed(Keyboard::BackSpace) && !_createRoomName.empty()) {
                _userInteraction = true;
                _createRoomName = _createRoomName.substr(0, _createRoomName.size() - 1);
                SoundManager::getInstance().playKeyStroke();
            }
            else if (_createRoomName.size() < (unsigned int)NAME_MAX_LENGTH) {
                std::string key = KeyManager::getInstance().getPressedKey(event);
                _createRoomName += key;
                SoundManager::getInstance().playKeyStroke();
            }

        }
    }
    for (int i = 1; i <= SELECTION_JOIN; ++i) {
        if (KeyManager::getInstance().isMouseButtonPressed(_listRect[i]) &&
            _clicking.find(static_cast<eRect>(i)) != _clicking.end()) {
            _selection = static_cast<eSelection>(i);
            (this->*_clicking[static_cast<eRect>(i)])(msg);
        }
    }
}

void RoomSelection::setUserInteraction(bool b)
{
    _userInteraction = b;
}
