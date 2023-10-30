#include "client_receiver.h"

#define MOVE_CODE 1

ClientReceiver::ClientReceiver(ClientProtocol& protocol, Queue<std::vector<uint8_t>>& messages_received):
        protocol(protocol), messages_received(messages_received) {}

void ClientReceiver::run() {
    is_alive = keep_talking = true;

    bool was_closed = false;
    while (keep_talking) {
    }

    is_alive = false;
}

void ClientReceiver::kill() { keep_talking = false; }

bool ClientReceiver::is_dead() { return not is_alive; }