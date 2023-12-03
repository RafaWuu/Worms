//
// Created by xguss on 02/12/23.
//

#include "server_provision_effect_health.h"

ProvisionEffectHealth::ProvisionEffectHealth(int health): health(health) {}

void ProvisionEffectHealth::take(GameWorld& world, Provision& provision, Worm& worm) {
    worm.health += this->health;
}
