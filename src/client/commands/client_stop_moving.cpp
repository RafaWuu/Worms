#include "client_stop_moving.h"

StopMoving::StopMoving() {}

std::vector<uint8_t> StopMoving::serialize(ClientProtocol& protocol) {
    return protocol.serialize_stop_move();
}
