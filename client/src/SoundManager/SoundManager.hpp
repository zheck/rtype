//
//  SoundManager.h
//  xCodeClient
//
//  Created by mo_r on 04/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef __xCodeClient__SoundManager__
#define __xCodeClient__SoundManager__

#include <SFML/Audio.hpp>
#include <iostream>

class SoundManager
{
    sf::SoundBuffer _bufferSwitch;
    sf::SoundBuffer _bufferKeyStroke;
    sf::SoundBuffer _bufferFlip;
    sf::SoundBuffer _bufferClick;
    sf::SoundBuffer _bufferSelect;
    sf::SoundBuffer _bufferFire;
    sf::SoundBuffer _bufferExplosion;
    sf::SoundBuffer _bufferMenu;
    sf::SoundBuffer _bufferGame;
    sf::SoundBuffer _bufferEndGame;
    sf::SoundBuffer _bufferVictory;
    sf::Sound _soundSwitch;
    sf::Sound _soundKeyStroke;
    sf::Sound _soundFlip;
    sf::Sound _soundClick;
    sf::Sound _soundSelect;
    sf::Sound _soundFire;
    sf::Sound _soundExplosion;
    sf::Sound _soundEndGame;
    sf::Sound _soundVictory;
    sf::Music _musicMenu;
    sf::Music _musicGame;
    
public:
    static SoundManager & getInstance()
    {
        static SoundManager   instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    };
    void init();
    
    void playSwitch();
    void playKeyStroke();
    void playFlip();
    void playClick();
    void playSelect();
    void playFire();
    void playExplosion();
    void playVictory();
    void playMenu(bool playStat);
    void playGame(bool playStat);
    void playEndGame(bool playStat);

private:
    SoundManager() {}
    SoundManager(SoundManager const&);
    void operator=(SoundManager const&);
};

#endif /* defined(__xCodeClient__SoundManager__) */
