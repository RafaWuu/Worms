

#include "server_gameworld_state_waiting.h"

#include <memory>

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

float GameWorldWaitingState::get_remaining_time() { return 0; }

std::shared_ptr<GameStatus> GameWorldWaitingState::get_status() {
    return std::make_shared<GameStatusWaiting>(world);
}
