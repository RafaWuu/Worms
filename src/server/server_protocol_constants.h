//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_PROTOCOL_CONSTANTS_H
#define WORMS_SERVER_PROTOCOL_CONSTANTS_H

#define SERVERPROTOCOL_LOG_SRC "../log/serverprotocol_log.txt"

// Lobby

#define LOBBY_RECEIVING 88

#define LOBBY_CREATE_GAME 01
#define LOBBY_JOIN_GAME 02
#define LOBBY_LIST_GAMES 03

#define LOBBY_SENDING 89

#define LOBBY_ERROR 01
#define LOBBY_GAMEJOINING 02
#define LOBBY_GAMELISTING 03

// Juego

#define GAME_RECEIVING 86

#define GAME_START_GAME 01
#define GAME_MOVE 02

#define GAME_SENDING 87

#define GAME_ERROR 01
#define GAME_SCENARIO 02
#define GAME_LIST_WORMS 03
#define GAME_STATUS 04

// Errores lobby

#define INVALID_SCENARIO_NAME 01
#define INVALID_GAME_ID 02
#define CLIENT_ALREADY_IN_GAME 03

// Errores juego

#define ONLY_OWNER_CAN_LAUNCH 01
#define GAME_HAS_NOT_STARTED 02
#define INVALID_WORM_ID 03

#endif  // WORMS_SERVER_PROTOCOL_CONSTANTS_H
