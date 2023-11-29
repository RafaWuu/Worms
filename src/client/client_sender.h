#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <memory>
#include <vector>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "commands/client_command.h"

#include "client_protocol.h"

class ClientSender: public Thread {

private:
    ClientProtocol& protocol;

    // Por ahora que sea un array de chars, despues cambiarlo a una clase propia
    Queue<std::shared_ptr<Command>>& messages_to_send;

    std::atomic<bool> keep_talking;

    uint16_t worm;

public:
    ClientSender(ClientProtocol& protocol, Queue<std::shared_ptr<Command>>& messages_to_send);
    void run() override;
    bool is_dead();

    void kill();

    void set_current_worm(uint16_t current_worm);
};

#endif
