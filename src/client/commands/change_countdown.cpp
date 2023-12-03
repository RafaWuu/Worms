#include "change_countdown.h"

ChangeCountdown::ChangeCountdown(int countdown): countdown(countdown) {}

void ChangeCountdown::serialize(uint16_t worm, ClientProtocol& protocol) {
    return protocol.serialize_change_countdown(worm, countdown);
}
