

#include "server_gameworld_simulationstate.h"

#include <iostream>
#include <memory>

#include "server_gameworld.h"
#include "server_gameworld_interactive_state.h"
#include "server_gameworld_state_finished.h"
GameWorldSimulationState::GameWorldSimulationState(PlayerManager& player_manager, Worm& worm,
                                                   bool grace_period, GameWorld& world):
        grace_period(grace_period), worm(worm), GameWorldState(player_manager, world) {
    auto& config = Configuration::get_instance();

    ticks = 0;
    round_length = grace_period ? config.grace_length * config.get_tick_rate() : 0;

    all_entities_had_stopped = true;
}

std::unique_ptr<GameWorldState> GameWorldSimulationState::update() {
    ticks++;

    if (ticks > round_length)
        worm.set_deactive();

    if (all_entities_had_stopped) {
        worm.set_deactive();
        if (player_manager.game_ended())
            return std::make_unique<GameWorldFinishedState>(player_manager, worm, world,
                                                            player_manager.last_client_alive());

        world.on_new_round();
        return std::make_unique<GameWorldInteractiveState>(player_manager, world);
    }

    all_entities_had_stopped = true;
    return std::make_unique<GameWorldSimulationState>(*this);
}

void GameWorldSimulationState::handle_weapon_fired() {}

void GameWorldSimulationState::handle_worm_damaged(uint16_t worm_id) {}

void GameWorldSimulationState::handle_entity_moving() { all_entities_had_stopped = false; }

Worm& GameWorldSimulationState::get_active_worm() { return worm; }

float GameWorldSimulationState::get_remaining_time() {
    float remaining = (round_length - ticks) / Configuration::get_instance().get_tick_rate();
    return fmax(remaining, 0.0f);
}

std::shared_ptr<GameStatus> GameWorldSimulationState::get_status() {
    return std::make_shared<GameStatusRunning>(world, worm.id, get_remaining_time());
}
