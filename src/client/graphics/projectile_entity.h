//
// Created by xguss on 15/11/23.
//

#ifndef WORMS_projectile_ENTITY_H
#define WORMS_projectile_ENTITY_H

#include "animation.h"
#include "entity.h"
#include "weapons/weapon_factory.h"

class projectileEntity: public Entity {
public:
    explicit projectileEntity(TextureController& texture_controller, uint8_t type);
    ~projectileEntity();

    void update_info(EntityInfo* info, SoundController& sound_controller) override;
    void update(float dt) override;
    void render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) override;

private:
    TextureController& texture_controller;

    // Que arma disparo el proyectil (bazooka, granada, ...)
    std::unique_ptr<Weapon> weapon;

    WeaponFactory weapon_factory;

    Animation an;

    uint8_t type;
    int id;
    float angle;
    Configuration& config;
    int x;
    int y;
    uint16_t width;
    uint16_t height;

    bool was_just_thrown;
};
#endif  // WORMS_projectile_ENTITY_H
