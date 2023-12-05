

#include "server_gameworld_interactive_state.h"

#include <iostream>
#include <memory>

#include "server_gameworld.h"
#include "server_gameworld_simulationstate.h"
#include "server_gameworld_state.h"

GameWorldInteractiveState::GameWorldInteractiveState(PlayerManager& player_manager,
                                                     GameWorld& world):
        worm(player_manager.get_next_worm_from_client()), GameWorldState(player_manager, world) {
    auto& config = Configuration::get_instance();
    ticks = 0;
    round_length = config.round_length * config.get_tick_rate();
    active_worm_get_damaged = false;
    active_worm_used_weapon = false;

    worm.set_active();
    std::cout << "Empezando turno de " << unsigned(worm.id) << "\n";
}

std::unique_ptr<GameWorldState> GameWorldInteractiveState::update() {
    ticks++;
    if ((worm.get_state() & Alive) == 0)
        return std::make_unique<GameWorldSimulationState>(player_manager, worm, false, world);

    if (ticks > round_length || active_worm_get_damaged)
        return std::make_unique<GameWorldSimulationState>(player_manager, worm, false, world);


    if (active_worm_used_weapon) {
        return std::make_unique<GameWorldSimulationState>(player_manager, worm, true, world);
    }


    return std::make_unique<GameWorldInteractiveState>(*this);
}

void GameWorldInteractiveState::handle_weapon_fired() { active_worm_used_weapon = true; }

void GameWorldInteractiveState::handle_worm_damaged(uint16_t worm_id) {
    if (worm.id == worm_id)
        active_worm_get_damaged = true;
}

void GameWorldInteractiveState::handle_entity_moving() {}

Worm& GameWorldInteractiveState::get_active_worm() { return worm; }

float GameWorldInteractiveState::get_remaining_time() {
    float remaining = (round_length - ticks) / Configuration::get_instance().get_tick_rate();
    return fmax(remaining, 0.0f);
}

std::shared_ptr<GameStatus> GameWorldInteractiveState::get_status() {
    return std::make_shared<GameStatusRunning>(world, worm.id, get_remaining_time());
}
