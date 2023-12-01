#include "green_grenade.h"

AnimationState GreenGrenade::get_idle_texture_state() { return AnimationState::GREEN_GRENADE_IDLE; }

AnimationState GreenGrenade::get_aiming_texture_state() { return AnimationState::GREEN_GRENADE_AIMING; }

AnimationState GreenGrenade::get_projectile_texture() { return GREEN_GRENADE_PROJECTILE; }
