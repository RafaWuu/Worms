#include "client_stop_moving.h"

StopMoving::StopMoving() {}

void StopMoving::serialize(uint16_t worm, ClientProtocol& protocol) {
    return protocol.serialize_stop_move(worm);
}
