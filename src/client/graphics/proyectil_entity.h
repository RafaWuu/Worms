//
// Created by xguss on 15/11/23.
//

#ifndef WORMS_PROYECTIL_ENTITY_H
#define WORMS_PROYECTIL_ENTITY_H

#include "animation.h"
#include "entity.h"

class ProyectilEntity: public Entity {
public:
    explicit ProyectilEntity(TextureController& texture_controller);
    ~ProyectilEntity();

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
#endif  // WORMS_PROYECTIL_ENTITY_H
