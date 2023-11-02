//
// Created by xguss on 03/10/23.
//

#ifndef THREADS_SERVER_SENDER_H
#define THREADS_SERVER_SENDER_H

#include <atomic>
#include <queue>

#include "../common/common_queue.h"
#include "../common/common_thread.h"

#include "server_protocol.h"


class Sender: public Thread {
private:
    ServerProtocol& game_protocol;

    Queue<uint8_t>& outgoing_q;

    std::atomic<bool> is_alive;

public:
    Sender(Queue<uint8_t>& queue, ServerProtocol& gp);
    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    void run() override;

    void kill();

    bool is_dead();
};

#endif  // THREADS_SERVER_SENDER_H
