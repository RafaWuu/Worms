#include "baseball_bat.h"

AnimationState BaseballBat::get_idle_texture_state() { return AnimationState::BAT_IDLE; }

AnimationState BaseballBat::get_aiming_texture_state() { return AnimationState::BAT_AIMING; }

// El bate no tiene proyectil, no se deberia llamar a esta funcion
AnimationState BaseballBat::get_projectile_texture() { return BAT_AIMING; }
