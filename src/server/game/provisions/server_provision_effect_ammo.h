//
// Created by xguss on 03/12/23.
//

#ifndef WORMS_SERVER_PROVISION_EFFECT_AMMO_H
#define WORMS_SERVER_PROVISION_EFFECT_AMMO_H

#include "server_provision_effect.h"

class ProvisionEffectAmmo: public ProvisionEffect {
private:
    int quantity;
    uint16_t weapon_id;

public:
    explicit ProvisionEffectAmmo(int quantity, uint16_t weapon_id);

    void take(GameWorld& world, Provision& provision, Worm& worm) override;
};

#endif  // WORMS_SERVER_PROVISION_EFFECT_AMMO_H
