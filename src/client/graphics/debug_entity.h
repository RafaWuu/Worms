//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_DEBUG_ENTITY_H
#define WORMS_DEBUG_ENTITY_H

#include "entity.h"
class DebugEntity: public Entity {
private:
    TextureController& texture_controller;

    float x;
    float y;
    float width;
    float height;
    std::shared_ptr<SDL2pp::Texture> texture;

public:
    DebugEntity(TextureController controller, float d, float d1, float d2, float d3);
    void render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) override;
    void update_info(EntityInfo* info) override;
};
#endif  // WORMS_DEBUG_ENTITY_H
