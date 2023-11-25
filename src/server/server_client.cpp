//
// Created by xguss on 03/10/23.
//

#include "server_client.h"

#include <memory>

#include "lobby/server_clientstate_lobby.h"

#include "utility"

Client::Client(uint16_t id, Socket socket, LobbyMonitor& lobby):
        bp(std::move(socket)),
        game_protocol(bp),
        lobby(lobby),
        state(std::make_unique<LobbyClientState>(id, lobby, game_protocol)),
        is_alive(true),
        client_id(id) {}

void Client::run() {
    while (is_alive) {
        // Excelente, a esto me referia cuando les comente lo de los estados del cliente!
        // bonus points (si llegan solamente!!!) -> pueden tener un estado ContinuePlaying que pueda volver a mandarlos al Lobby o desconectarlos
        // segun lo que el cliente elija
        this->state = this->state->run();
        if (!this->state)
            is_alive = false;
    }
}

bool Client::is_dead() { return !is_alive; }

void Client::kill_connection() {
    is_alive = false;

    if (state)
        this->state->kill();
    bp.kill();
}

void Client::reap_connection() {
    is_alive = false;

    if (state)
        this->state->kill();
}
