

#include "server_provision_effect_health.h"

ProvisionEffectHealth::ProvisionEffectHealth(int health): health(health) {}

void ProvisionEffectHealth::take(GameWorld& world, Provision& provision, Worm& worm) {
    worm.add_health(health);
}
