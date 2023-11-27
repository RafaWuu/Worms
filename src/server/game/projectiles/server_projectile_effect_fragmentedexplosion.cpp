//
// Created by xguss on 26/11/23.
//

#include "server_projectile_effect_fragmentedexplosion.h"

#include "game/listeners/server_raycast_explosion_callback.h"
#include "game/weapons/server_weapon.h"
#include "game/world/server_gameworld.h"

#include "common_weapon_constants.h"
#include "server_projectile_effect.h"
#include "server_projectile_effect_defaultexplosion.h"
#include "server_projectile_effect_noeffect.h"

#define MAX_IMPULSE 500.0f
#define NRAYS 15

ProjectileEffectFragmentedExplosion::ProjectileEffectFragmentedExplosion(float radius, float damage,
                                                                         float blast_power,
                                                                         int fragment_number,
                                                                         float fragment_radius,
                                                                         float fragment_damage) {
    this->main_radius = radius;
    this->main_damage = damage;
    this->blast_power = blast_power;
    this->fragment_number = fragment_number;
    this->fragment_radius = fragment_radius;
    this->fragment_damage = fragment_damage;
}


bool ProjectileEffectFragmentedExplosion::execute(GameWorld& world, b2Body& body) {

    b2Vec2 center = body.GetPosition();
    int num_rays = NRAYS;
    float m_blastPower = blast_power;
    for (int i = 0; i < num_rays; i++) {
        float angle = (i / (float)num_rays) * 2 * M_PI;

        b2Vec2 rayDir(sinf(angle), cosf(angle));
        b2Vec2 rayEnd = center + main_radius * rayDir;

        // check what this ray hits
        RayCastExplosionCallback callback;
        world.b2_world.RayCast(&callback, center, rayEnd);
        if (callback.m_body && callback.p_worm) {
            apply_blast_impulse(callback.m_body, callback.p_worm, center, callback.m_point,
                                (m_blastPower / (float)num_rays));
        }
    }

    for (int i = 0; i < fragment_number; ++i) {
        float angle = (i / (float)fragment_number) * M_PI_2 + M_PI_4;

        world.add_projectile(std::make_shared<Projectile>(
                &world.b2_world, BAZOOKA,
                std::make_unique<ProjectileEffectDefaultExplosion>(
                        fragment_radius, fragment_damage, blast_power / (float)fragment_number),
                std::make_unique<ProjectileEffectNone>(), center, angle, .5, 0.0));
    }

    return true;
}

void ProjectileEffectFragmentedExplosion::apply_blast_impulse(b2Body* body, Worm* worm,
                                                              b2Vec2 blastCenter, b2Vec2 applyPoint,
                                                              float blastPower) {
    b2Vec2 blastDir = applyPoint - blastCenter;
    float distance = blastDir.Normalize();
    // ignore bodies exactly at the blast point - blast direction is undefined
    if (distance == 0)
        return;
    float invDistance = 1 / distance;
    float impulseMag = blastPower * invDistance * invDistance;
    impulseMag = b2Min(impulseMag, MAX_IMPULSE);

    body->ApplyLinearImpulse(impulseMag * blastDir, applyPoint, true);
    worm->get_hit(main_damage * invDistance);
}