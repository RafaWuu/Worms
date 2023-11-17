//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_COMMON_PROTOCOL_CONSTANTS_H
#define WORMS_COMMON_PROTOCOL_CONSTANTS_H

#define SERVERPROTOCOL_LOG_SRC "../log/serverprotocol_log.txt"

// Lobby

#define LOBBY_RECEIVING 88

#define LOBBY_CREATE_GAME 01
#define LOBBY_JOIN_GAME 02
#define LOBBY_LIST_GAMES 03

#define LOBBY_SENDING 89

#define LOBBY_ERROR 01
#define LOBBY_NEWCLIENT 02
#define LOBBY_GAMEJOINING 03
#define LOBBY_GAMELISTING 04


// Juego

#define GAME_RECEIVING 86

#define GAME_START_GAME 1
#define GAME_MOVE 2
#define GAME_JUMP 3
#define GAME_ROLLBACK 4
#define GAME_FIRE 5
#define GAME_AIM 6
#define GAME_POWER 7
#define GAME_DATTACK 8
#define GAME_COUNTDOWN 9
#define GAME_GUNSELECT 10


#define GAME_SENDING 87

#define GAME_ERROR 1
#define GAME_SCENARIO 2
#define GAME_LIST_WORMS 3
#define GAME_STATUS 4

// Errores lobby

#define INVALID_SCENARIO_NAME 1
#define INVALID_GAME_ID 2
#define CLIENT_ALREADY_IN_GAME 3

// Errores juego

#define ONLY_OWNER_CAN_LAUNCH 1
#define GAME_HAS_NOT_STARTED 2
#define INVALID_WORM_ID 3

#endif  // WORMS_COMMON_PROTOCOL_CONSTANTS_H