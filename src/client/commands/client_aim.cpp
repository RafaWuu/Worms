//
// Created by xguss on 14/11/23.
//

#include "client_aim.h"
Aim::Aim(int x, int y) {
    this->x = x / 640.0 * 20.0;
    this->y = (-y + 480.0) / 480.0 * 20.0;
}
void Aim::serialize(ClientProtocol& protocol) {
    return protocol.serialize_aim(x, y);
}
