//
// Created by xguss on 03/11/23.
//

#include "server_worm_info.h"

#include "server_worm.h"

WormInfo::WormInfo(const Worm& worm) {
    id = worm.id;
    client_id = worm.client_id;
    x = worm.body->GetPosition().x;
    y = worm.body->GetPosition().y;
    dir = worm.facing_right;

    state = worm.get_state();
    health = worm.health;
}
