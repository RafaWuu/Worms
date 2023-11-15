#include "client_stop_moving.h"

StopMoving::StopMoving() {}

void StopMoving::serialize(ClientProtocol& protocol) {
    return protocol.serialize_stop_move();
}
