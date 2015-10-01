//
//  Menu.cpp
//  xCodeClient
//
//  Created by mo_r on 22/10/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "Menu.hpp"
#include "KeyManager.hpp"
#include "SoundManager.hpp"

Menu::Menu() :
_cursorPos(WINX/4 + 5, WINY/4 + 93),
_playPressed(false)
{}

Menu::~Menu()
{}

void Menu::init()
{
    _inputState = USERINPUT;
    gameState = MENU;
    _lastUpdateTime = 0.0;
}

void Menu::update(sf::Event const & event, ClockManager const & clock, Message & msg)
{
    if (clock.getElapsedTime() - _lastUpdateTime < 0.10)
        return ;
    if (KeyManager::getInstance().typeIsTextEntered(event) == true)
    {
        _lastUpdateTime = clock.getElapsedTime();
        std::string key = KeyManager::getInstance().getPressedKey(event);
        
        if (KeyManager::getInstance().isKeyPressed(Keyboard::Tab)) {
            switchInput();
            SoundManager::getInstance().playSwitch();
        }
        else if (_inputState == USERINPUT) {
            updateUsername(key);
            SoundManager::getInstance().playKeyStroke();
        }
        else {
            updateIp(key);
            SoundManager::getInstance().playKeyStroke();
        }
        if (KeyManager::getInstance().isKeyPressed(Keyboard::Return) &&
                 !_userName.empty() && !_serverAdress.empty()) {
            msg.messageType = MSG_CONNECT;
            msg.copyMessage(_userName.c_str());
            KeyManager::getInstance().setUserInteraction(false);
            _playPressed = true;
        }
    }
}

void Menu::updateIp(const std::string &str)
{
    if (KeyManager::getInstance().isPrintable(str) == true && _serverAdress.size() < 15)       {
        _serverAdress += str;
        SoundManager::getInstance().playKeyStroke();
    }
    else if (KeyManager::getInstance().isKeyPressed(Keyboard::BackSpace) && !_serverAdress.empty()) {
        _serverAdress = _serverAdress.substr(0, _serverAdress.size()-1);
    }
}

void Menu::updateUsername(const std::string &str)
{
    if (KeyManager::getInstance().isPrintable(str) == true && _userName.size() < (unsigned int)NAME_MAX_LENGTH) {
        _userName += str;
        SoundManager::getInstance().playKeyStroke();
    }
    else if (KeyManager::getInstance().isKeyPressed(Keyboard::BackSpace) && !_userName.empty()) {
        _userName = _userName.substr(0, _userName.size()-1);
    }
}

void Menu::switchInput()
{
    if (_inputState == USERINPUT) {
        _inputState = SERVERINPUT;
        _cursorPos.y += 84;
    }
    else {
        _inputState = USERINPUT;
        _cursorPos.y -= 84;
    }
}

std::string Menu::getInputIp() const
{
    return _serverAdress;
}

std::string Menu::getInputUser() const
{
    return _userName;
}

Vect2f Menu::getCursorPos() const
{
    return _cursorPos;
}

