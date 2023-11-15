#ifndef CLIENT_BEAM_H
#define CLIENT_BEAM_H

#include "entity_info.h"
class Beam : public EntityInfo{
private:
    float x;
    float y;
    float height;
    float width;
    float angle;
public:
    explicit Beam(float x, float y, float height, float width, float angle);
    float get_pos_x() const override;
    float get_pos_y() const override;
    float get_height();
    float get_width();
    float get_angle();
    uint16_t get_id() const override;
    std::unique_ptr<Entity> create(TextureController &controller) override;
};

#endif
