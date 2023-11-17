//
// Created by xguss on 10/09/23.
//

#include "server_protocol.h"

#include <memory>
#include <stdexcept>
#include <vector>

#include "../common/common_protocol_constants.h"
#include "game/entities/server_worm_info.h"
#include "game/server_gameevent.h"
#include "game/server_gameinfo.h"
#include "lobby/server_lobby_request.h"

#include "server_error.h"
#include "utility"


ServerProtocol::ServerProtocol(BaseProtocol& bp): baseProtocol(bp) {}

void ServerProtocol::send_lobby_newclient(uint16_t id) {
    baseProtocol.send_1byte_number(LOBBY_SENDING);
    baseProtocol.send_1byte_number(LOBBY_NEWCLIENT);
    baseProtocol.send_2byte_number(id);

    getLog().write("Server enviando id de cliente %hu \n", id);
}

std::unique_ptr<LobbyRequest> ServerProtocol::recv_lobby_msg() {
    u_int8_t status = 0;
    baseProtocol.recv_1byte_number(status);

    if (status != LOBBY_RECEIVING)
        throw InvalidMsg();

    baseProtocol.recv_1byte_number(status);

    switch (status) {
        case Request::CREATE_GAME:
            return recv_create_game();
        case Request::JOIN_GAME:
            return recv_join_game();
        case Request::LIST_GAMES:
            getLog().write("Server recibe pedido de listar partidas");

            return std::make_unique<LobbyRequestListGames>();
        default:
            throw InvalidMsg();
    }
}

std::unique_ptr<LobbyRequest> ServerProtocol::recv_create_game() {
    uint16_t l;
    baseProtocol.recv_2byte_number(l);
    std::vector<char> v(l);

    if (l == 0)
        throw InvalidMsg();

    baseProtocol.recv_char_vector(v);

    std::string s(v.data(), l);
    getLog().write("Server recibe creacion de partida, escenario %s\n", s.c_str());

    return std::make_unique<LobbyRequestNewGame>(s);
}

std::unique_ptr<LobbyRequest> ServerProtocol::recv_join_game() {
    uint16_t id;
    baseProtocol.recv_2byte_number(id);
    getLog().write("Server recibe union a partida, id %hu\n", id);

    return std::make_unique<LobbyRequestJoinGame>(id);
}

void ServerProtocol::send_lobby_errormessage(uint8_t error_code) {
    baseProtocol.send_1byte_number(LOBBY_SENDING);
    baseProtocol.send_1byte_number(LOBBY_ERROR);
    baseProtocol.send_1byte_number(error_code);

    getLog().write("Server enviando codigo de error %hhu \n", error_code);
}

void ServerProtocol::send_gameid_message(uint16_t game_id) {
    baseProtocol.send_1byte_number(LOBBY_SENDING);
    baseProtocol.send_1byte_number(LOBBY_GAMEJOINING);
    baseProtocol.send_2byte_number(game_id);

    getLog().write("Server enviando id de partidas %hu \n", game_id);
}

void ServerProtocol::send_gameslist(std::vector<GameInfo>& games_vec) {
    baseProtocol.send_1byte_number(LOBBY_SENDING);
    baseProtocol.send_1byte_number(LOBBY_GAMELISTING);

    baseProtocol.send_2byte_number(games_vec.size());

    getLog().write("Server enviando lista de %hu partidas \n", games_vec.size());

    for (auto& game: games_vec) {
        game.serialize(baseProtocol);
    }
}

std::unique_ptr<GameEvent> ServerProtocol::recv_game_msg(uint16_t id_client) {
    u_int8_t status = 0;
    baseProtocol.recv_1byte_number(status);

    if (status != GAME_RECEIVING) {

        throw InvalidMsg();
    }

    baseProtocol.recv_1byte_number(status);

    switch (status) {
        case Input::StartGame:
            getLog().write("Server recibiendo de  %hu "
                           "pedido de iniciar partida \n",
                           id_client);

            return std::make_unique<GameEventStartGame>(id_client);
        case Input::Move:
            return recv_move(id_client);
        case Input::Jump:
            return recv_jump(id_client);
        case Input::Rollback:
            return recv_rollback(id_client);
        case Input::Fire:
            return recv_fire(id_client);
        case Input::Aim:
            return recv_aim(id_client);
        case Input::Power:
            return recv_power(id_client);
        case Input::DirAttack:
            return recv_aim(id_client);
        case Input::CountDown:
            return recv_move(id_client);
        case Input::SelectGun:
            return recv_move(id_client);

        default:
            throw InvalidMsg();
    }
}

std::unique_ptr<GameEvent> ServerProtocol::recv_move(uint16_t id_client) {
    uint8_t id_worm;
    baseProtocol.recv_1byte_number(id_worm);
    uint8_t code;
    baseProtocol.recv_1byte_number(code);

    getLog().write("Server recibiendo de  %hu "
                   "pedido de mover %hhu. code(%hhu)\n",
                   id_client, id_worm, code);

    switch (code) {
        case MoveEnum::MoveLeft:
            return std::make_unique<GameEventMove>(id_client, id_worm, DirLeft);
        case MoveEnum::MoveRight:
            return std::make_unique<GameEventMove>(id_client, id_worm, DirRight);
        case MoveEnum::StopMove:
            return std::make_unique<GameEventStop>(id_client, id_worm);
        default:
            throw InvalidMsg();
    }
}

std::unique_ptr<GameEvent> ServerProtocol::recv_jump(uint16_t id_client) {
    uint8_t id_worm;
    baseProtocol.recv_1byte_number(id_worm);

    return std::make_unique<GameEventJump>(id_client, id_worm);
}

std::unique_ptr<GameEvent> ServerProtocol::recv_rollback(uint16_t id_client) {
    uint8_t id_worm;
    baseProtocol.recv_1byte_number(id_worm);

    return std::make_unique<GameEventRollBack>(id_client, id_worm);
}

std::unique_ptr<GameEvent> ServerProtocol::recv_fire(uint16_t id_client) {
    uint8_t id_worm;
    baseProtocol.recv_1byte_number(id_worm);

    return std::make_unique<GameEventFireGun>(id_client, id_worm);
}

std::unique_ptr<GameEvent> ServerProtocol::recv_aim(uint16_t id_client) {
    uint8_t id_worm;
    baseProtocol.recv_1byte_number(id_worm);

    uint8_t how;
    baseProtocol.recv_1byte_number(how);

    switch (how) {
        case AimType::AimUp:
            float x;
            float y;

            baseProtocol.recv_4byte_float(x);
            baseProtocol.recv_4byte_float(y);

            return std::make_unique<GameEventAim>(id_client, id_worm, x, y);
        case AimType::AimStop:
            return std::make_unique<GameEventAimStop>(id_client, id_worm);
        default:
            throw InvalidMsg();
    }
}

std::unique_ptr<GameEvent> ServerProtocol::recv_power(uint16_t id_client) {
    uint8_t id_worm;
    baseProtocol.recv_1byte_number(id_worm);

    uint8_t how;
    baseProtocol.recv_1byte_number(how);

    switch (how) {
        case PowerType::PowerUp:
            return std::make_unique<GameEventPower>(id_client, id_worm, true);
        case PowerType::PowerDown:
            return std::make_unique<GameEventPower>(id_client, id_worm, false);
        case PowerType::PowerStop:
            return std::make_unique<GameEventPowerStop>(id_client, id_worm);
        default:
            throw InvalidMsg();
    }
}


void ServerProtocol::send_game_errormessage(uint8_t error_code) {
    baseProtocol.send_1byte_number(GAME_SENDING);
    baseProtocol.send_1byte_number(GAME_ERROR);
    baseProtocol.send_1byte_number(error_code);

    getLog().write("Server juego enviando codigo de error %hhu \n", error_code);
}


void ServerProtocol::send_scenario(std::map<uint16_t, std::shared_ptr<GameObjectInfo>>& entities,
                                   float height, float width) {
    baseProtocol.send_1byte_number(GAME_SENDING);
    baseProtocol.send_1byte_number(GAME_SCENARIO);

    baseProtocol.send_4byte_float(height);
    baseProtocol.send_4byte_float(width);

    baseProtocol.send_2byte_number(entities.size());

    for (auto& e: entities) {
        baseProtocol.send_2byte_number(e.first);
        e.second->serialize_scenario(baseProtocol);
    }

    getLog().write("Server enviando escenario \n");
}

void ServerProtocol::send_worms_list(const std::map<uint16_t, std::shared_ptr<WormInfo>>& worms) {
    baseProtocol.send_1byte_number(GAME_SENDING);
    baseProtocol.send_1byte_number(GAME_LIST_WORMS);

    baseProtocol.send_2byte_number(worms.size());

    for (auto& e: worms) {
        e.second->serialize_start(baseProtocol);
    }

    getLog().write("Server enviando lista de gusanos \n");
}

void ServerProtocol::send_status(uint16_t current_worm,
                                 std::map<uint16_t, std::shared_ptr<GameObjectInfo>> entities) {
    baseProtocol.send_1byte_number(GAME_SENDING);
    baseProtocol.send_1byte_number(GAME_STATUS);

    baseProtocol.send_2byte_number(current_worm);

    baseProtocol.send_2byte_number(entities.size());

    for (auto& e: entities) {
        baseProtocol.send_2byte_number(e.first);
        e.second->serialize_status(baseProtocol);
    }

    // getLog().write("Server enviando estado de partida, %hhu gusanos vivos \n", worms_vec.size());
}

Log& ServerProtocol::getLog() {
    static Log log_(SERVERPROTOCOL_LOG_SRC);
    return log_;
}
