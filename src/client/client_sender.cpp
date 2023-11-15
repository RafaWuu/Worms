#include "client_sender.h"

ClientSender::ClientSender(ClientProtocol& protocol,
                           Queue<std::shared_ptr<Command>>& messages_to_send):
        protocol(protocol), messages_to_send(messages_to_send) {}

void ClientSender::run() {
    is_alive = keep_talking = true;

    bool was_closed = false;
    while (keep_talking) {
        try {
            std::shared_ptr<Command> command = messages_to_send.pop();
            command->serialize(protocol);

        } catch (ClosedSocket& e) {
            is_alive = keep_talking = false;
        } catch (ClosedQueue& e) {
            is_alive = keep_talking = false;
        }
    }

    is_alive = false;
}

void ClientSender::kill() { keep_talking = false; }

bool ClientSender::is_dead() { return not is_alive; }
