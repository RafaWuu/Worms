//
// Created by xguss on 14/11/23.
//

#include "entities_factory.h"
EntityFactory::EntityFactory(TextureController& controller) : controller(controller) {}

std::unique_ptr<Entity> EntityFactory::create(EntityInfo& info) {
    return info.create(controller);
}
