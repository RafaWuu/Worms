#include "client_sender.h"

ClientSender::ClientSender(ClientProtocol& protocol,
                           Queue<std::shared_ptr<Command>>& messages_to_send):
        protocol(protocol), messages_to_send(messages_to_send), worm(0) {}

void ClientSender::run() {
    _is_alive = keep_talking = true;

    bool was_closed = false;
    while (keep_talking) {
        try {

            std::shared_ptr<Command> command = messages_to_send.pop();
            command->serialize(worm, protocol);

        } catch (ClosedSocket& e) {
            _is_alive = keep_talking = false;
        } catch (ClosedQueue& e) {
            _is_alive = keep_talking = false;
        }
    }

    _is_alive = false;
}

void ClientSender::set_current_worm(uint16_t current_worm) { worm = current_worm; }


void ClientSender::kill() { keep_talking = false; }

bool ClientSender::is_dead() { return not _is_alive; }
