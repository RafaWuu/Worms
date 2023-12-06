

#include "server_server.h"

#include <iostream>
#include <utility>

#include "server_accepter.h"
#include "server_protocol.h"
#define CLOSE_CHAR 'q'

Server::Server(const std::string& port):
        sk(port.c_str()),
        reap_queue(),
        lobby(reap_queue),
        game_reaper(lobby, reap_queue),
        acc(std::move(sk), lobby) {
}

void Server::run() {
    acc.start();
    game_reaper.start();

    while (std::cin.get() != CLOSE_CHAR) {}

    acc.kill();
    acc.join();

    game_reaper.kill();
    game_reaper.join();
}

Server::~Server() {
}
