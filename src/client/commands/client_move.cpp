#include "client_move.h"

Move::Move(int dir): dir(dir) {}

void Move::serialize(ClientProtocol& protocol) {
    return protocol.serialize_move(dir);
}
