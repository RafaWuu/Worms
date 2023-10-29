//
// Created by xguss on 03/10/23.
//

#include "server_clienthandler.h"

#include "utility"


ClientHandler::ClientHandler(Socket socket):
        game_protocol(std::move(socket)),
        outgoing_q(),
        sender(outgoing_q, game_protocol),
        receiver(outgoing_q, game_protocol) {}

void ClientHandler::start_all() {
    this->sender.start();
    this->receiver.start();
}

bool ClientHandler::is_dead() { return receiver.is_dead() || sender.is_dead(); }

void ClientHandler::kill_both() {
    receiver.kill();
    sender.kill();
}

void ClientHandler::join_both() {
    receiver.join();
    sender.join();
}

void ClientHandler::close_socket() { game_protocol.kill(); }

void ClientHandler::kill_connection() {
    kill_both();
    close_socket();
    join_both();
}

void ClientHandler::reap_connection() {
    kill_both();  // Por si solo una de las dos conexiones termino
    join_both();
}
