//
// Created by xguss on 17/11/23.
//

#ifndef WORMS_SERVER_GAME_REAPER_H
#define WORMS_SERVER_GAME_REAPER_H

#include "lobby/server_lobby.h"

#include "common_thread.h"

class GameReaper: public Thread {
private:
    LobbyMonitor& lobby;
    Queue<uint16_t>& reap_queue;

    // utilizar el atomic_bool que viene de la clase padre (aca y en todos lados en donde se necesite)
    std::atomic<bool> is_alive;
    void kill_all();

public:
    GameReaper(LobbyMonitor& lobby, Queue<uint16_t>& reap_queue);

    GameReaper(const GameReaper&) = delete;
    GameReaper& operator=(const GameReaper&) = delete;
    ~GameReaper() override;
    void run() override;

    void kill();
};

#endif  // WORMS_SERVER_GAME_REAPER_H
