//
// Created by xguss on 30/11/23.
//

#include "server_weapon_teleportation.h"

#include "game/entities/server_gameobject.h"

#include "b2_fixture.h"
#include "b2_world_callbacks.h"
#include "common_weapon_constants.h"
#include "server_weapon_info_teleportation.h"

class IntersectionCallback: public b2QueryCallback {
public:
    bool intersecting = false;
    bool ReportFixture(b2Fixture* fixture) override {
        auto fixture_data = fixture->GetUserData().pointer;

        auto game_object = (GameObject*)fixture_data;
        auto id = game_object->get_id();
        if (id == BEAM || id == BOUNDARY) {
            intersecting = true;
            return false;
        }
        return true;
    }
};

TeleportationWeapon::TeleportationWeapon(GameWorld& world): Weapon(world) {
    ammo = config.get_weapon_ammo(TELEPORTATION);
    aim_x = 0;
    aim_y = 0;
}


bool TeleportationWeapon::fire_projectile(b2Body& body, bool facing_right) {

    IntersectionCallback callback;
    b2AABB aabb{};
    b2Vec2 size(config.worm_width, config.worm_height);

    aabb.lowerBound = b2Vec2(aim_x - size.x, aim_y - size.y);
    aabb.upperBound = b2Vec2(aim_x + size.x, aim_y + size.y);

    body.GetWorld()->QueryAABB(&callback, aabb);

    if (!callback.intersecting) {
        body.SetTransform(b2Vec2(aim_x, aim_y), 0);
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
