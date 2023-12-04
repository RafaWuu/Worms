#include "client_receiver.h"

ClientReceiver::ClientReceiver(ClientProtocol& protocol,
                               Queue<std::shared_ptr<EstadoJuego>>& messages_received):
        protocol(protocol), messages_received(messages_received) {}

void ClientReceiver::run() {
    is_alive = keep_talking = true;

    while (keep_talking) {
        try {

            std::shared_ptr<EstadoJuego> game_status = protocol.recv_snapshot();
            messages_received.push(game_status);

        } catch (ClosedSocket& e) {
            is_alive = keep_talking = false;
        } catch (ClosedQueue& e) {
            is_alive = keep_talking = false;
        }
    }

    is_alive = false;
}

void ClientReceiver::kill() { keep_talking = false; }

bool ClientReceiver::is_dead() { return not is_alive; }
