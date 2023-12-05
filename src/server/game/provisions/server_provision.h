

#ifndef WORMS_SERVER_PROVISION_H
#define WORMS_SERVER_PROVISION_H

#include <memory>

#include "game/entities/server_gameobject.h"
#include "game/entities/server_worm.h"

#include "server_provision_effect.h"

class Provision: public GameObject {
private:
    std::unique_ptr<ProvisionEffect> effect;
    Configuration& config;
    bool been_took;

public:
    friend class ProvisionInfo;

    Provision(GameWorld& world, float x, float y, std::unique_ptr<ProvisionEffect> effect);
    ~Provision() override = default;
    void update(GameWorld& world) override;
    std::unique_ptr<GameObjectInfo> get_status() const override;
    ObjectType get_id() const override;

    void delete_body() override;

    void take(GameWorld& world, Worm& worm);


    b2Body* body;
};
#endif  // WORMS_SERVER_PROVISION_H
