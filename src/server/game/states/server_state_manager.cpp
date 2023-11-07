//
// Created by xguss on 07/11/23.
//

#include "server_state_manager.h"

#include <memory>

#include "server_state_walking.h"

StateManager::StateManager(uint16_t starting): current(starting), registeredStates() {
    registeredStates.emplace(Alive, std::make_shared<AliveState>());
    registeredStates.emplace(Standing, std::make_shared<StandingState>());
    registeredStates.emplace(Walking, std::make_shared<WalkingState>());
    registeredStates.emplace(Jumping, std::make_shared<JumpingState>());
    registeredStates.emplace(Rolling, std::make_shared<RollingState>());
}

void StateManager::update(Worm& worm) {
    for (auto& state: registeredStates) {
        if (is_active(*state.second))
            state.second->update(worm);
    }
}

void StateManager::try_activate(StateEnum state_code, Worm& worm) {

    auto it = registeredStates.find(state_code);
    if (it == registeredStates.end())
        return;

    if (!is_activable(*it->second))
        return;

    if (!it->second->can_be_activated(worm))
        return;

    deactivate_states(it->second->get_states_to_terminate());
    current |= it->second->get_code();
    it->second->on_activated(worm);
}

bool StateManager::is_activable(const WormState& state) const {
    if (is_active(state))
        return false;
    if (is_blocked(state)) {
        return false;
    }
    if (!has_required(state)) {
        return false;
    }
    return true;
}

bool StateManager::is_active(const WormState& state) const {
    return (state.get_code() & current) != 0;
}

bool StateManager::is_blocked(const WormState& state) const {
    return (state.get_states_blocking_me() & current) != 0;
}

bool StateManager::has_required(const WormState& state) const {
    return (state.get_states_required() & current) == state.get_states_required();
}

void StateManager::deactivate_states(uint16_t states_code) {
    uint16_t states = current & states_code;

    for (auto& state: registeredStates) {
        if (states & state.first)
            deactivate(*state.second);
    }
}

void StateManager::deactivate(const WormState& state) {
    current &= !state.get_code();
    // state.OnDeactivated();
    // deactivate_states(state.get_states_requiring());
}
