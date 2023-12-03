//
// Created by xguss on 03/12/23.
//

#include "server_provision_effect_explosion.h"

ProvisionEffectExplosion::ProvisionEffectExplosion(uint16_t id, int damage, int radius,
                                                   int blast_power):
        explosion(std::make_unique<ProjectileEffectDefaultExplosion>(id, radius, damage,
                                                                     blast_power)) {}

void ProvisionEffectExplosion::take(GameWorld& world, Provision& provision, Worm& worm) {
    explosion->execute(world, *provision.body);
}
