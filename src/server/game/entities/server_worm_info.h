//
// Created by xguss on 03/11/23.
//

#ifndef WORMS_SERVER_WORM_INFO_H
#define WORMS_SERVER_WORM_INFO_H

#include <cstdint>

#include "server_worm.h"

class WormInfo {

public:
    explicit WormInfo(const Worm& worm);
    uint8_t id;
    uint16_t client_id;
    float x;
    float y;
    uint8_t dir;
    uint16_t state;
    uint8_t health;
};
#endif  // WORMS_SERVER_WORM_INFO_H
