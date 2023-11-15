#include "beam.h"

#include "graphics/scenario_beam.h"

Beam::Beam(float x, float y, float height, float width, float angle) : 
    x(x), y(y), height(height), width(width), angle(angle) {}

float Beam::get_pos_x() const { return x; }

float Beam::get_pos_y() const { return y; }

float Beam::get_height()  { return height; }

float Beam::get_width()  { return width; }

float Beam::get_angle()  { return angle; }

uint16_t Beam::get_id() const {return 0;}

std::unique_ptr<Entity> Beam::create(TextureController& controller) {
    return std::make_unique<ScenarioBeam>(controller,
                               get_pos_x(),
                               get_pos_y(),
                               get_width(),
                               get_height(),
                               get_angle());
}
