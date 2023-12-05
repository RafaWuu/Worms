

#include "server_provision_effect_ammo.h"

ProvisionEffectAmmo::ProvisionEffectAmmo(int quantity, uint16_t weapon_id):
        quantity(quantity), weapon_id(weapon_id) {}

void ProvisionEffectAmmo::take(GameWorld& world, Provision& provision, Worm& worm) {
    worm.add_ammo(weapon_id, quantity);
}
