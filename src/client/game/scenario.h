#ifndef CLIENT_SCENARIO_H
#define CLIENT_SCENARIO_H

#include <map>
#include <vector>

#include "beam.h"
#include "ground.h"
#include "worm.h"

class Scenario {
private:
    // Worms, missiles, explosions, ...
    std::map<uint16_t, std::unique_ptr<EntityInfo>> dynamic_entities_info;
    // Beams & Ground (entities that should always be rendered, but aren't sent by the server every frame)
    std::map<uint16_t, std::unique_ptr<EntityInfo>> static_entities_info;

public:
    Scenario(std::map<uint16_t, std::unique_ptr<EntityInfo>>& dynamic_entities_info,
             std::map<uint16_t, std::unique_ptr<EntityInfo>>& static_entities_info, float height,
             float width);

    float width;
    float height;

    // Return Worms, missiles, ...
    std::map<uint16_t, std::unique_ptr<EntityInfo>>& get_dynamic_entities_info();

    // Return Ground and Beams
    std::map<uint16_t, std::unique_ptr<EntityInfo>>& get_static_entities_info();
};

#endif
