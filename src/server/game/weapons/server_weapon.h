//
// Created by xguss on 11/11/23.
//

#ifndef WORMS_SERVER_WEAPON_H
#define WORMS_SERVER_WEAPON_H


#include <memory>

#include "../../../configuration/configuration.h"

#include "b2_body.h"
#include "b2_math.h"
#include "server_weapon_info.h"

#define MAX_POWER 1

class GameWorld;
class Projectile;

class Weapon {
private:
protected:
    GameWorld& world;
    Configuration& config;

public:
    explicit Weapon(GameWorld& world);
    virtual ~Weapon() = default;
    virtual bool aim_projectile(b2Body& body, float x, float y, bool facing_right);

    virtual bool power_projectile();

    virtual bool fire_projectile(b2Body& body, bool facing_right) = 0;

    virtual bool adjust_projectile_countdown(float seconds);

    virtual std::unique_ptr<WeaponInfo> get_info() const = 0;
};
#endif  // WORMS_SERVER_WEAPON_H
