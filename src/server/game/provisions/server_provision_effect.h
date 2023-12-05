

#ifndef WORMS_SERVER_PROVISION_EFFECT_H
#define WORMS_SERVER_PROVISION_EFFECT_H

#include "../entities/server_worm.h"

class Provision;

class ProvisionEffect {
public:
    virtual ~ProvisionEffect() = default;
    virtual void take(GameWorld&, Provision& provision, Worm& worm) = 0;
};
#endif  // WORMS_SERVER_PROVISION_EFFECT_H
