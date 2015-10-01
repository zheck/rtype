//
//  Defines.h
//  xCodeClient
//
//  Created by mo_r on 21/10/13.
//  Copyright (c) 2013 mo_r. All rights reserved.
//

#ifndef xCodeClient_Defines_h
#define xCodeClient_Defines_h

static const float WINX = 800;
static const float WINY = 600;
static const int MSG_SIZE = 30;
static const int IP_SIZE = 16;
static const int PORT = 1234;
static const double TIME_UNIT = 0.015;
static const int GAME_TIME_UNIT = 20;
static const int NAME_MAX_LENGTH = 20;
static const int BACKGROUND_SCROLL_UNIT = 1;

static const int PLAYER_SIZE = 33;
static const int BULLET_SIZE = 8;
static const int MINION1_WIDTH = 17;
static const int MINION1_HEIGHT = 36;
static const int EXPLOSION_SIZE = 30;
static const int SCROLL_SPEED = 20;

enum eKEY
{
    LEFT = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    SHOOT = 4
};

enum eINPUTSTATE
{
    USERINPUT,
    SERVERINPUT
};

enum eGameState
{
    MENU,
    ROOM_SELECTION,
    ROOM,
    GAME,
    GAME_LOST,
    GAME_WON
};

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

enum eSelection
{
    NONE = -1,
    CREATE_ROOM_INPUT,
    CREATE_ROOM_BUTTON,
    SELECTION_ROOM1,
    SELECTION_ROOM2,
    SELECTION_ROOM3,
    SELECTION_ROOM4,
    SELECTION_JOIN,
    SELECTION_START
};

enum eSelectedRoom
{
    SELECTED_NONE = -1,
    SELECTED_ROOM1 = 2,
    SELECTED_ROOM2,
    SELECTED_ROOM3,
    SELECTED_ROOM4
};

enum eRect
{
    INPUT_RECT,
    CREATE_RECT,
    ROOM1_RECT,
    ROOM2_RECT,
    ROOM3_RECT,
    ROOM4_RECT,
    JOIN_RECT
};

#endif
