//
// Created by xguss on 10/09/23.
//

#ifndef SOCKETS_2023C2_ABRAIDA_SERVER_PROTOCOL_GAMEINTERFACE_H
#define SOCKETS_2023C2_ABRAIDA_SERVER_PROTOCOL_GAMEINTERFACE_H

#include <memory>
#include <string>
#include <vector>

#include "../common/common_baseprotocol.h"
#include "../common/common_socket.h"

#include "server_gameinfo.h"
#include "server_lobby_request.h"

struct InvalidMsg: public std::runtime_error {
    InvalidMsg(): std::runtime_error("The message is invalid") {}
};

class LobbyRequest;

class ServerProtocol: public BaseProtocol {
private:
    std::unique_ptr<LobbyRequest> recv_create_game();
    std::unique_ptr<LobbyRequest> recv_join_game();

public:
    explicit ServerProtocol(Socket skt);

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    // Devuelven 1 si hubo un error en la comunicacion
    void send_mov(uint8_t type);
    uint8_t recv_msg();

    std::unique_ptr<LobbyRequest> recv_lobby_msg();

    void send_lobby_errormessage(uint8_t error_code);

    void send_gameid_message(size_t game_id);

    void send_gameslist(std::vector<GameInfo>& games_vec);
};

#endif  // SOCKETS_2023C2_ABRAIDA_SERVER_PROTOCOL_GAMEINTERFACE_H
