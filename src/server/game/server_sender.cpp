#include "server_sender.h"

#include <memory>

#include "../../common/common_queue.h"
//
// Created by xguss on 03/10/23.
//
Sender::Sender(Queue<std::shared_ptr<GameStatus>>& queue, ServerProtocol& gp):
        game_protocol(gp), outgoing_q(queue), is_alive(true) {}

void Sender::run() {
    while (is_alive) {
        try {
            auto status = outgoing_q.pop();
            status.get()->serialize(game_protocol);

        } catch (ClosedSocket& e) {
            is_alive = false;
        } catch (ClosedQueue& e) {
            is_alive = false;
        }
    }
}

void Sender::kill() { is_alive = false; }

bool Sender::is_dead() { return not is_alive; }
