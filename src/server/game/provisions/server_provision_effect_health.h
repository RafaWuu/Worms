//
// Created by xguss on 02/12/23.
//

#ifndef WORMS_SERVER_PROVISION_EFFECT_HEALTH_H
#define WORMS_SERVER_PROVISION_EFFECT_HEALTH_H

#include "server_provision_effect.h"

class ProvisionEffectHealth: public ProvisionEffect {
private:
    int health;

public:
    explicit ProvisionEffectHealth(int health);
    void take(GameWorld& world, Provision& provision, Worm& worm) override;
};
#endif  // WORMS_SERVER_PROVISION_EFFECT_HEALTH_H
