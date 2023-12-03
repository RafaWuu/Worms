//
// Created by xguss on 26/11/23.
//

#include "server_projectile_effect_defaultexplosion.h"

#include "game/listeners/server_raycast_explosion_callback.h"

#define MAX_IMPULSE 500.0f

#define NRAYS 15

ProjectileEffectDefaultExplosion::ProjectileEffectDefaultExplosion(uint16_t projectile_type,
                                                                   float radius, float damage,
                                                                   float blast_power):
        ProjectileEffect(projectile_type) {
    this->radius = radius;
    this->damage = damage;
    this->blast_power = blast_power;
}

bool ProjectileEffectDefaultExplosion::execute(GameWorld& world, b2Body& body) {
    std::vector<uint16_t> affected_worms;

    b2Vec2 center = body.GetPosition();
    int num_rays = NRAYS;
    float m_blastPower = blast_power;
    for (int i = 0; i < num_rays; i++) {
        float angle = (i / (float)num_rays) * 2 * M_PI;

        b2Vec2 rayDir(sinf(angle), cosf(angle));
        b2Vec2 rayEnd = center + radius * rayDir;

        // check what this ray hits
        RayCastExplosionCallback callback;
        world.b2_world.RayCast(&callback, center, rayEnd);
        if (callback.m_body && callback.p_worm) {
            if (std::find(affected_worms.begin(), affected_worms.end(),
                          callback.p_worm->get_id()) == affected_worms.end()) {
                apply_blast_impulse(callback.m_body, callback.p_worm, center, callback.m_point,
                                    (m_blastPower / (float)num_rays));
                affected_worms.push_back(callback.p_worm->get_id());
            }
        }
    }

    world.notify_explosion(projectile_type, radius, center);
    return true;
}

void ProjectileEffectDefaultExplosion::apply_blast_impulse(b2Body* body, Worm* worm,
                                                           b2Vec2 blastCenter, b2Vec2 applyPoint,
                                                           float blastPower) {
    b2Vec2 blastDir = applyPoint - blastCenter;
    float distance = blastDir.Normalize();

    if (distance == 0)
        return;
    float invDistance = 1 / distance;
    float impulseMag = blastPower * invDistance * invDistance;
    impulseMag = b2Min(impulseMag, MAX_IMPULSE);

    body->ApplyLinearImpulse(impulseMag * blastDir, applyPoint, true);
    worm->get_hit(damage * 1 / (distance + 1));
}
