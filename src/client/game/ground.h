//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_GROUND_H
#define WORMS_GROUND_H


#include "entity_info.h"
class Ground: public EntityInfo {
private:
public:
    Ground(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    ;

    std::unique_ptr<Entity> create(TextureController& controller) override;
};


#endif  // WORMS_GROUND_H
