#ifndef CLIENT_WORMS_EXPLOSION_INFO_H
#define CLIENT_WORMS_EXPLOSION_INFO_H

#include <memory>

#include "entity_info.h"

class Explosion: public EntityInfo {

private:
    float radius;

public:
    Explosion(uint8_t type, uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height,
               float radius);

    float get_radius() const;

    std::unique_ptr<Entity> create(TextureController& controller) override;

    uint8_t type;
};
#endif 
