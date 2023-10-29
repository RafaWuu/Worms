//
// Created by xguss on 03/10/23.
//

#ifndef THREADS_SERVER_CLIENTHANDLER_H
#define THREADS_SERVER_CLIENTHANDLER_H


#include <atomic>
#include <list>
#include <queue>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "server_protocol.h"
#include "server_receiver.h"
#include "server_sender.h"

class ClientHandler {
private:
    ProtocolGameInterface game_protocol;
    Queue<std::uint8_t> outgoing_q;
    Sender sender;
    Receiver receiver;

public:
    explicit ClientHandler(Socket socket);
    ClientHandler(const ClientHandler&) = delete;
    ClientHandler& operator=(const ClientHandler&) = delete;

    ~ClientHandler() = default;

    void start_all();

    void kill_both();

    bool is_dead();

    void join_both();

    void close_socket();

    void kill_connection();

    void reap_connection();
};


#endif  // THREADS_SERVER_CLIENTHANDLER_H
