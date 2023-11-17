//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_STATUSBROADCAST_MONITOR_H
#define WORMS_SERVER_STATUSBROADCAST_MONITOR_H

#include <cstdint>
#include <map>
#include <memory>
#include <mutex>

#include "../../common/common_queue.h"

#include "server_gamestatus.h"

class StatusBroadcastMonitor {

private:
    std::mutex mutex;
    std::map<uint16_t, Queue<std::shared_ptr<GameStatus>>&> queues_map;

public:
    StatusBroadcastMonitor();
    StatusBroadcastMonitor(const StatusBroadcastMonitor&) = delete;
    StatusBroadcastMonitor& operator=(const StatusBroadcastMonitor&) = delete;

    void add_queue(Queue<std::shared_ptr<GameStatus>>& q, uint16_t client_id);
    void remove_queue(uint16_t key);

    void send_status_toall(const std::shared_ptr<GameStatus>& status);

    void send_status(uint16_t client_id, const std::shared_ptr<GameStatus>& status);
};

#endif  // WORMS_SERVER_STATUSBROADCAST_MONITOR_H
