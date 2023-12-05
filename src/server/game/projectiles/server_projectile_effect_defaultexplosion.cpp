//
// Created by xguss on 26/11/23.
//

#include "server_projectile_effect_defaultexplosion.h"

#include "game/listeners/server_explosion_callback.h"

#define MAX_IMPULSE 500.0f


ProjectileEffectDefaultExplosion::ProjectileEffectDefaultExplosion(uint16_t projectile_type,
                                                                   float radius, float damage,
                                                                   float blast_power):
        ProjectileEffect(projectile_type) {
    this->radius = radius;
    this->damage = damage;
    this->blast_power = blast_power;
}

bool ProjectileEffectDefaultExplosion::execute(GameWorld& world, b2Body& body) {
    ExplosionCallback callback;
    b2AABB aabb{};

    b2Vec2 center = body.GetPosition();

    aabb.lowerBound = center - b2Vec2(radius, radius);
    aabb.upperBound = center + b2Vec2(radius, radius);

    body.GetWorld()->QueryAABB(&callback, aabb);

    for (int i = 0; i < callback.found_worms.size(); i++) {
        b2Body* worm_body = callback.found_bodies[i];
        Worm* worm = callback.found_worms[i];

        b2Vec2 bodyCom = worm_body->GetWorldCenter();

        // ignore bodies outside the blast range
        if ((bodyCom - worm_body->GetPosition()).Length() >= radius)
            continue;

        apply_blast_impulse(worm_body, worm, center, bodyCom, blast_power);
    }

    world.add_explosion_entity(projectile_type, radius, center);
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
