#include "beam.h"

#include "graphics/scenario_beam.h"

Beam::Beam(uint16_t x, uint16_t y, uint16_t width, uint16_t height, float angle):
        angle(angle), EntityInfo(x, y, width, height) {}

float Beam::get_angle() { return angle; }

uint16_t Beam::get_id() const { return 0; }

std::unique_ptr<Entity> Beam::create(TextureController& controller) {
    return std::make_unique<ScenarioBeam>(controller, get_pos_x(), get_pos_y(), get_width(),
                                          get_height(), get_angle());
}
