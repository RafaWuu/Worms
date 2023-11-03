//
// Created by xguss on 31/10/23.
//

#ifndef WORMS_SERVER_GAME_H
#define WORMS_SERVER_GAME_H


#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "../../common/common_queue.h"

#include "common_thread.h"
#include "server_event_handler.h"
#include "server_gameevent.h"
#include "server_gameinfo.h"
#include "server_gameworld.h"
#include "server_statusbroadcast_monitor.h"

class Game: Thread {
private:
    std::mutex mutex;
    GameWorld game_world;
    uint16_t game_id;
    uint16_t owner_id;
    std::vector<uint16_t> id_lists;

    Queue<std::shared_ptr<GameEvent>> event_queue;
    StatusBroadcastMonitor broadcastMonitor;
    EventHandler eventHandler;

    std::atomic<bool> is_alive;
    bool had_started;


public:
    explicit Game(uint16_t game_id, std::string& scenario, uint16_t owner_id_);

    void run() override;
    void kill();
    bool is_dead();

    void subscribe_queue(Queue<std::shared_ptr<GameStatus>>& queue, uint16_t client_id);

    void push_event(const std::shared_ptr<GameEvent>& event);

    void add_player(uint16_t client_id);

    std::string name;

    void exit_game(uint16_t client_id);

    GameInfo get_info();
};
#endif  // WORMS_SERVER_GAME_H
