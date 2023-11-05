//
// Created by xguss on 04/11/23.
//

#ifndef WORMS_SERVER_ERROR_H
#define WORMS_SERVER_ERROR_H

#include <cstdint>

#include "game/server_statusbroadcast_monitor.h"

#include "common_liberror.h"
#include "server_protocol.h"
#include "server_protocol_constants.h"


struct LobbyError: public LibError {
    LobbyError(uint8_t code, const char* fmt, uint16_t a): code(code), LibError(0, fmt, a) {}

    LobbyError(uint8_t code, const char* fmt, uint16_t a, uint16_t b):
            code(code), LibError(0, fmt, a, b) {}
    uint8_t code;

    void send(ServerProtocol& protocol) { protocol.send_lobby_errormessage(code); }
};

struct InvalidGameIDLobbyError: public LobbyError {
    explicit InvalidGameIDLobbyError(uint16_t id):
            LobbyError(INVALID_GAME_ID, "The requested game with %hu was not found", id) {}
};

struct ClientAlreadyInGameLobbyError: public LobbyError {
    ClientAlreadyInGameLobbyError(uint16_t client_id, uint16_t game_id):
            LobbyError(CLIENT_ALREADY_IN_GAME, "Client %hu already in game %hu", client_id,
                       game_id) {}
};

struct GameError: public LibError {
    GameError(uint8_t code, const char* fmt, uint16_t client_id):
            code(code), client_id(client_id), LibError(0, fmt, client_id) {}

    uint8_t code;
    uint16_t client_id;
};

struct OnlyTheOwnerCanLaunchGameError: public GameError {
    explicit OnlyTheOwnerCanLaunchGameError(uint16_t client_id):
            GameError(ONLY_OWNER_CAN_LAUNCH, "Error in %hu request, client is not the owner",
                      client_id) {}
};

struct GameHasNotStartedGameError: public GameError {
    explicit GameHasNotStartedGameError(uint16_t client_id):
            GameError(GAME_HAS_NOT_STARTED, "Error in %hu request, Game has not started yet",
                      client_id) {}
};

struct InvalidWormIdGameError: public GameError {
    explicit InvalidWormIdGameError(uint16_t client_id):
            GameError(INVALID_WORM_ID, "Error in %hu request,  the worm requested cant be moved",
                      client_id) {}
};

#endif  // WORMS_SERVER_ERROR_H
