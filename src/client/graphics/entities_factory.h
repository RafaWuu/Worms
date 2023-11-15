//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_ENTITIES_FACTORY_H
#define WORMS_ENTITIES_FACTORY_H

#include <memory>

#include "entity.h"
#include "texture_controller.h"
class EntityFactory {
private:
    TextureController& controller;
public:
    EntityFactory(TextureController& controller);
    std::unique_ptr<Entity> create(EntityInfo& info);
};
#endif  // WORMS_ENTITIES_FACTORY_H
