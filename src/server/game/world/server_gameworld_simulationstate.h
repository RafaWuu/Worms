//
// Created by xguss on 28/11/23.
//

#ifndef WORMS_SERVER_GAMEWORLD_SIMULATIONSTATE_H
#define WORMS_SERVER_GAMEWORLD_SIMULATIONSTATE_H

#include "server_gameworld_state.h"

class GameWorldSimulationState: public GameWorldState {
private:
    bool all_entities_had_stopped;

public:
    GameWorldSimulationState(std::map<uint16_t, Worm*>::iterator active_worm,
                             std::map<uint16_t, Worm*>& worm_map, bool grace_period);
    std::unique_ptr<GameWorldState> update() override;

    void handle_weapon_fired() override;

    void handle_worm_damaged(uint16_t worm_id) override;

    void handle_entity_moving() override;

    bool grace_period;
    int ticks;
    int round_length;
};

#endif  // WORMS_SERVER_GAMEWORLD_SIMULATIONSTATE_H
