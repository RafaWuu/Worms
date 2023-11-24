#include "scenario.h"

#include <utility>


Scenario::Scenario(std::map<uint16_t, std::unique_ptr<EntityInfo>>&& dynamic_entities_info,
                   std::map<uint16_t, std::unique_ptr<EntityInfo>>&& static_entities_info,
                   float height, float width):
        dynamic_entities_info(std::move(dynamic_entities_info)),
        static_entities_info(std::move(static_entities_info)) {
    this->height = height;
    this->width = width;
}


std::map<uint16_t, std::unique_ptr<EntityInfo>>& Scenario::get_dynamic_entities_info() {
    return dynamic_entities_info;
}

std::map<uint16_t, std::unique_ptr<EntityInfo>>& Scenario::get_static_entities_info() {
    return static_entities_info;
}
