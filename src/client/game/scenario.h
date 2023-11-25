#ifndef CLIENT_SCENARIO_H
#define CLIENT_SCENARIO_H

#include <map>
#include <vector>

#include "beam.h"
#include "ground.h"
#include "worm.h"

class Scenario {
private:

    std::map<uint16_t, std::unique_ptr<EntityInfo>> entities_info;

public:
    Scenario(std::map<uint16_t, std::unique_ptr<EntityInfo>>& entities_info,
             float height, float width);

    float width;
    float height;
    std::map<uint16_t, std::unique_ptr<EntityInfo>>& get_entities_info();
};

#endif
