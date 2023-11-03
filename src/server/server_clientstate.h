//
// Created by xguss on 31/10/23.
//

#ifndef WORMS_SERVER_CLIENTSTATE_H
#define WORMS_SERVER_CLIENTSTATE_H

#include <atomic>
#include <memory>

#include "server_protocol.h"

class ClientState {
protected:
    std::atomic<bool> is_alive;
    ServerProtocol& gp;
    uint16_t client_id;

public:
    ClientState(uint16_t client_id, ServerProtocol& gp);
    virtual std::unique_ptr<ClientState> run() = 0;
    virtual void kill() = 0;
    virtual bool is_dead() = 0;
    virtual ~ClientState() = default;
};


#endif  // WORMS_SERVER_CLIENTSTATE_H
