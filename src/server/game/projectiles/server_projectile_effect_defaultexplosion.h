//
// Created by xguss on 26/11/23.
//

#ifndef WORMS_SERVER_PROJECTILE_EFFECT_DEFAULTEXPLOSION_H
#define WORMS_SERVER_PROJECTILE_EFFECT_DEFAULTEXPLOSION_H

#include "server_projectile_effect.h"

class ProjectileEffectDefaultExplosion: public ProjectileEffect {
private:
    float blast_power;
    float radius;
    float damage;

public:
    ProjectileEffectDefaultExplosion(uint16_t projectile_type, float radius, float damage,
                                     float blast_power);
    bool execute(GameWorld& world, b2Body& body) override;

    void apply_blast_impulse(b2Body* body, Worm* worm, b2Vec2 blastCenter, b2Vec2 applyPoint,
                             float blastPower);
};

#endif  // WORMS_SERVER_PROJECTILE_EFFECT_DEFAULTEXPLOSION_H
