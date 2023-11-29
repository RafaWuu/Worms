#include "client_move.h"

Move::Move(int dir): dir(dir) {}

void Move::serialize(uint16_t worm, ClientProtocol& protocol) {
    return protocol.serialize_move(worm, dir);
}
