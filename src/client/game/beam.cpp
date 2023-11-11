#include "beam.h"

Beam::Beam(float x, float y, float height, float width, float angle) : 
    x(x), y(y), height(height), width(width), angle(angle) {}

float Beam::get_pos_x() { return x; }

float Beam::get_pos_y() { return y; }

float Beam::get_height()  { return height; }

float Beam::get_width()  { return width; }

float Beam::get_angle()  { return angle; }