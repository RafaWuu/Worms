//
// Created by xguss on 03/12/23.
//

#include "server_player_manager.h"

PlayerManager::PlayerManager(): players(), active_player() {}

void PlayerManager::assign_worms_to_players(const std::vector<uint16_t>& clients,
                                            std::map<uint16_t, Worm*> worm_map) {
    for (auto& client: clients) players.emplace_back(client);

    active_player = players.begin();

    int i = 0;

    int n = worm_map.size();
    int last_player_full_of_worms = n % players.size() - 1;

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
    if (!active_player->is_any_worm_alive())
        ++active_player;

    auto& worm = active_player->get_next_alive_worm();
    ++active_player;

    if (active_player == players.end())
        active_player = players.begin();

    return worm;
}
