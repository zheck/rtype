//
//  Room.h
//  xCodeClient
//
//  Created by mo_r on 23/10/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__Room__
#define __xCodeClient__Room__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>

#include "ClockManager.hpp"
#include "Defines.hpp"
#include "Message.hpp"
#include "Defines.hpp"

class RoomSelection
{
    float _time;
    eSelection _selection;
    eSelectedRoom _selectedRoom;
    std::vector<sf::IntRect> _listRect;
    sf::IntRect _createRect;
    sf::IntRect _inputRect;
    sf::IntRect _joinRoom;
    std::string _createRoomName;
    bool _userInteraction;
    std::list<std::string> _listRoom;
    std::map<eRect, void(RoomSelection::*)(Message & msg)> _clicking;
    
public:
    RoomSelection();
    ~RoomSelection();
    RoomSelection(RoomSelection const & Room);
    RoomSelection & operator=(RoomSelection const & Room);
    
    void init();
    void clear();
    void update(sf::Event const & event, ClockManager const & clock, Message & msg);
    std::string getCreateRoomName() const;
    eSelection getSelection() const;
    sf::IntRect getRect(eRect const & rectType) const;
    std::list<std::string> getListRoom() const;
    void setUserInteraction(bool b);
    
private:
    void clickOnCreateRoom(Message & msg);
    void clickOnRoom(Message & msg);
    void clickOnJoin(Message & msg);
    bool clickedOnButton(sf::IntRect const & rect, sf::Event const & event);
};


#endif /* defined(__xCodeClient__Room__) */
