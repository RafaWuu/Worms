

#ifndef WORMS_SERVER_PROJECTILE_EFFECT_FRAGMENTEDEXPLOSION_H
#define WORMS_SERVER_PROJECTILE_EFFECT_FRAGMENTEDEXPLOSION_H

#include <memory>

#include "server_projectile_effect.h"

class ProjectileEffectFragmentedExplosion: public ProjectileEffect {
private:
    float blast_power;
    float main_radius;
    float main_damage;
    int fragment_number;
    float fragment_radius;
    float fragment_damage;

public:
    ProjectileEffectFragmentedExplosion(uint16_t projectile_type, float radius, float damage,
                                        float blast_power, int fragment_number,
                                        float fragment_radius, float fragment_damage);

    bool execute(GameWorld& world, b2Body& body) override;
    void apply_blast_impulse(b2Body* body, Worm* worm, b2Vec2 blastCenter, b2Vec2 applyPoint,
                             float blastPower);
};
#endif  // WORMS_SERVER_PROJECTILE_EFFECT_FRAGMENTEDEXPLOSION_H
