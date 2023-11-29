//
// Created by xguss on 28/11/23.
//

#include "server_gameworld_interactive_state.h"

#include <iostream>
#include <memory>

#include "server_gameworld_simulationstate.h"
#include "server_gameworld_state.h"

GameWorldInteractiveState::GameWorldInteractiveState(
        std::map<uint16_t, Worm*>::iterator active_worm, std::map<uint16_t, Worm*>& worm_map):
        GameWorldState(active_worm, worm_map) {
    ticks = 0;
    round_length = 30 * 100;
    active_worm_get_damaged = false;
    active_worm_used_weapon = false;
    active_worm->second->set_active();
    std::cout << "Empezando turno de " << unsigned(active_worm->first) << "\n";
}

std::unique_ptr<GameWorldState> GameWorldInteractiveState::update() {
    ticks++;
    if ((active_worm->second->get_state() & Alive) == 0)
        return std::make_unique<GameWorldSimulationState>(active_worm, worm_map, false);

    if (ticks > round_length || active_worm_get_damaged)
        return std::make_unique<GameWorldSimulationState>(active_worm, worm_map, false);


    if (active_worm_used_weapon) {
        return std::make_unique<GameWorldSimulationState>(active_worm, worm_map, true);
    }


    return std::make_unique<GameWorldInteractiveState>(*this);
}

void GameWorldInteractiveState::handle_weapon_fired() { active_worm_used_weapon = true; }

void GameWorldInteractiveState::handle_worm_damaged(uint16_t worm_id) {
    if (active_worm->first == worm_id)
        active_worm_get_damaged = true;
}

void GameWorldInteractiveState::handle_entity_moving() {}
