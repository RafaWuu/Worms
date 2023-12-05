

#ifndef THREADS_SERVER_ACCEPTOR_H
#define THREADS_SERVER_ACCEPTOR_H

#include <list>
#include <thread>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "lobby/server_lobby.h"

#include "server_client.h"

class Acceptor: public Thread {
private:
    Socket& sk_acceptor;
    LobbyMonitor& lobby;
    std::list<Client> clients_list;

    void reap_dead();
    void kill_all();
    size_t client_ids;

public:
    Acceptor(Socket&& sk, LobbyMonitor& lobby);
    Acceptor(const Acceptor&) = delete;

    Acceptor& operator=(const Acceptor&) = delete;
    ~Acceptor() override;
    void run() override;
    void kill();
};

#endif  // THREADS_SERVER_ACCEPTOR_H
