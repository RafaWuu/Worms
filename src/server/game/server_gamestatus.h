//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_GAMESTATUS_H
#define WORMS_SERVER_GAMESTATUS_H


#include <vector>

#include "game/entities/server_beam_info.h"
#include "game/entities/server_worm_info.h"

#include "game/world/server_gameworld.h"
#include "server_protocol.h"

class ServerProtocol;

class GameStatus {

protected:
    std::vector<WormInfo> worm_info;

public:
    explicit GameStatus(GameWorld& world);
    virtual void serialize(ServerProtocol& protocol) = 0;
};

class GameStatusError: public GameStatus {
private:
    std::vector<BeamInfo> beam_info;
    uint8_t code;

public:
    explicit GameStatusError(uint8_t code, GameWorld& world);

    void serialize(ServerProtocol& protocol) override;
};

class GameStatusScenario: public GameStatus {
private:
    std::vector<BeamInfo> beam_info;

public:
    explicit GameStatusScenario(GameWorld& world);
    void serialize(ServerProtocol& protocol) override;
};

class GameStatusStart: public GameStatus {
private:
public:
    explicit GameStatusStart(GameWorld& world);
    void serialize(ServerProtocol& protocol) override;
};

class GameStatusRunning: public GameStatus {
private:
    uint8_t current_worm;

public:
    GameStatusRunning(uint8_t current_worm, GameWorld& world);
    void serialize(ServerProtocol& protocol) override;
};
#endif  // WORMS_SERVER_GAMESTATUS_H
