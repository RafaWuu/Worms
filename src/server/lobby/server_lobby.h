

#ifndef WORMS_SERVER_LOBBY_H
#define WORMS_SERVER_LOBBY_H

#include <map>
#include <memory>
#include <string>
#include <vector>

class Game;

#include "../game/server_game.h"
#include "../game/server_gameinfo.h"

#include "common_liberror.h"


class LobbyMonitor {
private:
    Queue<uint16_t>& reap_queue;
    ScenarioFileHandler scenario_file_handler;
    std::mutex mutex;
    std::map<uint8_t, std::shared_ptr<Game>> games_map;
    uint16_t id;

public:
    explicit LobbyMonitor(Queue<uint16_t>& reap_queue);
    LobbyMonitor(const LobbyMonitor&) = delete;
    LobbyMonitor& operator=(const LobbyMonitor&) = delete;

    uint16_t create_game(const std::string& name, uint16_t client_id);
    std::shared_ptr<Game> join_game(uint16_t client_id, uint16_t game_id);

    std::vector<GameInfo> list_games() const;

    void close_game(uint16_t id);

    void close_all();

    std::map<std::string, uint16_t> list_scenarios();
};

#endif  // WORMS_SERVER_LOBBY_H
