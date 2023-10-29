//
// Created by xguss on 03/10/23.
//

#ifndef THREADS_SERVER_ACCEPTOR_H
#define THREADS_SERVER_ACCEPTOR_H

#include <list>
#include <thread>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "server_clienthandler.h"

class Lobby: public Thread {
private:
    Socket& sk_acceptor;
    std::list<ClientHandler> clients_list;

    std::atomic<bool> is_alive;

    void reap_dead();
    void kill_all();

public:
    explicit Lobby(Socket&& sk);
    Lobby(const Lobby&) = delete;

    Lobby& operator=(const Lobby&) = delete;
    ~Lobby() override;
    void run() override;
    void kill();
};

#endif  // THREADS_SERVER_ACCEPTOR_H
