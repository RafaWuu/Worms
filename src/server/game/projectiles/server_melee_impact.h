

#ifndef WORMS_SERVER_MELEE_IMPACT_H
#define WORMS_SERVER_MELEE_IMPACT_H

#include <memory>
#include <string>

#include "../../../../configuration/configuration.h"
#include "../entities/server_worm.h"
#include "game/entities/server_gameobject.h"
class MeleeImpact: public GameObject {
private:
    Configuration& config;
    uint8_t type;
    b2Body* body;
    float blast_power;
    int damage;
    bool had_impacted;
    uint16_t owner_id;
    b2Vec2 direction;

public:
    friend class MeeleSensorInfo;

    MeleeImpact(b2World* world, std::string&& identifier, uint16_t owner_id, b2Vec2 center,
                b2Vec2 direction);

    ~MeleeImpact() override = default;
    MeleeImpact& operator=(const MeleeImpact&) = delete;
    std::unique_ptr<GameObjectInfo> get_status() const override;
    ObjectType get_id() const override;

    void update(GameWorld& world) override;

    void on_impact(GameWorld& world, Worm& worm);

    void delete_body() override;

    int frames;
};

#endif  // WORMS_SERVER_MELEE_IMPACT_H
