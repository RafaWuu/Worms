//
// Created by xguss on 03/12/23.
//

#ifndef WORMS_PROVISION_ENTITY_H
#define WORMS_PROVISION_ENTITY_H

#include "entity.h"

#include "animation.h"
#include "camera.h"

class ProvisionEntity: public Entity {
private:
    TextureController& texture_controller;
    Animation an;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;

public:
    ProvisionEntity(TextureController& texture_controller, uint16_t x, uint16_t y, uint16_t width,
                    uint16_t height);
    ~ProvisionEntity();

    void update(float dt) override;

    void update_info(EntityInfo* info, SoundController& sound_controller) override;

    void render(SDL2pp::Renderer& renderer, Camera& camera) override;
};

#endif  // WORMS_PROVISION_ENTITY_H
