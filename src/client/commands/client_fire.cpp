//
// Created by xguss on 14/11/23.
//

#include "client_fire.h"
void Fire::serialize(uint16_t worm, ClientProtocol& protocol) { protocol.serialize_fire(worm); }
