//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_GROUND_H
#define WORMS_GROUND_H


#include "entity_info.h"
class Ground: public EntityInfo {
private:
    float x;
    float y;
    float height;
    float width;

public:
    Ground(float x, float y, float height, float width);;

    float get_pos_x() const override;
    float get_pos_y() const override;
    std::unique_ptr<Entity> create(TextureController &controller) override;
};


#endif  // WORMS_GROUND_H
