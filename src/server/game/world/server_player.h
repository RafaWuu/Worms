//
// Created by xguss on 03/12/23.
//

#ifndef WORMS_SERVER_PLAYER_H
#define WORMS_SERVER_PLAYER_H

#include <cstdint>

#include "../entities/server_worm.h"

class Player {
    uint16_t client_id;
    std::vector<Worm*> worms;
    std::vector<Worm*>::iterator active_worm;

public:
    explicit Player(uint16_t client_id);

    void assign_worm(Worm& worm, bool extra_health);

    Worm& get_next_alive_worm();

    bool is_any_worm_alive() const;
};

#endif  // WORMS_SERVER_PLAYER_H
