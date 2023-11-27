//
// Created by xguss on 24/09/23.
//

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

    acc.start();
    game_reaper.start();
}

void Server::run() {

    while (std::cin.get() != CLOSE_CHAR) {}
}

Server::~Server() {
    acc.kill();
    game_reaper.kill();

    acc.join();
    game_reaper.join();
}
