//
// Created by xguss on 17/11/23.
//

#include "client_power_attack.h"

PowerAttack::PowerAttack() = default;

void PowerAttack::serialize(uint16_t worm, ClientProtocol& protocol) {
    return protocol.serialize_power_attack(worm);
}
