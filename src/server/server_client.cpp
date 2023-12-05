

#include "server_client.h"

#include <memory>

#include "lobby/server_clientstate_lobby.h"

#include "utility"

Client::Client(uint16_t id, Socket socket, LobbyMonitor& lobby):
        bp(std::move(socket)),
        game_protocol(bp),
        lobby(lobby),
        state(std::make_unique<LobbyClientState>(id, lobby, game_protocol)),
        client_id(id) {}

void Client::run() {
    while (_is_alive) {
        this->state = this->state->run();
        if (!this->state)
            _is_alive = false;
    }
}

bool Client::is_dead() { return !_is_alive; }

void Client::kill_connection() {
    _is_alive = false;

    if (state)
        this->state->kill();
    bp.kill();
}

void Client::reap_connection() {
    _is_alive = false;

    if (state)
        this->state->kill();
}
