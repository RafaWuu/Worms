#include "client_sender.h"

ClientSender::ClientSender(ClientProtocol& protocol, Queue<std::vector<uint8_t>>& messages_to_send):
        protocol(protocol), messages_to_send(messages_to_send) {}

void ClientSender::run() {
    is_alive = keep_talking = true;

    bool was_closed = false;
    while (keep_talking) {
    }

    is_alive = false;
}

void ClientSender::kill() { keep_talking = false; }

bool ClientSender::is_dead() { return not is_alive; }