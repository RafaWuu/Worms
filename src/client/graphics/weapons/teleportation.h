//
// Created by xguss on 30/11/23.
//

#ifndef WORMS_TELEPORTATION_H
#define WORMS_TELEPORTATION_H

#include "weapon.h"

class Teleportation: public Weapon {
public:
    AnimationState get_idle_texture_state() override;

    AnimationState get_aiming_texture_state() override;
};


#endif  // WORMS_TELEPORTATION_H
