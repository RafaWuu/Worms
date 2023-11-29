//
// Created by xguss on 14/11/23.
//

#include "client_stop_aim.h"
void StopAim::serialize(uint16_t worm, ClientProtocol& protocol) {
    protocol.serialize_stop_aim(worm);
}
