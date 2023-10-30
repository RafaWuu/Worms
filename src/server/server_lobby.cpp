//
// Created by xguss on 03/10/23.
//

#include "server_lobby.h"

#include <sys/socket.h>

#include "server_clienthandler.h"
#include "../common/common_baseprotocol.h"
#include "utility"

Lobby::Lobby(Socket&& sk):
        sk_acceptor(sk),
        is_alive(true) {}

Lobby::~Lobby() {
    kill_all();
}

void Lobby::run() {
    while (is_alive) {
        try {
            Socket peer = sk_acceptor.accept();

            auto& client_handler = clients_list.emplace_back(std::move(peer));
            client_handler.start_all();

            reap_dead();
        } catch (ClosedSocket& e) {
            if (is_alive) {
                throw(e);  // Inesperado, dejo que run_expecting loggee
            }
        }
    }
}

void Lobby::reap_dead() {
    clients_list.remove_if([](ClientHandler& c) {
        if (c.is_dead()) {
            c.reap_connection();

            return true;
        }
        return false;
    });
}
void Lobby::kill_all() {
    for (auto& c: clients_list) {
        if (c.is_dead())
            c.reap_connection();
        else
            c.kill_connection();
    }
}

void Lobby::kill() {
    is_alive = false;

    sk_acceptor.shutdown(SHUT_RDWR);
    sk_acceptor.close();
}
