//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_EVENT_HANDLER_H
#define WORMS_SERVER_EVENT_HANDLER_H

#include <cstdint>
#include <vector>

#include "server_gameworld.h"
#include "server_statusbroadcast_monitor.h"

class EventHandler {
private:
    bool& had_started;

    std::vector<uint16_t>& id_list;
    GameWorld& game_world;
    StatusBroadcastMonitor& broadcast;
    uint16_t& game_owner;

public:
    EventHandler(GameWorld& game_world, StatusBroadcastMonitor& broadcast,
                 std::vector<uint16_t>& id_list, bool& had_started, uint16_t& game_owner);

    void create_game(uint16_t client_id);

    void move_worm(uint16_t client_id, uint8_t worm_id, MovementEnum code);
};
#endif  // WORMS_SERVER_EVENT_HANDLER_H
