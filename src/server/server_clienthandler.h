//
// Created by xguss on 03/10/23.
//

#ifndef THREADS_SERVER_CLIENTHANDLER_H
#define THREADS_SERVER_CLIENTHANDLER_H


#include <atomic>
#include <list>
#include <memory>
#include <queue>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "client_states/server_clientstate.h"
#include "client_states/server_clientstate_lobby.h"

#include "server_lobby.h"
#include "server_protocol.h"
#include "server_receiver.h"
#include "server_sender.h"

class ClientHandler: public Thread {
private:
    ServerProtocol game_protocol;
    Lobby& lobby;
    std::unique_ptr<ClientState> state;
    std::atomic<bool> is_alive;
    size_t client_id;

public:
    friend LobbyClientState;

    explicit ClientHandler(size_t id, Socket socket, Lobby& lobby);
    ClientHandler(const ClientHandler&) = delete;
    ClientHandler& operator=(const ClientHandler&) = delete;

    void run() override;

    bool is_dead();

    void kill_connection();

    void reap_connection();
};


#endif  // THREADS_SERVER_CLIENTHANDLER_H
