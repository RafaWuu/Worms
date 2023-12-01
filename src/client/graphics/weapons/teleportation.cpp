//
// Created by xguss on 30/11/23.
//

#include "teleportation.h"

AnimationState Teleportation::get_idle_texture_state() {
    return AnimationState::TELEPORTATION_IDLE;
}

AnimationState Teleportation::get_aiming_texture_state() {
    return AnimationState::TELEPORTATION_AIMING;
}

// Teleportation no tiene proyectil, no se deberia llamar a esta funcion
AnimationState Teleportation::get_projectile_texture() {
    return AnimationState::TELEPORTATION_AIMING;
}
