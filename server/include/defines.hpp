//
//  defines.h
//  R-TypeServer
//
//  Created by Zhou Fong on 10/12/13.
//  Copyright (c) 2013 Zhou Fong. All rights reserved.
//

#ifndef R_TypeServer_defines_h
#define R_TypeServer_defines_h

static const int MAX_PLAYER = 10;
static const int MAX_ROOM = 4;
static const int MSG_SIZE = 30;
static const int TIME_UNIT = 20;
static const int BONUS_AMMO = 20;
static const int BOSS_LIFE = 20;

enum eType
{
    PLAYER = 0,
    MINION = 1,
    BULLET = 2,
    SHOCK_WAVE = 3,
    BOSS = 4,
    ASTEROID = 5,
    MEGA_ATTACK = 6,
    MINION2 = 7
};

enum eMessageType
{
    MSG_IDDLE = -1,
    MSG_CONNECT = 0,
    MSG_DISCONNECT = 1,
    MSG_CREAT_ROOM = 2,
    MSG_JOIN_ROOM = 3,
    MSG_LEAVE_ROOM = 4,
    MSG_ROOM_LIST = 5,
    MSG_PLAYER_LIST = 6,
    MSG_START_GAME = 7,
    MSG_GAME = 8,
    MSG_WON = 9,
    MSG_LOST = 10,
    MSG_DELETE_ROOM = 11,
};

enum eGameState
{
    GAME_PLAYING = 0,
    GAME_WON = 1,
    GAME_LOST = 2
};

#endif
