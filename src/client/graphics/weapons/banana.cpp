#include "banana.h"

AnimationState Banana::get_idle_texture_state() { return AnimationState::BANANA_IDLE; }

AnimationState Banana::get_aiming_texture_state() { return AnimationState::BANANA_AIMING; }

AnimationState Banana::get_projectile_texture() { return BANANA_PROJECTILE; }

