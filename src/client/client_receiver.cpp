#include "client_receiver.h"

#define MOVE_CODE 1

ClientReceiver::ClientReceiver(ClientProtocol& protocol,
                               Queue<std::shared_ptr<EstadoJuego>>& messages_received):
        protocol(protocol), messages_received(messages_received) {}

void ClientReceiver::run() {
    is_alive = keep_talking = true;

    while (keep_talking) {
        EstadoJuego estado = protocol.recv_msg();
        std::shared_ptr<EstadoJuego> game_status = std::make_shared<EstadoJuego>(estado);
        messages_received.push(game_status);
    }

    is_alive = false;
}

void ClientReceiver::kill() { keep_talking = false; }

bool ClientReceiver::is_dead() { return not is_alive; }
