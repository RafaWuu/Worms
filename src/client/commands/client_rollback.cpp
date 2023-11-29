//
// Created by xguss on 10/11/23.
//

#include "client_rollback.h"

void Rollback::serialize(uint16_t worm, ClientProtocol& protocol) {
    return protocol.serialize_rollback(worm);
}

Rollback::Rollback() {}