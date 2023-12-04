//
// Created by xguss on 02/11/23.
//

#include "server_statusbroadcast_monitor.h"

#include <memory>

#include "server_gamestatus.h"

StatusBroadcastMonitor::StatusBroadcastMonitor() = default;

void StatusBroadcastMonitor::add_queue(Queue<std::shared_ptr<GameStatus>>& q, uint16_t client_id) {
    std::lock_guard<std::mutex> lock(mutex);

    auto it = queues_map.find(client_id);
    if (it != queues_map.end()) {
        it->second.close();
        queues_map.erase(it);
    }
    queues_map.insert({client_id, q});
}

void StatusBroadcastMonitor::remove_queue(uint16_t key) {
    std::lock_guard<std::mutex> lock(mutex);

    auto it = queues_map.find(key);
    if (it != queues_map.end()) {
        it->second.close();
        queues_map.erase(it);
    }
}

void StatusBroadcastMonitor::send_status_toall(const std::shared_ptr<GameStatus>& status) {
    std::lock_guard<std::mutex> lock(mutex);

    for (auto& kv: queues_map) {
        try {
            if (!kv.second.try_push(status))
                kv.second.close();
        } catch (ClosedQueue& e) {}
    }
}

void StatusBroadcastMonitor::send_status(uint16_t client_id,
                                         const std::shared_ptr<GameStatus>& status) {
    std::lock_guard<std::mutex> lock(mutex);

    auto it = queues_map.find(client_id);
    if (it != queues_map.end()) {
        try {
            if (!it->second.try_push(status))
                it->second.close();
        } catch (ClosedQueue& e) {}
    }
}
