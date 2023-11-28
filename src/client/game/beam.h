#ifndef CLIENT_BEAM_H
#define CLIENT_BEAM_H

#include "entity_info.h"
class Beam: public EntityInfo {
private:
    float angle;

public:
    explicit Beam(uint16_t x, uint16_t y, uint16_t width, uint16_t height, float angle);
    float get_angle();
    uint16_t get_id() const override;
    std::unique_ptr<Entity> create(TextureController& controller) override;
};

#endif
