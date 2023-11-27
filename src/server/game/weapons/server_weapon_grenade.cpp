//
// Created by xguss on 26/11/23.
//

#include "server_weapon_grenade.h"

#include <memory>

#include "game/projectiles/server_projectile_effect_defaultexplosion.h"
#include "game/projectiles/server_projectile_effect_noeffect.h"
#include "game/projectiles/server_projectile_launch_parabolic.h"
#include "game/world/server_gameworld.h"

#include "common_weapon_constants.h"
#include "server_weapon_info_grenade.h"

GrenadeWeapon::GrenadeWeapon(GameWorld& world): Weapon(world) {
    ammo = config.get_weapon_ammo(GREEN_GRENADE);
    countdown = config.get_maximum_countdown();
}

bool GrenadeWeapon::aim_projectile(b2Body& body, float x, float y, bool facing_right) {
    b2Vec2 toTarget = body.GetLocalPoint(b2Vec2(x, y));

    if (facing_right && toTarget.x < 0) {  // Limito el campo de vision al apuntar hacia la derecha
        aim_angle = (toTarget.y > 0) ? M_PI_2f32 : -M_PI_2f32;
        return true;
    }

    if (!facing_right &&
        toTarget.x > 0) {  // Limito el campo de vision al apuntar hacia la izquierda
        aim_angle = (toTarget.y > 0) ? M_PI_2f32 : -M_PI_2f32;
        return true;
    }

    aim_angle = atan2f(toTarget.y, toTarget.x);

    return true;
}

bool GrenadeWeapon::power_projectile() {
    aim_power += config.get_powering_time() / config.get_tick_rate();

    if (aim_power > MAX_POWER) {
        aim_power = MAX_POWER;
        return false;
    }
    return true;
}

bool GrenadeWeapon::fire_projectile(b2Body& body, bool facing_right) {
    if (ammo == 0) {
        aim_power = 0;
        aim_angle = 0;
        return false;
    }

    b2Vec2 source = b2Vec2(config.get_firing_source_x(), config.get_firing_source_y());

    if (!facing_right) {
        source.x = -source.x;
    }

    float radius = config.get_weapon_radius(GREEN_GRENADE);
    float damage = config.get_weapon_damage(GREEN_GRENADE);
    float blast_power = config.get_weapon_blastpower(GREEN_GRENADE);
    float max_vel = config.get_weapon_max_vel(GREEN_GRENADE);

    world.add_projectile(std::make_shared<Projectile>(
            &world.b2_world, GREEN_GRENADE,
            std::make_unique<ProjectileLaunchParabolic>(body.GetWorldPoint(source), aim_angle,
                                                        aim_power, max_vel),
            std::make_unique<ProjectileEffectNone>(GREEN_GRENADE_ID),
            std::make_unique<ProjectileEffectDefaultExplosion>(GREEN_GRENADE_ID, radius, damage,
                                                               blast_power),
            countdown));

    ammo--;
    aim_power = 0;
    aim_angle = 0;
    return false;
}

bool GrenadeWeapon::adjust_projectile_countdown(float seconds) {
    countdown = seconds;
    return false;
}

std::unique_ptr<WeaponInfo> GrenadeWeapon::get_info() const {
    return std::make_unique<GrenadeWeaponInfo>(*this);
}
