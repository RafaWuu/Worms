

#ifndef WORMS_SERVER_WORM_INFO_H
#define WORMS_SERVER_WORM_INFO_H

#include <cstdint>
#include <memory>

#include "game/weapons/server_weapon_info.h"

#include "server_gameobject.h"
#include "server_gameobject_info.h"

class Worm;

class WormInfo: public GameObjectInfo {
private:
    ObjectType object_id;
    float x;
    float y;
    uint16_t worm_id;
    bool facing_right;
    uint16_t state;
    uint8_t health;
    int weapon;
    uint16_t client_id;

public:
    explicit WormInfo(const Worm& worm);

    void serialize_status(BaseProtocol& bp) override;
    void serialize_scenario(BaseProtocol& bp) override;


    void serialize_start(BaseProtocol& bp);

    std::unique_ptr<WeaponInfo> weapon_info;

    WormInfo(ObjectType object_id, float x, float y, uint16_t worm_id, bool facing_right,
             uint16_t state, uint8_t health, int current_weapon, uint16_t client_id,
             std::unique_ptr<WeaponInfo> weapon_info);
};
#endif  // WORMS_SERVER_WORM_INFO_H
