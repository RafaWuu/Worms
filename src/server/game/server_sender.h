

#ifndef THREADS_SERVER_SENDER_H
#define THREADS_SERVER_SENDER_H

#include <atomic>
#include <memory>
#include <queue>

#include "../../common/common_queue.h"
#include "../../common/common_thread.h"
#include "../server_protocol.h"

#include "server_gamestatus.h"


class Sender: public Thread {
private:
    ServerProtocol& game_protocol;

    Queue<std::shared_ptr<GameStatus>>& outgoing_q;

public:
    Sender(Queue<std::shared_ptr<GameStatus>>& queue, ServerProtocol& gp);
    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    void run() override;

    void kill();

    bool is_dead();
};

#endif  // THREADS_SERVER_SENDER_H
