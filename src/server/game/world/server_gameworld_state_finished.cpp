//
// Created by xguss on 04/12/23.
//

#include "server_gameworld_state_finished.h"

GameWorldFinishedState::GameWorldFinishedState(PlayerManager& player_manager, Worm& worm,
                                               GameWorld& world, uint16_t winner):
        worm(worm),
        ticks(0),
        lifespan(5 * Configuration::get_instance().get_tick_rate()),
        GameWorldState(player_manager, world) {
    this->winner = winner;
}

std::unique_ptr<GameWorldState> GameWorldFinishedState::update() {
    ticks++;
    if (ticks > lifespan)
        return nullptr;
    return std::make_unique<GameWorldFinishedState>(*this);
}

void GameWorldFinishedState::handle_weapon_fired() {}

void GameWorldFinishedState::handle_worm_damaged(uint16_t worm_id) {}

void GameWorldFinishedState::handle_entity_moving() {}

Worm& GameWorldFinishedState::get_active_worm() { return worm; }

float GameWorldFinishedState::get_remaining_time() { return 0; }

std::shared_ptr<GameStatus> GameWorldFinishedState::get_status() {
    return std::make_shared<GameStatusFinished>(world, winner);
}