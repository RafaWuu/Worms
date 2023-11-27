#ifndef _GRAPHICS_HOLY_GRENADE_H_
#define _GRAPHICS_HOLY_GRENADE_H_

#include "weapon.h"

class HolyGrenade : public Weapon {
public:
    AnimationState get_idle_texture_state() override;
    
    AnimationState get_aiming_texture_state() override;
};

#endif

