//
// Created by xguss on 28/11/23.
//

#include "server_gameworld_simulationstate.h"

#include <iostream>

#include "server_gameworld_interactive_state.h"

GameWorldSimulationState::GameWorldSimulationState(std::map<uint16_t, Worm*>::iterator active_worm,
                                                   std::map<uint16_t, Worm*>& worm_map,
                                                   bool grace_period, GameWorld& world):
        grace_period(grace_period), GameWorldState(active_worm, worm_map, world) {
    auto& config = Configuration::get_instance();

    ticks = 0;
    round_length = grace_period ? config.grace_length * config.get_tick_rate() : 0;

    all_entities_had_stopped = true;
    std::cout << "Empezando simulacion " << (grace_period ? "con" : "sin") << " tiempo extra de "
              << unsigned(active_worm->first) << "\n";
}

std::unique_ptr<GameWorldState> GameWorldSimulationState::update() {
    ticks++;

    if (ticks > round_length)
        active_worm->second->set_deactive();

    if (all_entities_had_stopped) {
        ++active_worm;
        if (active_worm == worm_map.end())
            active_worm = worm_map.begin();

        active_worm->second->set_deactive();
        return std::make_unique<GameWorldInteractiveState>(active_worm, worm_map, world);
    }

    all_entities_had_stopped = true;
    return std::make_unique<GameWorldSimulationState>(*this);
}

void GameWorldSimulationState::handle_weapon_fired() {}

void GameWorldSimulationState::handle_worm_damaged(uint16_t worm_id) {}

void GameWorldSimulationState::handle_entity_moving() { all_entities_had_stopped = false; }