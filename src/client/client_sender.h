#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "../common/common_queue.h"
#include "client_protocol.h"
#include "commands/client_command.h"

class ClientSender : public Thread {

private:
    ClientProtocol& protocol;

    // Por ahora que sea un array de chars, despues cambiarlo a una clase propia
    Queue<std::shared_ptr<Command>>& messages_to_send;

    std::atomic<bool> keep_talking;
    std::atomic<bool> is_alive;

public:
    ClientSender(ClientProtocol& protocol, Queue<std::shared_ptr<Command>>& messages_to_send);

    void run() override;
    bool is_dead();
    void kill();
};