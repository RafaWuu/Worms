//
// Created by xguss on 03/10/23.
//

#include "server_clienthandler.h"

#include <memory>

#include "client_states/server_clientstate_lobby.h"

#include "utility"

ClientHandler::ClientHandler(size_t id, Socket socket, Lobby& lobby):
        game_protocol(std::move(socket)),
        lobby(lobby),
        state(nullptr),
        is_alive(true),
        client_id(id) {}

void ClientHandler::run() {
    this->state = std::make_unique<LobbyClientState>(lobby, game_protocol);

    while (is_alive) {
        this->state = this->state->run();
        if (!this->state)
            is_alive = false;
    }
}

bool ClientHandler::is_dead() { return !is_alive; }

void ClientHandler::kill_connection() {
    is_alive = false;

    if (state)
        this->state->kill();
    game_protocol.kill();
}

void ClientHandler::reap_connection() {
    is_alive = false;

    if (state)
        this->state->kill();
}
