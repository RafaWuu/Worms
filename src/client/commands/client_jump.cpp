//
// Created by xguss on 07/11/23.
//

#include "client_jump.h"

void Jump::serialize(uint16_t worm, ClientProtocol& protocol) {
    return protocol.serialize_jump(worm);
}

Jump::Jump() {}
