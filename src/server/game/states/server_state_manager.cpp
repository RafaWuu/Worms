//
// Created by xguss on 07/11/23.
//

#include "server_state_manager.h"

#include <memory>

#include "server_states.h"

StateManager::StateManager(uint16_t starting): current(starting), registeredStates() {
    registeredStates.emplace(Alive, std::make_shared<AliveState>());
    registeredStates.emplace(Standing, std::make_shared<StandingState>());
    registeredStates.emplace(Walking, std::make_shared<WalkingState>());
    registeredStates.emplace(Jumping, std::make_shared<JumpingState>());
    registeredStates.emplace(Rolling, std::make_shared<RollingState>());
    registeredStates.emplace(Falling, std::make_shared<FallingState>());
    registeredStates.emplace(Firing, std::make_shared<FiringState>());
    registeredStates.emplace(Aiming, std::make_shared<AimingState>());
    registeredStates.emplace(Powering, std::make_shared<PoweringState>());
}

void StateManager::update(Worm& worm) {
    for (auto& state: registeredStates) {
        if (is_active(*state.second)){
            bool deactivate_state = state.second->update(worm);
            if(!deactivate_state)
                deactivate(*state.second, worm);
        }
    }
}

bool StateManager::try_activate(StateEnum state_code, Worm& worm) {

    auto it = registeredStates.find(state_code);
    if (it == registeredStates.end())
        return false;

    if (!is_activable(*it->second))
        return false;

    if (!it->second->can_be_activated(worm))
        return false;

    it->second->on_activated(worm);
    current |= it->second->get_code();

    deactivate_states(it->second->get_states_to_terminate(), worm);

    return true;
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
    return (state.get_code() & current) != NoState;
}

bool StateManager::is_blocked(const WormState& state) const {
    return (state.get_states_blocking_me() & current) != NoState;
}

bool StateManager::has_required(const WormState& state) const {
    return (state.get_states_required() & current) == state.get_states_required();
}

void StateManager::deactivate_states(uint16_t states_code, Worm& worm) {
    uint16_t states = current & states_code;

    for (auto& state: registeredStates) {
        if (states & state.first)
            deactivate(*state.second, worm);
    }
}

void StateManager::deactivate(WormState& state, Worm& worm) {
    current &= ~state.get_code();
    uint16_t to_activate = state.on_deactivated(worm);
    activate_states(to_activate, worm);

    // deactivate_states(state.get_states_requiring());
}

void StateManager::activate_states(uint16_t states_code, Worm& worm) {
    uint16_t states = ~current & states_code;

    for (auto& state: registeredStates) {
        if (states & state.first){
            state.second->on_activated(worm);
            current |= state.second->get_code();
        }
    }
}