//
// Created by xguss on 26/11/23.
//

#ifndef WORMS_SERVER_PROJECTILE_EFFECT_H
#define WORMS_SERVER_PROJECTILE_EFFECT_H

#include "game/world/server_gameworld.h"

class ProjectileEffect {
protected:
    uint16_t projectile_type;

public:
    explicit ProjectileEffect(uint16_t projectile_type);
    virtual ~ProjectileEffect() = default;

    // Devuelve true si el preyectil deberia desaparecer
    virtual bool execute(GameWorld& world, b2Body& body) = 0;
};
#endif  // WORMS_SERVER_PROJECTILE_EFFECT_H
