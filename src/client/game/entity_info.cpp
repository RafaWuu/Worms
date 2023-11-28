//
// Created by xguss on 14/11/23.
//

#include "entity_info.h"

uint16_t EntityInfo::get_pos_x() const { return x; }

uint16_t EntityInfo::get_pos_y() const { return y; }

uint16_t EntityInfo::get_height() const { return height; }

uint16_t EntityInfo::get_width() const { return width; }

EntityInfo::EntityInfo(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height):
        x(pos_x), y(pos_y), width(width), height(height) {}
