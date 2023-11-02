//
// Created by xguss on 31/10/23.
//

#ifndef WORMS_SERVER_CLIENTSTATE_H
#define WORMS_SERVER_CLIENTSTATE_H

#include <atomic>
#include <memory>

class ClientState {
protected:
    std::atomic<bool> is_alive;

public:
    ClientState();
    virtual std::unique_ptr<ClientState> run() = 0;
    virtual void kill() = 0;
    virtual bool is_dead() = 0;
    virtual ~ClientState() = default;
};


#endif  // WORMS_SERVER_CLIENTSTATE_H
