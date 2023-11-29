//
// Created by xguss on 14/11/23.
//

#include "client_aim.h"
Aim::Aim(int x, int y) {
    this->x = x;
    this->y = y;
}
void Aim::serialize(uint16_t worm, ClientProtocol& protocol) {
    return protocol.serialize_aim(worm, x, y);
}
