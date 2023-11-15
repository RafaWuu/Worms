#include "scenario.h"

#include <utility>


Scenario::Scenario(std::map<uint16_t, std::unique_ptr<EntityInfo>>&& entities_info,
                   float height, float width) :
        entities_info(std::move(entities_info)) {
    this->height = height;
    this->width = width;
}


std::map<uint16_t, std::unique_ptr<EntityInfo>>& Scenario::get_entities_info() {
    return entities_info;
}
