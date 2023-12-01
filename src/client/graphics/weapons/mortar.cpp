#include "mortar.h"

AnimationState Mortar::get_idle_texture_state() { return AnimationState::MORTAR_IDLE; }

AnimationState Mortar::get_aiming_texture_state() { return AnimationState::MORTAR_AIMING; }

AnimationState Mortar::get_projectile_texture() { return MORTAR_PROJECTILE; }
