//
// Created by xguss on 03/12/23.
//

#ifndef WORMS_PROVISION_H
#define WORMS_PROVISION_H

#include "entity_info.h"

class Provision: public EntityInfo {
private:
public:
    Provision(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height);

    std::unique_ptr<Entity> create(TextureController& controller) override;
};

#endif  // WORMS_PROVISION_H
