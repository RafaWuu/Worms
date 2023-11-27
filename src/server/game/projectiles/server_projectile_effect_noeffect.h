//
// Created by xguss on 26/11/23.
//

#ifndef WORMS_SERVER_PROJECTILE_EFFECT_NOEFFECT_H
#define WORMS_SERVER_PROJECTILE_EFFECT_NOEFFECT_H


#include "server_projectile_effect.h"

class ProjectileEffectNone: public ProjectileEffect {

public:
    ProjectileEffectNone() = default;
    bool execute(GameWorld& world, b2Body& body) override;
};

#endif  // WORMS_SERVER_PROJECTILE_EFFECT_NOEFFECT_H
