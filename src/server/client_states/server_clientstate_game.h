//
// Created by xguss on 31/10/23.
//

#ifndef WORMS_SERVER_CLIENTSTATE_GAME_H
#define WORMS_SERVER_CLIENTSTATE_GAME_H


#include <cstdint>
#include <memory>

#include "../../common/common_queue.h"
#include "../server_game.h"
#include "../server_protocol.h"
#include "../server_sender.h"

#include "server_clientstate.h"

class GameClientState: public ClientState {
private:
    Queue<std::uint8_t> outgoing_q;
    ServerProtocol& gp;
    Sender sender;

public:
    explicit GameClientState(ServerProtocol& gameProtocol, Game& game);
    std::unique_ptr<ClientState> run() override;
    void kill() override;
    bool is_dead() override;
    ~GameClientState() override;
};


#endif  // WORMS_SERVER_CLIENTSTATE_GAME_H
