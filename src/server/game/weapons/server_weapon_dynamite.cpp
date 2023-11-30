//
// Created by xguss on 27/11/23.
//

#include "server_weapon_dynamite.h"

#include <memory>

#include "game/projectiles/server_projectile_effect_defaultexplosion.h"
#include "game/projectiles/server_projectile_effect_noeffect.h"
#include "game/projectiles/server_projectile_launch_inplace.h"
#include "game/projectiles/server_projectile_launch_parabolic.h"

#include "common_weapon_constants.h"
#include "server_weapon_info_dynamite.h"

DynamiteWeapon::DynamiteWeapon(GameWorld& world): Weapon(world) {
    ammo = config.get_weapon_ammo(DYNAMITE);
    countdown = config.get_maximum_countdown();
}

bool DynamiteWeapon::aim_projectile(b2Body& body, float x, float y, bool facing_right) {
    return false;
}

bool DynamiteWeapon::power_projectile() { return false; }

bool DynamiteWeapon::fire_projectile(b2Body& body, bool facing_right) {
    if (ammo == 0) {
        return false;
    }

    b2Vec2 source = b2Vec2(config.get_firing_source_x(), config.get_firing_source_y());

    if (!facing_right) {
        source.x = -source.x;
    }

    float radius = config.get_weapon_radius(DYNAMITE);
    float damage = config.get_weapon_damage(DYNAMITE);
    float blast_power = config.get_weapon_blastpower(DYNAMITE);
    float max_vel = config.get_weapon_max_vel(DYNAMITE);

    world.add_entity(std::make_shared<Projectile>(
            &world.b2_world, DYNAMITE,
            std::make_unique<ProjectileLaunchInPlace>(body.GetWorldPoint(source), max_vel),
            std::make_unique<ProjectileEffectNone>(DYNAMITE_ID),
            std::make_unique<ProjectileEffectDefaultExplosion>(DYNAMITE_ID, radius, damage,
                                                               blast_power),
            countdown));

    ammo--;

    return true;
}

bool DynamiteWeapon::adjust_projectile_countdown(float seconds) {
    countdown = seconds;
    return false;
}

std::unique_ptr<WeaponInfo> DynamiteWeapon::get_info() const {
    return std::make_unique<DynamiteWeaponInfo>(*this);
}
