//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_SERVER_BAZOOKA_projectile_H
#define WORMS_SERVER_BAZOOKA_projectile_H

#include <memory>
#include <string>

#include "../../../../configuration/configuration.h"
#include "game/entities/server_gameobject.h"
#include "game/entities/server_gameobject_info.h"

#include "b2_body.h"
#include "b2_world.h"
#include "server_projectile_launch.h"

class ProjectileEffect;
class GameWorld;

class Projectile: public GameObject {
private:
    Configuration& config;
    uint8_t type;
    std::unique_ptr<ProjectileEffect> impact_strategy;
    std::unique_ptr<ProjectileEffect> countdown_strategy;
    b2Body* body;
    float dragConstant;
    float width;
    float height;
    float countdown;
    bool had_impacted;

public:
    friend class ProjectileInfo;

    Projectile(b2World* world, std::string&& identifier,
               std::unique_ptr<ProjectileLaunch> launch_strategy,
               std::unique_ptr<ProjectileEffect> impact_strategy,
               std::unique_ptr<ProjectileEffect> countdown_strategy, float countdown);

    ~Projectile() override = default;
    Projectile& operator=(const Projectile&) = delete;

    void update(GameWorld& world) override;
    std::unique_ptr<GameObjectInfo> get_status() const override;
    ObjectType get_id() const override;
    void delete_body() override;
    void on_projectile_impact(GameWorld& world);
    void on_countdown_finished(GameWorld& world);
};
#endif  // WORMS_SERVER_BAZOOKA_projectile_H
