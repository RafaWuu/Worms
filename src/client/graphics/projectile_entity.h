//
// Created by xguss on 15/11/23.
//

#ifndef WORMS_projectile_ENTITY_H
#define WORMS_projectile_ENTITY_H

#include "animation.h"
#include "entity.h"

class projectileEntity: public Entity {
public:
    explicit projectileEntity(TextureController& texture_controller);
    ~projectileEntity();

    void update_info(EntityInfo* info) override;
    void update(float dt) override;
    void render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) override;

private:
    TextureController& texture_controller;
    Animation an;

    uint8_t type;
    int x;
    int y;
    int id;
};
#endif  // WORMS_projectile_ENTITY_H
