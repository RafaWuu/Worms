

#ifndef WORMS_SERVER_GAMEWORLD_STATE_FINISHED_H
#define WORMS_SERVER_GAMEWORLD_STATE_FINISHED_H

#include <memory>

#include "server_gameworld_state.h"
class GameWorldFinishedState: public GameWorldState {
private:
    Worm& worm;
    int ticks;
    int lifespan;
    uint16_t winner;

public:
    GameWorldFinishedState(PlayerManager& player_manager, Worm& worm, GameWorld& world,
                           uint16_t winner);
    std::unique_ptr<GameWorldState> update() override;
    void handle_weapon_fired() override;

    void handle_worm_damaged(uint16_t worm_id) override;

    void handle_entity_moving() override;

    Worm& get_active_worm() override;
    float get_remaining_time() override;
    std::shared_ptr<GameStatus> get_status() override;
};

#endif  // WORMS_SERVER_GAMEWORLD_STATE_FINISHED_H
