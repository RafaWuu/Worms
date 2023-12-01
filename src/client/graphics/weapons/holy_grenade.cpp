#include "holy_grenade.h"

AnimationState HolyGrenade::get_idle_texture_state() { return AnimationState::HOLY_GRENADE_IDLE; }

AnimationState HolyGrenade::get_aiming_texture_state() { return AnimationState::HOLY_GRENADE_AIMING; }

AnimationState HolyGrenade::get_projectile_texture() { return HOLY_GRENADE_PROJECTILE; }
