

#include "server_projectile_effect_noeffect.h"

bool ProjectileEffectNone::execute(GameWorld& world, b2Body& body) { return false; }

ProjectileEffectNone::ProjectileEffectNone(uint16_t projectile_id):
        ProjectileEffect(projectile_id) {}
