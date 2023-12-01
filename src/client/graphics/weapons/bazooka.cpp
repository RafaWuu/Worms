#include "bazooka.h"

AnimationState Bazooka::get_idle_texture_state() { return AnimationState::BAZOOKA_IDLE; }

AnimationState Bazooka::get_aiming_texture_state() { return AnimationState::BAZOOKA_AIMING; }

AnimationState Bazooka::get_projectile_texture() { return BAZOOKA_PROJECTILE; }
