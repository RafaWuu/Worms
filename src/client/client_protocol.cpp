#include "client_protocol.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <arpa/inet.h>
#include <string.h>

#include "game/estado_juego.h"
#include "lobby/lobby_state.h"
#define SUCCESS 0
#define FAILURE 1

#define BYTE 1

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

ClientProtocol::ClientProtocol(Socket socket): BaseProtocol(std::move(socket)) {}
// lobby
void ClientProtocol::send_create_game(std::string& escenario) {
    send_1byte_number(LOBBY_SENDING);
    send_1byte_number(CREATE_CODE);

    send_2byte_number(escenario.length());

    getLog().write("Cliente crea partida\n");

    std::vector<char> nombre_escenario(escenario.begin(), escenario.end());
    send_char_vector(nombre_escenario);
}

LobbyState ClientProtocol::receive_confirmation() {
    // error
    // 89 01 x -> x 1byte (code de error)

    // partida creada/ unida correctamente
    // 89 03 id -> id 2 bytes
    LobbyState l;
    uint8_t lobby_receive_code;
    recv_1byte_number(lobby_receive_code);

    uint8_t action_code;
    recv_1byte_number(action_code);
    if (action_code == 1) {
        uint8_t error_code;
        recv_1byte_number(error_code);  // no deberia chequear quien lo llama?

        getLog().write("Cliente recibe error al crear partida\n");
        throw ErrorLobby();
    }

    uint16_t id;
    recv_2byte_number(id);

    getLog().write("Cliente recibe creacion de partida %hu exitosa \n", id);

    l.id = id;
    return l;
}

void ClientProtocol::receive_beam(std::vector<Beam> beams) {
    float x;
    float y;
    float height;
    float width;
    float angle;

    recv_4byte_float(x);
    recv_4byte_float(y);
    recv_4byte_float(height);
    recv_4byte_float(width);
    recv_4byte_float(angle);

    Beam beam(x, y, height, width, angle);
    beams.push_back(beam);

    getLog().write("Cliente recibe beam. x=%lf y=%lf\n", x, y);
}

std::map<uint8_t, uint16_t> ClientProtocol::receive_worms_distribution() {
    // 87 03 n_worms [... {worm_id, client_id} ...]

    std::map<uint8_t, uint16_t> distribution;

    uint8_t game_receiving_code;
    uint8_t distribution_receiving_code;
    recv_1byte_number(game_receiving_code);
    recv_1byte_number(distribution_receiving_code);

    uint8_t worms_number;
    recv_1byte_number(worms_number);
    for (int i = 0; i < worms_number; i++) {
        uint8_t id_worm;
        uint16_t id_client;
        recv_1byte_number(id_worm);
        recv_2byte_number(id_client);

        distribution.insert({id_worm, id_client});
    }

    return distribution;
}

Scenario ClientProtocol::receive_scenario() {
    uint8_t game_receiving_code;
    uint8_t scenario_receiving_code;
    recv_1byte_number(game_receiving_code);
    recv_1byte_number(scenario_receiving_code);

    uint8_t beams_number;
    recv_1byte_number(beams_number);
    std::vector<Beam> beams;
    for (int i = 0; i < beams_number; i++) {
        receive_beam(beams);
    }

    uint8_t worms_number;
    recv_1byte_number(worms_number);
    std::vector<Worm> worms;
    for (int i = 0; i < worms_number; i++) {
        receive_worm(worms);
    }

    Scenario scenario(beams, worms);
    return scenario;
}

void ClientProtocol::send_join_game(const int& id) {
    send_1byte_number(LOBBY_SENDING);
    send_1byte_number(JOIN_CODE);
    send_2byte_number(id);

    getLog().write("Cliente se une a partida %hu  \n", id);
}

void ClientProtocol::request_game_list() {
    send_1byte_number(LOBBY_SENDING);
    send_1byte_number(GAME_LIST_CODE);

    getLog().write("Cliente solicita lista de partidas\n");
}
LobbyState ClientProtocol::receive_game_list() {
    LobbyState l;

    uint8_t lobby_receive_code;
    recv_1byte_number(lobby_receive_code);

    uint8_t action_code;
    recv_1byte_number(action_code);

    uint16_t games_list_size;
    recv_2byte_number(games_list_size);

    for (int i = 0; i < games_list_size; i++) {

        uint16_t game_id;
        recv_2byte_number(game_id);

        uint16_t scenario_len;
        recv_2byte_number(game_id);

        std::vector<char> buff(scenario_len);
        recv_char_vector(buff);

        std::string scenario(buff.begin(), buff.end());

        std::pair<uint16_t, std::string> partida(game_id, scenario);
        l.game_list.emplace_back(partida);
    }

    getLog().write("Cliente recibe lista de partidas\n");

    return l;
}
void ClientProtocol::send_start_game() {
    send_1byte_number(GAME_SENDING);
    send_1byte_number(START_GAME_CODE);

    getLog().write("Cliente inicia la partidas\n");
}
// game
void ClientProtocol::receive_worm(std::vector<Worm>& worms) {
    uint8_t id;
    float x;
    float y;
    uint8_t dir;
    uint16_t state;
    uint8_t health;

    recv_1byte_number(id);
    recv_4byte_float(x);
    recv_4byte_float(y);
    recv_1byte_number(dir);

    recv_2byte_number(state);
    recv_1byte_number(health);

    Worm worm(id, x, y, dir, state, health);
    worms.push_back(worm);

    getLog().write("Cliente recibe gusano: id %hhu, x: %f, y: %f. Estado %hu \n", id, x, y, state);
}

EstadoJuego ClientProtocol::recv_msg() {
    uint8_t game_sending;
    recv_1byte_number(game_sending);
    uint8_t game_status;
    recv_1byte_number(game_status);
    uint8_t current_worm;
    recv_1byte_number(current_worm);

    std::vector<Worm> worms;
    uint8_t worms_number;
    recv_1byte_number(worms_number);
    for (int i = 0; i < worms_number; i++) {
        receive_worm(worms);
    }

    getLog().write("Cliente recibe estado de partida: %hhu gusanos vivos \n", worms_number);

    EstadoJuego estado(worms);
    return estado;
}

std::vector<uint8_t> ClientProtocol::serialize_move(int dir) {
    uint8_t direction = dir;

    // Falta enviar el worm_id
    std::vector<uint8_t> serialized_command = {GAME_SENDING, MOVE_CODE, worm_id, direction};

    getLog().write("Cliente serializando movimiento %hhu \n", direction);

    return serialized_command;
}

std::vector<uint8_t> ClientProtocol::serialize_stop_move() {
    // Falta enviar el worm_id
    std::vector<uint8_t> serialized_command = {GAME_SENDING, MOVE_CODE, worm_id, STOP_MOVE};

    getLog().write("Cliente serializando movimiento %hhu \n", STOP_MOVE);

    return serialized_command;
}

std::vector<uint8_t> ClientProtocol::serialize_jump(){

    // Falta enviar el worm_id
    std::vector<uint8_t> serialized_command = {GAME_SENDING, JUMP_CODE, worm_id};

    getLog().write("Cliente serializando salto \n");

    return serialized_command;
}

std::vector<uint8_t> ClientProtocol::serialize_rollback(){
    // Falta enviar el worm_id
    std::vector<uint8_t> serialized_command = {GAME_SENDING, ROLLBACK_CODE, worm_id};

    getLog().write("Cliente serializando salto hacia atras \n");

    return serialized_command;
}


Log& ClientProtocol::getLog() {
    static Log log_("../log/clientprotocol_log.txt");
    return log_;
}

void ClientProtocol::get_my_id(uint16_t& id) {
    uint8_t lobby_receiving_code;
    uint8_t id_receiving_code;
    recv_1byte_number(lobby_receiving_code);
    recv_1byte_number(id_receiving_code);

    recv_2byte_number(id);

    getLog().write("Cliente recibiendo id %hu \n", id);
}

void ClientProtocol::set_worm_id(uint16_t i) { worm_id = i; }

