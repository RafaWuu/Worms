#include "server_sender.h"

#include "../common/common_queue.h"

//
// Created by xguss on 03/10/23.
//
Sender::Sender(Queue<std::uint8_t>& queue, ServerProtocol& gp):
        game_protocol(gp), outgoing_q(queue), is_alive(true) {}

void Sender::run() {
    while (is_alive) {
        try {
            uint8_t msg = outgoing_q.pop();
            game_protocol.send_mov(msg);

        } catch (ClosedSocket& e) {
            is_alive = false;
        } catch (ClosedQueue& e) {
            is_alive = false;
        }
    }
}

void Sender::kill() {
    is_alive = false;
    outgoing_q.close();
}

bool Sender::is_dead() { return not is_alive; }
