//
// Created by xguss on 10/09/23.
//

#include "server_protocol.h"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "server_gameinfo.h"
#include "server_lobby_request.h"
#include "server_protocol_constants.h"
#include "utility"


enum Request {
    CREATE_GAME = LOBBY_CREATE_GAME,
    JOIN_GAME = LOBBY_JOIN_GAME,
    LIST_GAMES = LOBBY_LIST_GAMES,
};

ServerProtocol::ServerProtocol(Socket skt): BaseProtocol(std::move(skt)) {}

void ServerProtocol::send_mov(uint8_t type) {

    send_1byte_number(1);
    send_1byte_number(type);
}

uint8_t ServerProtocol::recv_msg() {
    u_int8_t status = 0;
    recv_1byte_number(status);

    if (status != 1)
        throw InvalidMsg();

    uint8_t type = 0;
    this->recv_1byte_number(type);

    return type;
}

std::unique_ptr<LobbyRequest> ServerProtocol::recv_lobby_msg() {
    u_int8_t status = 0;
    recv_1byte_number(status);

    if (status != LOBBY_RECEIVING)
        throw InvalidMsg();

    recv_1byte_number(status);

    switch (status) {
        case Request::CREATE_GAME:
            return recv_create_game();
        case Request::JOIN_GAME:
            return recv_join_game();
        case Request::LIST_GAMES:
            return std::make_unique<LobbyRequestListGames>();
        default:
            return nullptr;
    }
}

std::unique_ptr<LobbyRequest> ServerProtocol::recv_create_game() {
    uint16_t l;
    recv_2byte_number(l);
    std::vector<char> v(l);

    recv_char_vector(v);

    std::string s(v.data(), l);
    return std::make_unique<LobbyRequestNewGame>(s);
}

std::unique_ptr<LobbyRequest> ServerProtocol::recv_join_game() {
    uint32_t id;
    recv_4byte_number(id);
    return std::make_unique<LobbyRequestJoinGame>(id);
}

void ServerProtocol::send_lobby_errormessage(uint8_t error_code) {
    send_1byte_number(LOBBY_SENDING);
    send_1byte_number(LOBBY_ERROR);
    send_1byte_number(error_code);
}

void ServerProtocol::send_gameid_message(size_t game_id) {
    send_1byte_number(LOBBY_SENDING);
    send_1byte_number(LOBBY_GAMEJOINING);
    send_4byte_number(game_id);
}

void ServerProtocol::send_gameslist(std::vector<GameInfo>& games_vec) {
    send_1byte_number(LOBBY_SENDING);
    send_1byte_number(LOBBY_GAMELISTING);

    send_2byte_number(games_vec.size());

    for (auto& game: games_vec) {
        send_4byte_number(game.id);
        send_2byte_number(game.scenario.length());

        std::vector<char> buffer(game.scenario.c_str(),
                                 game.scenario.c_str() + game.scenario.length());
        send_char_vector(buffer);
    }
}
