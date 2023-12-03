//
// Created by xguss on 28/11/23.
//

#include "server_gameworld_state.h"

GameWorldState::GameWorldState(std::map<uint16_t, Worm*>::iterator active_worm,
                               std::map<uint16_t, Worm*>& worm_map, GameWorld& world):
        active_worm(active_worm), worm_map(worm_map), world(world) {}
