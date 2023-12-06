

#include "server_weapon_teleportation.h"

#include "../world/server_gameworld.h"
#include "game/entities/server_gameobject.h"

#include "b2_fixture.h"
#include "b2_world_callbacks.h"
#include "common_weapon_constants.h"
#include "server_weapon_info_teleportation.h"

TeleportationWeapon::TeleportationWeapon(GameWorld& world): Weapon(world) {
    ammo = config.get_weapon_ammo(TELEPORTATION);
    aim_x = 0;
    aim_y = 0;
}


bool TeleportationWeapon::fire_projectile(b2Body& body, bool facing_right) {
    if (ammo == 0) {
        return false;
    }

    b2Vec2 size(config.worm_width, config.worm_height);

    if (world.is_new_position_valid(aim_x, aim_y, size)) {
        body.SetTransform(b2Vec2(aim_x, aim_y), 0);
        return true;
    }

    return false;
}

bool TeleportationWeapon::aim_projectile(b2Body& body, float x, float y, bool facing_right) {
    aim_x = x;
    aim_y = y;

    return true;
}

std::unique_ptr<WeaponInfo> TeleportationWeapon::get_info() const {
    return std::make_unique<TeleportationWeaponInfo>(*this);
}
