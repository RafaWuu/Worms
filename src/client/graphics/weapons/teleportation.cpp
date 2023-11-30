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
