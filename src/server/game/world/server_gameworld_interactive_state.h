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

public:
    GameWorldInteractiveState(std::map<uint16_t, Worm*>::iterator active_worm,
                              std::map<uint16_t, Worm*>& worm_map, GameWorld& world);
    std::unique_ptr<GameWorldState> update() override;
    void handle_weapon_fired() override;

    void handle_worm_damaged(uint16_t worm_id) override;

    void handle_entity_moving() override;
};

#endif  // WORMS_SERVER_GAMEWORLD_INTERACTIVE_STATE_H
