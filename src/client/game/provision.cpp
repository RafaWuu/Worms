//
// Created by xguss on 03/12/23.
//

#include "provision.h"

#include "graphics/provision_entity.h"

std::unique_ptr<Entity> Provision::create(TextureController& controller) {
    return std::make_unique<ProvisionEntity>(controller, x, y, width, height);
}

Provision::Provision(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height):
        EntityInfo(pos_x, pos_y, width, height) {}