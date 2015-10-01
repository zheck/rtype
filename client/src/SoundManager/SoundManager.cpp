//
//  SoundManager.cpp
//  xCodeClient
//
//  Created by mo_r on 04/11/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#include "SoundManager.hpp"
#include "ResourcePath.hpp"

void SoundManager::init()
{
    if (_bufferFire.loadFromFile(resourcePath() + "laser.wav"))
        _soundFire.setBuffer(_bufferFire);
    if (_bufferExplosion.loadFromFile(resourcePath()  + "explosion.wav"))
        _soundExplosion.setBuffer(_bufferExplosion);
    if (_bufferClick.loadFromFile(resourcePath()  + "click.wav"))
        _soundClick.setBuffer(_bufferClick);
    if (_bufferFlip.loadFromFile(resourcePath()  + "flip1.wav"))
        _soundFlip.setBuffer(_bufferFlip);
    if (_bufferKeyStroke.loadFromFile(resourcePath()  + "keyStroke.wav"))
        _soundKeyStroke.setBuffer(_bufferKeyStroke);
    if (_bufferSwitch.loadFromFile(resourcePath()  + "switch.wav"))
        _soundSwitch.setBuffer(_bufferSwitch);
    if (_bufferEndGame.loadFromFile(resourcePath() + "gameEndMusic.wav")) {
        _soundEndGame.setBuffer(_bufferEndGame);
        _soundEndGame.setLoop(true);
    }
    if (_bufferVictory.loadFromFile(resourcePath() + "victory.wav")) {
        _soundVictory.setBuffer(_bufferVictory);
    }
    _musicMenu.openFromFile(resourcePath()  + "gameofthrones.ogg");
    _musicGame.openFromFile(resourcePath()  + "game.ogg");
}

void SoundManager::playSwitch()
{
    _soundSwitch.play();
}

void SoundManager::playKeyStroke()
{
    _soundKeyStroke.setVolume(30);
    _soundKeyStroke.play();
}

void SoundManager::playFlip()
{
    _soundFlip.play();
}

void SoundManager::playClick()
{
    _soundClick.play();
}

void SoundManager::playFire()
{
    _soundFire.play();
}

void SoundManager::playExplosion()
{
    _soundExplosion.setVolume(70);
    _soundExplosion.play();
}

void SoundManager::playVictory()
{
    _soundVictory.play();
}

void SoundManager::playMenu(bool playStat)
{
    playStat ? _musicMenu.play() : _musicMenu.stop();
}

void SoundManager::playGame(bool playStat)
{
    playStat ? _musicGame.play() : _musicGame.stop();
}

void SoundManager::playEndGame(bool playStat)
{
    playStat ? _soundEndGame.play() : _soundEndGame.stop();
}
