//
//  KeyManager.cpp
//  xCodeClient
//
//  Created by mo_r on 28/10/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "KeyManager.hpp"

void KeyManager::init(sf::RenderWindow *window)
{
    _window = window;
    _keyBinding[UP] = sf::Keyboard::Up;
    _keyBinding[DOWN] = sf::Keyboard::Down;
    _keyBinding[LEFT] = sf::Keyboard::Left;
    _keyBinding[RIGHT] = sf::Keyboard::Right;
}

std::string KeyManager::getPressedKey(const sf::Event &event)
{
    std::string key;
    
    key += static_cast<char>(event.text.unicode);
    return key;
}

bool KeyManager::isPrintable(std::string const & key) const
{
  return ((!key.empty() && (key[0] > 30 && (key[0] < 127))));
}

bool KeyManager::typeIsTextEntered(sf::Event const & event) const
{
    return (event.type == sf::Event::TextEntered);
}

bool KeyManager::typeIsKeyPressed(const sf::Event &event) const
{
    return (event.type == sf::Event::KeyPressed);
}

bool KeyManager::isKeyPressed(Keyboard::Key key)
{
    return (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key)));
}

bool KeyManager::isMouseButtonPressed() const
{
    return (sf::Mouse::isButtonPressed(sf::Mouse::Left));
}

bool KeyManager::isMouseButtonPressed(sf::IntRect const & rect) const
{
    return (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        rect.contains(this->getMousePosition().x, this->getMousePosition().y));
}

void KeyManager::setUserInteraction(bool userInteraction)
{
    _userInteraction = userInteraction;
}

bool KeyManager::getUserInteraction() const
{
    return _userInteraction;
}

Vect2 KeyManager::getMousePosition() const
{
    Vect2 pos;

    pos.x = sf::Mouse::getPosition(*_window).x;
    pos.y = sf::Mouse::getPosition(*_window).y;
    return (pos);
}

void KeyManager::setMousePosition(int x, int y)
{
    sf::Vector2<int> pos(x,y);
    sf::Mouse::setPosition(pos, *_window);
}
