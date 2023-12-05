

#include "server_weapon_airattack.h"

#include "game/projectiles/server_projectile_effect_defaultexplosion.h"
#include "game/projectiles/server_projectile_effect_noeffect.h"
#include "game/projectiles/server_projectile_launch_inplace.h"
#include "game/world/server_gameworld.h"

#include "common_weapon_constants.h"
#include "server_weapon_info_airattack.h"

AirAttackWeapon::AirAttackWeapon(GameWorld& world): Weapon(world) {
    ammo = config.get_weapon_ammo(AIR_ATTACK);
    aim_x = 0;
    aim_y = 0;
}

bool AirAttackWeapon::aim_projectile(b2Body& body, float x, float y, bool facing_right) {
    aim_x = x;
    aim_y = y;

    return true;
}

bool AirAttackWeapon::fire_projectile(b2Body& body, bool facing_right) {
    if (ammo == 0) {
        return false;
    }

    b2Vec2 source = b2Vec2(config.get_firing_source_x(), config.get_firing_source_y());

    if (!facing_right) {
        source.x = -source.x;
    }

    float radius = config.get_weapon_radius(AIR_ATTACK);
    float damage = config.get_weapon_damage(AIR_ATTACK);
    float blast_power = config.get_weapon_blastpower(AIR_ATTACK);
    float max_vel = config.get_weapon_max_vel(AIR_ATTACK);

    int missiles = config.get_missil_quantity(AIR_ATTACK);

    for (int i = 0; i < missiles; ++i) {

        b2Vec2 center(aim_x - 3 + 2 * 3 / missiles * i, -1);
        world.add_entity(std::make_shared<Projectile>(
                &world.b2_world, BAZOOKA,
                std::make_unique<ProjectileLaunchInPlace>(center, -max_vel),
                std::make_unique<ProjectileEffectDefaultExplosion>(AIR_ATTACK_ID, radius, damage,
                                                                   blast_power),
                std::make_unique<ProjectileEffectNone>(AIR_ATTACK_ID), 0));
    }


    ammo--;
    aim_x = aim_y = 0;

    return true;
}

std::unique_ptr<WeaponInfo> AirAttackWeapon::get_info() const {
    return std::make_unique<AirAttackWeaponInfo>(*this);
}
