//
// Created by xguss on 03/12/23.
//

#include "server_gameworld_state_waiting.h"


GameWorldWaitingState::GameWorldWaitingState(PlayerManager& player_manager, Worm& worm,
                                             GameWorld& world):
        worm(worm), GameWorldState(player_manager, world) {}

std::unique_ptr<GameWorldState> GameWorldWaitingState::update() {
    return std::make_unique<GameWorldWaitingState>(*this);
}

void GameWorldWaitingState::handle_weapon_fired() {}

void GameWorldWaitingState::handle_worm_damaged(uint16_t worm_id) {}

void GameWorldWaitingState::handle_entity_moving() {}

Worm& GameWorldWaitingState::get_active_worm() { return worm; }
