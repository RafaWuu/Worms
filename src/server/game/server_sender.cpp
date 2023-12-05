#include "server_sender.h"

#include <memory>

#include "../../common/common_queue.h"

Sender::Sender(Queue<std::shared_ptr<GameStatus>>& queue, ServerProtocol& gp):
        game_protocol(gp), outgoing_q(queue) {}

void Sender::run() {
    while (_is_alive) {
        try {
            auto status = outgoing_q.pop();
            status->serialize(game_protocol);

        } catch (ClosedSocket& e) {
            _is_alive = false;
        } catch (ClosedQueue& e) {
            _is_alive = false;
        }
    }
}

void Sender::kill() { _is_alive = false; }

bool Sender::is_dead() { return not _is_alive; }
