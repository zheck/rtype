//
//  KeyManager.h
//  xCodeClient
//
//  Created by mo_r on 28/10/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__KeyManager__
#define __xCodeClient__KeyManager__

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <map>

#include "Vect2.hpp"
#include "Client.hpp"

namespace Keyboard
{
    enum  	Key {
        Unknown = -1,
        A = 0, B, C, D, E, F,  G, H, I, J, K,
        L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        Num0, Num1,  Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
        Escape, LControl, LShift, LAlt, LSystem, RControl, RShift, RAlt, RSystem,
        Menu, LBracket, RBracket, SemiColon, Comma, Period, Quote, Slash, BackSlash,
        Tilde, Equal, Dash, Space, Return, BackSpace, Tab, PageUp, PageDown,
        End, Home, Insert, Delete, Add, Subtract, Multiply, Divide,
        Left, Right, Up, Down,
        Numpad0, Numpad1, Numpad2, Numpad3, Numpad4, Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, Pause, KeyCount
    };
};

class KeyManager
{
    std::map<eKEY, sf::Keyboard::Key> _keyBinding;
    bool _userInteraction;
    sf::RenderWindow *_window;

public:
    static KeyManager & getInstance()
    {
        static KeyManager   instance;
        return instance;
    };

    void init(sf::RenderWindow *window);
    std::string getPressedKey(sf::Event const & event);
    bool typeIsTextEntered(sf::Event const & event) const;
    bool typeIsKeyPressed(sf::Event const & event) const;
    bool isPrintable(std::string const & key) const;
    bool isKeyPressed(Keyboard::Key key);
    bool isMouseButtonPressed() const;
    bool isMouseButtonPressed(sf::IntRect const & rect) const;
    void setUserInteraction(bool enabled);
    bool getUserInteraction() const;
    Vect2 getMousePosition() const;
    void setMousePosition(int x, int y);
    
private:
    KeyManager() : _userInteraction(true) {};
    KeyManager(KeyManager const&);
    void operator=(KeyManager const&);
};

#endif /* defined(__xCodeClient__KeyManager__) */
