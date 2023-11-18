//
// Created by xguss on 14/11/23.
//

#include "client_aim.h"
Aim::Aim(int x, int y) {
    this->x = x / (float)SCREEN_WIDTH * 20.0;
    this->y = -y / (float)SCREEN_HEIGHT * 20.0;
}
void Aim::serialize(ClientProtocol& protocol) { return protocol.serialize_aim(x, y); }
