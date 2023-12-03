//
// Created by xguss on 28/11/23.
//

#include "server_gameworld_state.h"

GameWorldState::GameWorldState(PlayerManager& player_manager, GameWorld& world):
        player_manager(player_manager), world(world) {}
