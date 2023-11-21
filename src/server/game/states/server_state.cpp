//
// Created by xguss on 07/11/23.
//

#include "server_state.h"

WormState::WormState(): config(Configuration::get_instance()) {
    _is_active = false;
    code = NoState;
    required = Alive;
    blocking_me = NoState;
    terminate = NoState;
    requiring = NoState;
}

bool WormState::can_be_activated(Worm& worm) { return true; }

uint16_t WormState::get_states_blocking_me() const { return blocking_me; }

uint16_t WormState::get_states_required() const { return required; }

uint16_t WormState::get_states_to_terminate() const { return terminate; }

uint16_t WormState::get_code() const { return code; }

uint16_t WormState::get_states_requiring() { return requiring; }

void WormState::on_activated(Worm& worm) {}

uint16_t WormState::on_deactivated(Worm& worm) { return 0; }
