#ifndef LOBBY_STATE_H
#define LOBBY_STATE_H

#include <string>
#include <vector>
#include <utility>
class LobbyState {
public:
    explicit LobbyState();
    int id;
    int valid;
    std::vector<std::pair<uint16_t, std::string>> game_list;
};
#endif  