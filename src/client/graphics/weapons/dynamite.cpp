#include "dynamite.h"

AnimationState Dynamite::get_idle_texture_state() { return AnimationState::DYNAMITE_IDLE; }

AnimationState Dynamite::get_aiming_texture_state() { return AnimationState::DYNAMITE_IDLE; }

AnimationState Dynamite::get_projectile_texture() { return DYNAMITE_PROJECTILE; }

bool Dynamite::projectile_should_loop() {
    return true;
}
