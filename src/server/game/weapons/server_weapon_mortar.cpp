

#include "server_weapon_mortar.h"

#include <memory>

#include "game/projectiles/server_projectile_effect_fragmentedexplosion.h"
#include "game/projectiles/server_projectile_effect_noeffect.h"
#include "game/projectiles/server_projectile_launch_parabolic.h"

#include "common_weapon_constants.h"
#include "server_weapon_mortar_info.h"

MortarWeapon::MortarWeapon(GameWorld& world): Weapon(world) {
    ammo = config.get_weapon_ammo(MORTAR);
    aim_power = 0;
    aim_angle = 0;
}

bool MortarWeapon::aim_projectile(b2Body& body, float x, float y, bool facing_right) {
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

bool MortarWeapon::power_projectile() {
    aim_power += 1 / (config.get_powering_time() * config.get_tick_rate());

    if (aim_power > MAX_POWER) {
        aim_power = MAX_POWER;
        return false;
    }
    return true;
}

bool MortarWeapon::fire_projectile(b2Body& body, bool facing_right) {
    if (ammo == 0) {
        aim_power = 0;
        aim_angle = 0;
        return false;
    }

    b2Vec2 source = b2Vec2(config.get_firing_source_x(), config.get_firing_source_y());

    if (!facing_right) {
        source.x = -source.x;
    }

    float radius = config.get_weapon_main_explosion_radius(MORTAR);
    float damage = config.get_weapon_main_explosion_damage(MORTAR);
    float blast_power = config.get_weapon_blastpower(MORTAR);
    float max_vel = config.get_weapon_max_vel(MORTAR);
    float fragment_number = config.get_weapon_fragment_number(MORTAR);
    float fragment_radius = config.get_weapon_fragment_radius(MORTAR);
    float fragment_damage = config.get_weapon_fragment_damage(MORTAR);

    world.add_entity(std::make_shared<Projectile>(
            &world.b2_world, MORTAR,
            std::make_unique<ProjectileLaunchParabolic>(body.GetWorldPoint(source), aim_angle,
                                                        aim_power, max_vel),
            std::make_unique<ProjectileEffectFragmentedExplosion>(MORTAR_ID, radius, damage,
                                                                  blast_power, fragment_number,
                                                                  fragment_radius, fragment_damage),
            std::make_unique<ProjectileEffectNone>(MORTAR_ID), 0));

    ammo--;
    aim_power = 0;
    aim_angle = 0;

    return true;
}

std::unique_ptr<WeaponInfo> MortarWeapon::get_info() const {
    return std::make_unique<MortarWeaponInfo>(*this);
}
