

#ifndef WORMS_SERVER_PLAYER_MANAGER_H
#define WORMS_SERVER_PLAYER_MANAGER_H

#include <cstdint>
#include <map>
#include <vector>

#include "../entities/server_worm.h"

#include "server_player.h"

class PlayerManager {
private:
    std::vector<Player> players;
    std::vector<Player>::iterator active_player;

public:
    PlayerManager();
    void assign_worms_to_players(const std::vector<uint16_t>& clients,
                                 std::map<uint16_t, Worm*>& worm_map);

    Worm& get_next_worm_from_client();

    bool game_ended();

    uint16_t last_client_alive();
};

#endif  // WORMS_SERVER_PLAYER_MANAGER_H
