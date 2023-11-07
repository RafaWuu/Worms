//
// Created by xguss on 07/11/23.
//

#ifndef WORMS_SERVER_STATE_MANAGER_H
#define WORMS_SERVER_STATE_MANAGER_H

#include <cstdint>
#include <map>
#include <memory>

#include "game/server_move.h"

#include "server_state_enum.h"

class WormState;
class Worm;

class StateManager {
private:
    std::map<StateEnum, std::shared_ptr<WormState>> registeredStates;

    bool is_activable(const WormState& state) const;

    bool is_blocked(const WormState& state) const;

    bool has_required(const WormState& state) const;

    bool is_active(const WormState& state) const;

    void deactivate_states(uint16_t states_code);

    void deactivate(const WormState& state);

public:
    explicit StateManager(uint16_t starting);
    void try_activate(StateEnum state_code, Worm& worm);

    void update(Worm& worm);

    uint16_t current;
};
#endif  // WORMS_SERVER_STATE_MANAGER_H
