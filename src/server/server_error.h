

#ifndef WORMS_SERVER_ERROR_H
#define WORMS_SERVER_ERROR_H

#include <cstdint>
#include <string>

#include "game/server_statusbroadcast_monitor.h"

#include "common_liberror.h"
#include "common_protocol_constants.h"
#include "server_protocol.h"

#define MAX_MSG_LEN 256

struct InvalidMsg: public std::exception {
private:
    std::string error_msg;

public:
    InvalidMsg(): error_msg("The message is invalid") {}

    void send(ServerProtocol& protocol) { protocol.send_lobby_errormessage(0); }
};

struct LobbyError: public std::exception {
protected:
    char error_msg[MAX_MSG_LEN];
    uint8_t code;

public:
    LobbyError(uint8_t code, const char* fmt, ...): code(code), error_msg() {
        va_list args;
        va_start(args, fmt);

        vsnprintf(error_msg, sizeof(error_msg), fmt, args);

        va_end(args);
    }

    ~LobbyError() override = default;

    void send(ServerProtocol& protocol) const { protocol.send_lobby_errormessage(code); }

    const char* what() const noexcept override { return error_msg; };
};

struct InvalidGameIDLobbyError: public LobbyError {
    explicit InvalidGameIDLobbyError(uint16_t id):
            LobbyError(INVALID_GAME_ID, "The requested game %hu was not found", id) {}
};

struct ClientAlreadyInGameLobbyError: public LobbyError {
    ClientAlreadyInGameLobbyError(uint16_t client_id, uint16_t game_id):
            LobbyError(CLIENT_ALREADY_IN_GAME, "Client %hu already in game %hu", client_id,
                       game_id) {}
};

struct GameFullLobbyError: public LobbyError {
    explicit GameFullLobbyError(uint16_t id, uint16_t i):
            LobbyError(INVALID_GAME_ID, "Game %hu is full", id) {}
};

struct GameError: public std::exception {
protected:
    char error_msg[MAX_MSG_LEN];

public:
    uint8_t code;
    uint16_t client_id;
    GameError(uint8_t code, uint16_t client_id, const char* fmt, ...):
            code(code), client_id(client_id), error_msg() {
        va_list args;
        va_start(args, fmt);

        vsnprintf(error_msg, sizeof(error_msg), fmt, args);

        va_end(args);
    }

    ~GameError() override = default;

    void send(ServerProtocol& protocol) const { protocol.send_lobby_errormessage(code); }

    const char* what() const noexcept override { return error_msg; };
};

struct OnlyTheOwnerCanLaunchGameError: public GameError {
    explicit OnlyTheOwnerCanLaunchGameError(uint16_t client_id):
            GameError(ONLY_OWNER_CAN_LAUNCH, client_id,
                      "Error in %hu request, client is not the owner", client_id) {}
};

struct GameHasNotStartedGameError: public GameError {
    explicit GameHasNotStartedGameError(uint16_t client_id):
            GameError(GAME_HAS_NOT_STARTED, client_id,
                      "Error in %hu request, Game has not started yet", client_id) {}
};

struct InvalidWormIdGameError: public GameError {
    explicit InvalidWormIdGameError(uint16_t client_id):
            GameError(INVALID_WORM_ID, client_id,
                      "Error in %hu request,  the worm requested cant be moved", client_id) {}
};

struct FinishedGameError: public std::exception {};


#endif  // WORMS_SERVER_ERROR_H
