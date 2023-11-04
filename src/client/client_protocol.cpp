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

#define SUCCESS 0
#define FAILURE 1

#define BYTE 1

#define GAME_SENDING 86
#define LOBBY_SENDING 88

#define CREATE_CODE 1
#define MOVE_CODE 1
#define STOP_MOVE 3

ClientProtocol::ClientProtocol(Socket socket): BaseProtocol(std::move(socket)) {}

void ClientProtocol::send_create_game(std::string& escenario) {
    send_1byte_number(LOBBY_SENDING);
    send_1byte_number(CREATE_CODE);

    send_2byte_number(escenario.length());

    std::vector<char> nombre_escenario(escenario.begin(), escenario.end());
    send_char_vector(nombre_escenario);
}

int16_t ClientProtocol::receive_confirmation_create() {
    // error 
    // 89 01 x -> x 1byte (code de error)

    // partida creada/ unida correctamente
    // 89 02 id -> id 2 bytes 

    uint8_t lobby_receive_code;
    recv_1byte_number(lobby_receive_code);

    uint8_t action_code;
    recv_1byte_number(action_code);
    if (action_code == 1) {
        uint8_t error_code;
        recv_1byte_number(error_code);
        throw ErrorLobby();
    }

    uint16_t id;
    recv_2byte_number(id);

    int16_t id_ = id;
    return id_;
}

void ClientProtocol::recv_worm(std::vector<Worm>& worms) {
    uint8_t id;
    float x;
    float y;
    uint8_t state;
    uint8_t health;

    recv_1byte_number(id);
    recv_4byte_float(x);
    recv_4byte_float(y);
    recv_1byte_number(state);
    recv_1byte_number(health);

    Worm worm(id, x, y, state, health);
    worms.push_back(worm);
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
        recv_worm(worms);
    }

    EstadoJuego estado(worms);
    return estado;
}

std::vector<uint8_t> ClientProtocol::serialize_move(int dir) {
    uint8_t direction = dir;

    // Falta enviar el worm_id
    std::vector<uint8_t> serialized_command = {GAME_SENDING, MOVE_CODE, direction};
    return serialized_command;
}

std::vector<uint8_t> ClientProtocol::serialize_stop_move() {
    // Falta enviar el worm_id
    std::vector<uint8_t> serialized_command = {GAME_SENDING, MOVE_CODE, STOP_MOVE};
    return serialized_command;
}
