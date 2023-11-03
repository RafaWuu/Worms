//
// Created by xguss on 03/10/23.
//

#include "server_client.h"

#include <memory>

#include "lobby/server_clientstate_lobby.h"

#include "utility"

Client::Client(uint16_t id, Socket socket, LobbyMonitor& lobby):
        game_protocol(std::move(socket)),
        lobby(lobby),
        state(std::make_unique<LobbyClientState>(id, lobby, game_protocol)),
        is_alive(true),
        client_id(id) {}

void Client::run() {
    while (is_alive) {
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
    game_protocol.kill();
}

void Client::reap_connection() {
    is_alive = false;

    if (state)
        this->state->kill();
}
