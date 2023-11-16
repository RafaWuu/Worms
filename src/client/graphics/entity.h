//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_ENTITY_H
#define WORMS_ENTITY_H

#include <cstdint>

#include <SDL2pp/Renderer.hh>

#include "game/entity_info.h"

class Entity {
private:
    float x = 0, y = 0;
    uint16_t id = 0;

public:
    virtual void update_info(EntityInfo* info){

    };
    virtual void update(float dt){

    };

    virtual void render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) = 0;

    virtual uint16_t get_id() const { return 0; };
};
#endif  // WORMS_ENTITY_H
