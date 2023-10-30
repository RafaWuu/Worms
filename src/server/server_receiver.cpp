#include "server_receiver.h"

#include "../common/common_queue.h"

Receiver::Receiver(Queue<uint8_t>& outgoing_q,
                   ProtocolGameInterface& gp):
        game_protocol(gp), outgoing_q(outgoing_q), is_alive(true) {}

void Receiver::run() {
    while (is_alive) {
        try {
            uint8_t msg = game_protocol.recv_msg();
            outgoing_q.push(msg);
        } catch (ClosedSocket& e) {
            is_alive = false;
        } catch (ClosedQueue& e) {
            if (is_alive) {
                // Inesperado, dejo que run_expecting loggee,
                // podria ser que el broadcaste cerro mi queue por lenta
                is_alive = false;
                throw(e);
            }
        }
    }
}

void Receiver::kill() { is_alive = false; }

bool Receiver::is_dead() { return not is_alive; }
