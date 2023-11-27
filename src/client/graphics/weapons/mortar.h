#ifndef _GRAPHICS_MORTAR_H_
#define _GRAPHICS_MORTAR_H_

#include "weapon.h"

class Mortar : public Weapon {
public:
    AnimationState get_idle_texture_state() override;
    
    AnimationState get_aiming_texture_state() override;
};

#endif
