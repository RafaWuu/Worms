//
// Created by xguss on 28/11/23.
//

#ifndef WORMS_SERVER_GAMEWORLD_SIMULATIONSTATE_H
#define WORMS_SERVER_GAMEWORLD_SIMULATIONSTATE_H

#include "server_gameworld_state.h"

class GameWorldSimulationState: public GameWorldState {
private:
    bool all_entities_had_stopped;
    Worm& worm;
    bool grace_period;
    int ticks;
    int round_length;

public:
    GameWorldSimulationState(PlayerManager& player_manager, Worm& worm, bool grace_period,
                             GameWorld& world);
    std::unique_ptr<GameWorldState> update() override;

    void handle_weapon_fired() override;

    void handle_worm_damaged(uint16_t worm_id) override;

    void handle_entity_moving() override;

    Worm& get_active_worm() override;

    float get_remaining_time() override;

    std::shared_ptr<GameStatus> get_status() override;
};

#endif  // WORMS_SERVER_GAMEWORLD_SIMULATIONSTATE_H
