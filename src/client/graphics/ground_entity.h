//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_GROUND_ENTITY_H
#define WORMS_GROUND_ENTITY_H

#include <memory>

#include "entity.h"

class GroundEntity: public Entity {
private:
    TextureController& texture_controller;

    float x;
    float y;
    float width;
    float height;
    std::shared_ptr<SDL2pp::Texture> texture;

public:
    GroundEntity(TextureController controller, float d, float d1, float d2, float d3);
    void render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) override;
    void update_info(EntityInfo* info) override;
};
#endif  // WORMS_GROUND_ENTITY_H
