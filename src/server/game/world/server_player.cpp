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
    active_worm = worms.end() - 1;
}

Worm& Player::get_next_alive_worm() {
    if (active_worm == worms.end())
        active_worm = worms.begin();

    auto worm = std::find_if(active_worm, worms.end(),
                             [&](const Worm* worm) { return worm->worm_is_alive(); });

    if (worm != worms.end()) {
        active_worm = worm + 1;
        return **worm;
    }

    worm = std::find_if(worms.begin(), active_worm,
                        [&](const Worm* worm) { return worm->worm_is_alive(); });

    if (worm != worms.end()) {
        active_worm = worm + 1;
        return **worm;
    }

    throw;
}

bool Player::is_any_worm_alive() const {
    return std::count_if(worms.begin(), worms.end(),
                         [&](const Worm* worm) { return worm->worm_is_alive(); }) > 0;
}
