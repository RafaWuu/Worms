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
#include "game/server_sender.h"
#include "lobby/server_clientstate_lobby.h"
#include "lobby/server_lobby.h"

#include "server_clientstate.h"
#include "server_protocol.h"

class Client: public Thread {
private:
    SocketBaseProtocol bp;
    ServerProtocol game_protocol;
    LobbyMonitor& lobby;
    std::unique_ptr<ClientState> state;
    std::atomic<bool> is_alive;
    uint16_t client_id;

public:
    friend LobbyClientState;

    explicit Client(uint16_t id, Socket socket, LobbyMonitor& lobby);
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    void run() override;

    bool is_dead();

    void kill_connection();

    void reap_connection();
};


#endif  // THREADS_SERVER_CLIENTHANDLER_H
