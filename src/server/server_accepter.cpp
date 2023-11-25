//
// Created by xguss on 03/10/23.
//

#include "server_accepter.h"

#include <utility>

#include <sys/socket.h>

#include "lobby/server_lobby.h"

Acceptor::Acceptor(Socket&& sk, LobbyMonitor& lobby):
        sk_acceptor(sk), lobby(lobby), is_alive(true), client_ids(0) {}

Acceptor::~Acceptor() { kill_all(); }

void Acceptor::run() {
    while (is_alive) {
        try {
            Socket peer = sk_acceptor.accept();

            auto& client_handler = clients_list.emplace_back(client_ids, std::move(peer), lobby);
            client_handler.start();
            client_ids++;
            reap_dead();
        } catch (ClosedSocket& e) {
            if (is_alive) {
                throw;  // Inesperado, dejo que run_expecting loggee
            }
        }
    }
}

void Acceptor::reap_dead() {
    clients_list.remove_if([](Client& c) {
        if (c.is_dead()) {
            c.reap_connection();
            c.join();
            return true;
        }
        return false;
    });
}
void Acceptor::kill_all() {
    for (auto& c: clients_list) {
        if (c.is_dead())
            c.reap_connection();
        else
            c.kill_connection();

        c.join();
    }
}

void Acceptor::kill() {
    is_alive = false;

    sk_acceptor.shutdown(SHUT_RDWR);
    sk_acceptor.close();
}
