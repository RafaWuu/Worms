#include "projectile_controller.h"

// Poner esto directamente en TextureController?
AnimationState ProjectileController::get_projectile_texture(uint8_t projectile_id) {
    if (projectile_id == BAZOOKA_ID) return BAZOOKA_PROJECTILE;
    if (projectile_id == GREEN_GRENADE_ID) return GREEN_GRENADE_PROJECTILE;
    if (projectile_id == RED_GRENADE_ID) return RED_GRENADE_PROJECTILE;
    if (projectile_id == HOLY_GRENADE_ID) return HOLY_GRENADE_PROJECTILE;
    if (projectile_id == MORTAR_ID) return MORTAR_PROJECTILE;
    if (projectile_id == DYNAMITE_ID) return DYNAMITE_PROJECTILE;
    if (projectile_id == BANANA_ID) return BANANA_PROJECTILE;

    return BAZOOKA_PROJECTILE;
}