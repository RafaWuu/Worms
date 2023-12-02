#include "aim_info.h"

AimInfo::AimInfo(float angle, float pos_x, float pos_y, AimType type) : angle(angle), x(pos_x), y(pos_y), type(type) {}

float AimInfo::get_angle() { return angle; }

float AimInfo::get_x() { return x; }

float AimInfo::get_y() { return y; }

AimType AimInfo::get_type() { return type; }