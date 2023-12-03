//
// Created by xguss on 03/12/23.
//

#ifndef WORMS_PROVISION_ENTITY_H
#define WORMS_PROVISION_ENTITY_H

#include "entity.h"

class ProvisionEntity: public Entity {
private:
    TextureController& texture_controller;
    std::shared_ptr<SDL2pp::Texture> texture;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;

public:
    ProvisionEntity(TextureController& texture_controller, uint16_t x, uint16_t y, uint16_t width,
                    uint16_t height);
    ~ProvisionEntity();


    void render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) override;
};

#endif  // WORMS_PROVISION_ENTITY_H
