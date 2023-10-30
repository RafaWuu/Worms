#include "client_sender.h"

ClientSender::ClientSender(ClientProtocol& protocol, Queue<std::vector<uint8_t>>& messages_to_send):
        protocol(protocol), messages_to_send(messages_to_send) {}

void ClientSender::run() {
    is_alive = keep_talking = true;

    bool was_closed = false;
    while (keep_talking) {
        try {
            std::vector<uint8_t> action = messages_to_send.pop();
            uint8_t action_code = action[0];
            uint8_t action_arg = action[1];
            if (action_code == 0x01) {
                protocol.send_move(action_arg);
            }

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