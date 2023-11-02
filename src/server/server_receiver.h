//
// Created by xguss on 03/10/23.
//

#ifndef THREADS_SERVER_RECEIVER_H
#define THREADS_SERVER_RECEIVER_H

#include <atomic>
#include <queue>

#include "../common/common_queue.h"
#include "../common/common_thread.h"

#include "server_protocol.h"

class Receiver: public Thread {
private:
    ServerProtocol& game_protocol;
    Queue<uint8_t>& outgoing_q;

    std::atomic<bool> is_alive;

public:
    Receiver(Queue<std::uint8_t>& outgoing_q, ServerProtocol& gp);
    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

    void run() override;

    void kill();

    bool is_dead();
};

#endif  // THREADS_SERVER_RECEIVER_H
