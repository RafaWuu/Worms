//
// Created by xguss on 30/11/23.
//

#include "server_weapon_bat.h"

#include "game/projectiles/server_melee_impact.h"
#include "game/projectiles/server_projectile_effect_defaultexplosion.h"
#include "game/projectiles/server_projectile_effect_noeffect.h"
#include "game/projectiles/server_projectile_launch_inplace.h"
#include "game/projectiles/server_projectile_launch_parabolic.h"

#include "common_weapon_constants.h"
#include "server_weapon_info_bat.h"


WeaponBat::WeaponBat(GameWorld& world, uint16_t worm_id): Weapon(world) {
    ammo = config.get_weapon_ammo(BASEBALL_BAT);
    this->worm_id = worm_id;
}

bool WeaponBat::aim_projectile(b2Body& body, float x, float y, bool facing_right) {
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

bool WeaponBat::power_projectile() {
    aim_power += config.get_powering_time() / config.get_tick_rate();

    if (aim_power > MAX_POWER) {
        aim_power = MAX_POWER;
        return false;
    }
    return true;
}

bool WeaponBat::fire_projectile(b2Body& body, bool facing_right) {
    if (ammo == 0) {
        return false;
    }

    b2Vec2 dir = b2Vec2(cosf(aim_angle), sinf(aim_angle));
    dir.Normalize();

    world.add_entity(std::make_shared<MeleeImpact>(&world.b2_world, BASEBALL_BAT, worm_id,
                                                   body.GetPosition(), dir));

    ammo--;

    return true;
}


std::unique_ptr<WeaponInfo> WeaponBat::get_info() const {
    return std::make_unique<BatWeaponInfo>(*this);
}
