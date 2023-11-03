//
// Created by xguss on 10/09/23.
//

#include "server_protocol.h"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "game/server_beam_info.h"
#include "game/server_gameevent.h"
#include "game/server_gameinfo.h"
#include "game/server_worm_info.h"
#include "lobby/server_lobby_request.h"

#include "server_protocol_constants.h"
#include "utility"


enum Request {
    CREATE_GAME = LOBBY_CREATE_GAME,
    JOIN_GAME = LOBBY_JOIN_GAME,
    LIST_GAMES = LOBBY_LIST_GAMES,
};

enum Event {
    START_GAME = LOBBY_CREATE_GAME,
    MOVE = LOBBY_JOIN_GAME,
};

ServerProtocol::ServerProtocol(Socket skt): BaseProtocol(std::move(skt)) {}

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
    uint16_t id;
    recv_2byte_number(id);
    return std::make_unique<LobbyRequestJoinGame>(id);
}

void ServerProtocol::send_lobby_errormessage(uint8_t error_code) {
    send_1byte_number(LOBBY_SENDING);
    send_1byte_number(LOBBY_ERROR);
    send_1byte_number(error_code);
}

void ServerProtocol::send_gameid_message(uint16_t game_id) {
    send_1byte_number(LOBBY_SENDING);
    send_1byte_number(LOBBY_GAMEJOINING);
    send_2byte_number(game_id);
}

void ServerProtocol::send_gameslist(std::vector<GameInfo>& games_vec) {
    send_1byte_number(LOBBY_SENDING);
    send_1byte_number(LOBBY_GAMELISTING);

    send_2byte_number(games_vec.size());

    for (auto& game: games_vec) {
        send_2byte_number(game.id);
        send_2byte_number(game.scenario.length());

        std::vector<char> buffer(game.scenario.c_str(),
                                 game.scenario.c_str() + game.scenario.length());
        send_char_vector(buffer);
    }
}

std::unique_ptr<GameEvent> ServerProtocol::recv_game_msg(uint16_t id_client) {
    u_int8_t status = 0;
    recv_1byte_number(status);

    if (status != GAME_RECEIVING)
        throw InvalidMsg();

    recv_1byte_number(status);

    switch (status) {
        case Event::START_GAME:
            return std::make_unique<GameEventStartGame>(id_client);
        case Event::MOVE:
            return recv_move(id_client);
        default:
            return nullptr;
    }
}

std::unique_ptr<GameEvent> ServerProtocol::recv_move(uint16_t id_client) {
    uint8_t id_worm;
    recv_1byte_number(id_worm);
    uint8_t code;
    recv_1byte_number(code);

    MovementEnum type = serialize_move(code);

    return std::make_unique<GameEventMove>(id_client, id_worm, type);
}


MovementEnum ServerProtocol::serialize_move(uint8_t code) {
    switch (code) {
        case 01:
            return MovementEnum::Left;
        case 02:
            return MovementEnum::Right;
        case 03:
            return MovementEnum::Stop;
        case 04:
            return MovementEnum::JumpF;
        case 05:
            return MovementEnum::JumpB;
        default:
            throw InvalidMsg();
    }
}

void ServerProtocol::send_scenario(std::vector<BeamInfo>& beams_vec,
                                   std::vector<WormInfo>& worms_vec) {
    send_1byte_number(GAME_SENDING);
    send_1byte_number(GAME_SCENARIO);

    send_1byte_number(beams_vec.size());

    for (auto& beam: beams_vec) {
        send_4byte_float(beam.x);
        send_4byte_float(beam.y);
        send_4byte_float(beam.height);
        send_4byte_float(beam.width);
        send_4byte_float(beam.angle);
    }

    send_1byte_number(worms_vec.size());

    for (auto& worm: worms_vec) {
        send_1byte_number(worm.id);
        send_4byte_float(worm.x);
        send_4byte_float(worm.y);
        send_1byte_number(worm.state);
        send_1byte_number(worm.health);
    }
}

void ServerProtocol::send_worms_list(std::vector<WormInfo>& worms_vec) {
    send_1byte_number(GAME_SENDING);
    send_1byte_number(GAME_LIST_WORMS);

    send_1byte_number(worms_vec.size());

    for (auto& worm: worms_vec) {
        send_1byte_number(worm.id);
        send_2byte_number(worm.client_id);
    }
}

void ServerProtocol::send_status(uint8_t current_worm, std::vector<WormInfo>& worms_vec) {
    send_1byte_number(GAME_SENDING);
    send_1byte_number(GAME_STATUS);

    send_1byte_number(current_worm);

    send_1byte_number(worms_vec.size());

    for (auto& worm: worms_vec) {
        send_1byte_number(worm.id);
        send_4byte_float(worm.x);
        send_4byte_float(worm.y);
        send_1byte_number(worm.state);
        send_1byte_number(worm.health);
    }
}
