

#include "server_player_manager.h"

#include <algorithm>

#define DRAW UINT16_MAX

PlayerManager::PlayerManager(): players(), active_player() {}

void PlayerManager::assign_worms_to_players(const std::vector<uint16_t>& clients,
                                            std::map<uint16_t, Worm*>& worm_map) {
    for (auto& client: clients) {
        //  cppcheck-suppress useStlAlgorithm
        players.emplace_back(client);
    }

    active_player = players.begin();

    int i = 0;

    size_t n = worm_map.size();
    size_t last_player_full_of_worms = n % players.size() - 1;

    for (auto& worm: worm_map) {
        if (worm.second == nullptr)
            continue;

        bool extra_health = i % players.size() > last_player_full_of_worms;

        players[i % players.size()].assign_worm(*worm.second, extra_health);
        i++;
    }
}

bool PlayerManager::game_ended() {
    if (players.size() == 1)
        return !players[0].is_any_worm_alive();  // Si es single-player seguir hasta que no haya
                                                 // gusanos

    return std::count_if(players.begin(), players.end(), [&](const Player& player) {
               return player.is_any_worm_alive();
           }) <= 1;  // Si hay mas de 1 jugador, seguir hasta que solo quede uno
}

Worm& PlayerManager::get_next_worm_from_client() {
    if (active_player == players.end())
        active_player = players.begin();

    auto player = std::find_if(active_player, players.end(),
                               [&](const Player& player) { return player.is_any_worm_alive(); });

    if (player != players.end()) {
        active_player = player + 1;

        return player->get_next_alive_worm();
    }

    player = std::find_if(players.begin(), active_player,
                          [&](const Player& player) { return player.is_any_worm_alive(); });

    if (player != players.end()) {
        active_player = player + 1;
        return player->get_next_alive_worm();
    }

    throw;
}

uint16_t PlayerManager::last_client_alive() {
    if (players.size() == 1)
        return players[0].client_id;

    auto player = std::find_if(players.begin(), players.end(),
                               [&](const Player& player) { return player.is_any_worm_alive(); });

    if (player != players.end())
        return player->get_next_alive_worm().client_id;

    return DRAW;
}
