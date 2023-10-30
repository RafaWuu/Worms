//
// Created by xguss on 24/09/23.
//

#include "server_server.h"

#include <iostream>
#include <utility>


#include "server_lobby.h"
#include "server_protocol.h"
#define CLOSE_CHAR 'q'

Server::Server(const std::string& port): sk(port.c_str()) {}

void Server::run() {
    Lobby acceptor(std::move(sk));
    acceptor.start();

    while (std::cin.get() != CLOSE_CHAR) {}

    acceptor.kill();
    acceptor.join();
}
