//
//  Game.h
//  R-TypeServer
//
//  Created by Zhou Fong on 10/13/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Game__
#define __R_TypeServer__Game__

#include <iostream>
#include <list>
#include <map>

#include "Player.hpp"
#include "Bullet.hpp"
#include "Map.hpp"
#include "ShockWave.hpp"
#include "MegaAttack.hpp"

class Room;

class Game {
    int _gameTime;
    std::string _gameName;
    eGameState _gameState;
    std::list<Entity *> _ennemies;
    std::list<Entity *> _missiles;
    std::list<Player *> _playerList;
    std::map<int, Entity *> _entities;
    Room * _delegate;
    Map _map;
    Message _msg;
    int _unitId;
    int _gameEnd;
    
    size_t _numberOfPlayerAlive;
    int _numberOfBossAlive;
    
    
public:
    Game(std::string const & gameName);
    Game(Game const & rhs);
    ~Game();
    
    Game & operator=(Game const & rhs);
    
    void init(std::list<Player *> & playerList);
    void start();
    void release();
    void setDelegate(Room *);
    void addEntity(Entity * e);
    void addMissile(Entity * e);
    
private:
    void run();
    bool stillPlaying();
    
    void getPlayerActions(Message & msg);
    void addSpawn();
    void updateMap();
    void updateBullets();
    void updateMinions();
    void sendMap(Message & msg);
    void sendEntity(Message & msg, Entity const & e);
    void sendAll(Message const & msg);
    Player * getPlayerById(int id);
};

#endif /* defined(__R_TypeServer__Game__) */
