//
// Created by xguss on 28/11/23.
//

#ifndef WORMS_SERVER_GAMEWORLD_INTERACTIVE_STATE_H
#define WORMS_SERVER_GAMEWORLD_INTERACTIVE_STATE_H

#include <memory>

#include "server_gameworld_state.h"

class GameWorldInteractiveState: public GameWorldState {
private:
    int round_length;
    int ticks;
    bool active_worm_used_weapon;
    bool active_worm_get_damaged;
    Worm& worm;

public:
    GameWorldInteractiveState(PlayerManager& player_manager, GameWorld& world);
    std::unique_ptr<GameWorldState> update() override;
    void handle_weapon_fired() override;

    void handle_worm_damaged(uint16_t worm_id) override;

    void handle_entity_moving() override;

    Worm& get_active_worm() override;

    float get_remaining_time() override;
};

#endif  // WORMS_SERVER_GAMEWORLD_INTERACTIVE_STATE_H
