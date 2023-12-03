//
// Created by xguss on 03/12/23.
//

#ifndef WORMS_SERVER_PROVISION_EFFECT_EXPLOSION_H
#define WORMS_SERVER_PROVISION_EFFECT_EXPLOSION_H

#include "game/projectiles/server_projectile_effect_defaultexplosion.h"

#include "server_provision.h"
#include "server_provision_effect.h"

class ProvisionEffectExplosion: public ProvisionEffect {
private:
    std::unique_ptr<ProjectileEffectDefaultExplosion> explosion;

public:
    ProvisionEffectExplosion(uint16_t id, int damage, int radius, int blast_power);

    void take(GameWorld& world, Provision& provision, Worm& worm) override;
};

#endif  // WORMS_SERVER_PROVISION_EFFECT_EXPLOSION_H
