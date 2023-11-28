//
// Created by xguss on 14/11/23.
//

#include "client_aim.h"
Aim::Aim(int x, int y) {
    this->x = x;
    this->y = y;
}
void Aim::serialize(ClientProtocol& protocol) { return protocol.serialize_aim(x, y); }
