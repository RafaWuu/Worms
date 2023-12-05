

#ifndef WORMS_SERVER_GAME_REAPER_H
#define WORMS_SERVER_GAME_REAPER_H

#include "lobby/server_lobby.h"

#include "common_thread.h"

class GameReaper: public Thread {
private:
    LobbyMonitor& lobby;
    Queue<uint16_t>& reap_queue;

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
