#ifndef _GRAPHICS_GREEN_GRENADE_H_
#define _GRAPHICS_GREEN_GRENADE_H_

#include "weapon.h"

class GreenGrenade : public Weapon {
public:
    AnimationState get_idle_texture_state() override;
    
    AnimationState get_aiming_texture_state() override;

    AnimationState get_projectile_texture() override;
};

#endif
