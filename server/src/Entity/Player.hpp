//
//  Player.h
//  R-TypeServer
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef __R_TypeServer__Player__
#define __R_TypeServer__Player__

#include <iostream>

#include "Entity.hpp"
#include "Message.hpp"
#include "ISocket.hpp"
#include "Weapon.hpp"

class Room;
class Game;

class Player : public Entity
{
public:
    Room * currentRoom;
    std::string name;
    int port;
    
protected:
    int _playerId;
    std::string _playerIp;
    int _color;
    ISocket * _udpSocket;
    int _lastUpdated;
    Weapon _weapon;
    
public:
    Player(int playerId, std::string const & playerIp, std::string const & port);
    Player(Player const & rhs);
    virtual ~Player();
    
    Player & operator=(Player const & rhs);
    
    virtual void update(int gameTime);
    virtual void attack(Entity * e, int gameTime);
    virtual void takeDamage(int gameTime);
    
    void reinit(Game * g);
    int getPlayerId() const ;
    std::string getPlayerIp();
    void setPlayerId(int id);
    void recvMsg(Message & msg);
    void sendMsg(Message const & msg);
};

#endif /* defined(__R_TypeServer__Player__) */
