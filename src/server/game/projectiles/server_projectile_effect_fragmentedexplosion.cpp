

#include "server_projectile_effect_fragmentedexplosion.h"

#include "game/listeners/server_explosion_callback.h"
#include "game/weapons/server_weapon.h"
#include "game/world/server_gameworld.h"

#include "common_weapon_constants.h"
#include "server_projectile_effect.h"
#include "server_projectile_effect_defaultexplosion.h"
#include "server_projectile_effect_noeffect.h"
#include "server_projectile_launch_parabolic.h"

#define MAX_IMPULSE 500.0f
#define NRAYS 15

ProjectileEffectFragmentedExplosion::ProjectileEffectFragmentedExplosion(
        uint16_t projectile_type, float radius, float damage, float blast_power,
        int fragment_number, float fragment_radius, float fragment_damage):
        ProjectileEffect(projectile_type) {
    this->main_radius = radius;
    this->main_damage = damage;
    this->blast_power = blast_power;
    this->fragment_number = fragment_number;
    this->fragment_radius = fragment_radius;
    this->fragment_damage = fragment_damage;
}


bool ProjectileEffectFragmentedExplosion::execute(GameWorld& world, b2Body& body) {
    ExplosionCallback callback;
    b2AABB aabb{};

    b2Vec2 center = body.GetPosition();

    aabb.lowerBound = center - b2Vec2(main_radius, main_radius);
    aabb.upperBound = center + b2Vec2(main_radius, main_radius);

    body.GetWorld()->QueryAABB(&callback, aabb);

    for (int i = 0; i < callback.found_worms.size(); i++) {
        b2Body* worm_body = callback.found_bodies[i];
        Worm* worm = callback.found_worms[i];

        b2Vec2 bodyCom = worm_body->GetWorldCenter();

        // ignore bodies outside the blast range
        if ((bodyCom - worm_body->GetPosition()).Length() >= main_radius)
            continue;

        apply_blast_impulse(worm_body, worm, center, bodyCom, blast_power);
    }

    for (int i = 0; i < fragment_number; ++i) {
        float angle = (i / (float)fragment_number) * M_PI_2 + M_PI_4;

        world.add_entity(std::make_shared<Projectile>(
                &world.b2_world, BAZOOKA,
                std::make_unique<ProjectileLaunchParabolic>(center + b2Vec2(0, .1), angle, .5, 12),
                std::make_unique<ProjectileEffectDefaultExplosion>(
                        BAZOOKA_ID, fragment_radius, fragment_damage,
                        blast_power / (float)fragment_number),
                std::make_unique<ProjectileEffectNone>(BAZOOKA_ID), 0.0));
    }

    world.add_explosion_entity(projectile_type, main_radius, center);
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
    worm->get_hit(main_damage * 1 / (invDistance + 1));
}
