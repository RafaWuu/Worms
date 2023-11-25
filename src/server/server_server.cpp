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
        acc(std::move(sk), lobby) {}

void Server::run() {
    acc.start();
    game_reaper.start();
    while (std::cin.get() != CLOSE_CHAR) {}
    // minor: para mantener la simetría y ser purista de RAII, metan el .kill()/.join() del acceptor y del game_reaper aqui
    // o, si prefieren, starteen tanto acceptor como reaper en el constructor y destruyanlos en el destructor.
}

Server::~Server() {
    acc.kill();
    game_reaper.kill();

    acc.join();
    game_reaper.join();
}
