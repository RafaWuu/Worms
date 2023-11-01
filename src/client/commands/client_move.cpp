#include "client_move.h"

Move::Move(int dir) : dir(dir) {}

std::vector<uint8_t> Move::serialize(ClientProtocol& protocol) {
    return protocol.serialize_move(dir);
}