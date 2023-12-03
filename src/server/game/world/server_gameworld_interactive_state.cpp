//
// Created by xguss on 28/11/23.
//

#include "server_gameworld_interactive_state.h"

#include <iostream>
#include <memory>

#include "server_gameworld.h"
#include "server_gameworld_simulationstate.h"
#include "server_gameworld_state.h"

GameWorldInteractiveState::GameWorldInteractiveState(
        std::map<uint16_t, Worm*>::iterator active_worm, std::map<uint16_t, Worm*>& worm_map,
        GameWorld& world):
        GameWorldState(active_worm, worm_map, world) {
    auto& config = Configuration::get_instance();
    ticks = 0;
    round_length = config.round_length * config.get_tick_rate();
    active_worm_get_damaged = false;
    active_worm_used_weapon = false;
    active_worm->second->set_active();
    std::cout << "Empezando turno de " << unsigned(active_worm->first) << "\n";

    world.generate_provision();
}

std::unique_ptr<GameWorldState> GameWorldInteractiveState::update() {
    ticks++;
    if ((active_worm->second->get_state() & Alive) == 0)
        return std::make_unique<GameWorldSimulationState>(active_worm, worm_map, false, world);

    if (ticks > round_length || active_worm_get_damaged)
        return std::make_unique<GameWorldSimulationState>(active_worm, worm_map, false, world);


    if (active_worm_used_weapon) {
        return std::make_unique<GameWorldSimulationState>(active_worm, worm_map, true, world);
    }


    return std::make_unique<GameWorldInteractiveState>(*this);
}

void GameWorldInteractiveState::handle_weapon_fired() { active_worm_used_weapon = true; }

void GameWorldInteractiveState::handle_worm_damaged(uint16_t worm_id) {
    if (active_worm->first == worm_id)
        active_worm_get_damaged = true;
}

void GameWorldInteractiveState::handle_entity_moving() {}
