

#ifndef WORMS_SERVER_CLIENTSTATE_GAME_H
#define WORMS_SERVER_CLIENTSTATE_GAME_H


#include <cstdint>
#include <memory>

#include "../../common/common_queue.h"
#include "../server_clientstate.h"
#include "../server_protocol.h"

#include "server_game.h"
#include "server_sender.h"

class GameClientState: public ClientState {
private:
    Game& game;
    Queue<std::shared_ptr<GameStatus>> outgoing_q;
    Sender sender;

public:
    explicit GameClientState(uint16_t client_id, ServerProtocol& gameProtocol, Game& game);
    std::unique_ptr<ClientState> run() override;
    void kill() override;
    bool is_dead() override;
    ~GameClientState() override;
};


#endif  // WORMS_SERVER_CLIENTSTATE_GAME_H
