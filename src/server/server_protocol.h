//
// Created by xguss on 10/09/23.
//

#ifndef SOCKETS_2023C2_ABRAIDA_SERVER_PROTOCOL_GAMEINTERFACE_H
#define SOCKETS_2023C2_ABRAIDA_SERVER_PROTOCOL_GAMEINTERFACE_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../common/common_baseprotocol.h"
#include "../common/common_socket.h"
#include "game/entities/server_gameobject_info.h"
#include "game/server_gameinfo.h"

#include "common_liberror.h"
#include "common_log.h"

class GameObjectInfo;
class WormInfo;

class LobbyRequest;
class GameEvent;

class ServerProtocol: public BaseProtocol {
protected:
    Log& getLog();

private:
    std::unique_ptr<LobbyRequest> recv_create_game();
    std::unique_ptr<LobbyRequest> recv_join_game();
    std::unique_ptr<GameEvent> recv_move(uint16_t id_client);

public:
    explicit ServerProtocol(Socket skt);

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    std::unique_ptr<LobbyRequest> recv_lobby_msg();

    void send_lobby_errormessage(uint8_t error_code);

    void send_gameid_message(uint16_t game_id);

    void send_gameslist(std::vector<GameInfo>& games_vec);

    std::unique_ptr<GameEvent> recv_game_msg(uint16_t id_client);


    void send_status(uint16_t current_worm,
                     std::map<uint16_t, std::shared_ptr<GameObjectInfo>> entities);

    void send_scenario(std::map<uint16_t, std::shared_ptr<GameObjectInfo>>& entities, float height,
                       float width);

    void send_worms_list(const std::map<uint16_t, std::shared_ptr<WormInfo>>& worms);

    void send_game_errormessage(uint8_t code);

    void send_lobby_newclient(uint16_t id);

    std::unique_ptr<GameEvent> recv_rollback(uint16_t id_client);

    std::unique_ptr<GameEvent> recv_jump(uint16_t id_client);

    std::unique_ptr<GameEvent> recv_fire(uint16_t id_client);

    std::unique_ptr<GameEvent> recv_aim(uint16_t id_client);

    std::unique_ptr<GameEvent> recv_power(uint16_t id_client);
};


#endif  // SOCKETS_2023C2_ABRAIDA_SERVER_PROTOCOL_GAMEINTERFACE_H
