#ifndef __DESKTOP_WORMS_SRC_CLIENT_CLIENT_CONSTANTS_H_
#define __DESKTOP_WORMS_SRC_CLIENT_CLIENT_CONSTANTS_H_

// Graphics
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define LEVEL_WIDTH 1000
#define LEVEL_HEIGHT 1000

#define PPM 1000 / 20

// Protocolo
#define GAME_RECEIVING 87
#define LOBBY_RECEIVING 89
#define GAME_SENDING 86
#define LOBBY_SENDING 88

#define CREATE_CODE 1
#define JOIN_CODE 2
#define GAME_LIST_CODE 3

#define START_GAME_CODE 1

#define MOVE_CODE 2
#define STOP_MOVE 3

#define JUMP_CODE 3
#define ROLLBACK_CODE 4
#define FIRE_CODE 5
#define AIM_CODE 6

#endif  // __DESKTOP_WORMS_SRC_CLIENT_CLIENT_CONSTANTS_H_
