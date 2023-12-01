#include "red_grenade.h"

AnimationState RedGrenade::get_idle_texture_state() { return AnimationState::RED_GRENADE_IDLE; }

AnimationState RedGrenade::get_aiming_texture_state() { return AnimationState::RED_GRENADE_AIMING; }

AnimationState RedGrenade::get_projectile_texture() { return RED_GRENADE_PROJECTILE; }
