

#ifndef WORMS_SERVER_GAMESTATUS_H
#define WORMS_SERVER_GAMESTATUS_H

#include <map>
#include <memory>
#include <vector>

#include "game/world/server_gameworld.h"

#include "server_protocol.h"
class ServerProtocol;

class GameStatus {

protected:
    std::map<uint16_t, std::shared_ptr<GameObjectInfo>> entities_info;

public:
    explicit GameStatus(GameWorld& world);
    virtual void serialize(ServerProtocol& protocol) = 0;
};

class GameStatusError: public GameStatus {
private:
    uint8_t code;

public:
    explicit GameStatusError(uint8_t code, GameWorld& world);

    void serialize(ServerProtocol& protocol) override;
};

class GameStatusScenario: public GameStatus {
private:
    float height;
    float width;

public:
    explicit GameStatusScenario(GameWorld& world);
    void serialize(ServerProtocol& protocol) override;
};

class GameStatusStart: public GameStatus {
private:
    std::map<uint16_t, std::shared_ptr<WormInfo>> worms_info;

public:
    explicit GameStatusStart(GameWorld& world);
    void serialize(ServerProtocol& protocol) override;
};

class GameStatusRunning: public GameStatus {
private:
    uint16_t current_worm;
    float wind;
    float remaining_round_time;

public:
    GameStatusRunning(GameWorld& world, uint16_t current_worm, float remaining_time);
    void serialize(ServerProtocol& protocol) override;
};

class GameStatusWaiting: public GameStatus {
private:
    uint16_t connected;

public:
    explicit GameStatusWaiting(GameWorld& world);
    void serialize(ServerProtocol& protocol) override;
};

class GameStatusFinished: public GameStatus {
private:
    uint16_t winner;

public:
    explicit GameStatusFinished(GameWorld& world, uint16_t winner);
    void serialize(ServerProtocol& protocol) override;
};
#endif  // WORMS_SERVER_GAMESTATUS_H
