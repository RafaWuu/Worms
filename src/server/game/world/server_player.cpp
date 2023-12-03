//
// Created by xguss on 03/12/23.
//

#include "server_player.h"

Player::Player(uint16_t client_id): client_id(client_id), worms(), active_worm() {}

void Player::assign_worm(Worm& worm, bool extra_health) {
    worm.set_client_id(client_id);
    if (extra_health)
        worm.set_extra_health();

    worms.emplace_back(&worm);
    active_worm = worms.begin();
}

Worm& Player::get_next_alive_worm() {
    auto worm = active_worm;
    ++active_worm;

    if (active_worm == worms.end())
        active_worm = worms.begin();

    return **worm;
}

bool Player::is_any_worm_alive() const {
    return std::count_if(worms.begin(), worms.end(),
                         [&](const Worm* worm) { return worm->health > 0; });
}
