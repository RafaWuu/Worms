//
// Created by xguss on 10/09/23.
//

#ifndef SOCKETS_2023C2_ABRAIDA_SERVER_PROTOCOL_GAMEINTERFACE_H
#define SOCKETS_2023C2_ABRAIDA_SERVER_PROTOCOL_GAMEINTERFACE_H

#include <memory>
#include <string>
#include <vector>

#include "../common/common_baseprotocol.h"
#include "../common/common_socket.h"
#include "game/entities/server_beam_info.h"
#include "game/entities/server_worm_info.h"
#include "game/server_gameinfo.h"

#include "common_liberror.h"
#include "common_log.h"

struct InvalidMsg: public LibError {
    InvalidMsg(): LibError(EBADRQC, "The message is invalid") {}
};

class LobbyRequest;
class GameEvent;

class ServerProtocol: public BaseProtocol {
protected:
    Log& getLog();

private:
    std::unique_ptr<LobbyRequest> recv_create_game();
    std::unique_ptr<LobbyRequest> recv_join_game();
    std::unique_ptr<GameEvent> recv_move(uint16_t id_client);
    MovementEnum serialize_move(uint8_t code);

public:
    explicit ServerProtocol(Socket skt);

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

    std::unique_ptr<LobbyRequest> recv_lobby_msg();

    void send_lobby_errormessage(uint8_t error_code);

    void send_gameid_message(uint16_t game_id);

    void send_gameslist(std::vector<GameInfo>& games_vec);

    std::unique_ptr<GameEvent> recv_game_msg(uint16_t id_client);


    void send_status(uint8_t current_worm, std::vector<WormInfo>& worms_vec);

    void send_scenario(std::vector<BeamInfo>& beams_vec, std::vector<WormInfo>& worms_vec);

    void send_worms_list(std::vector<WormInfo>& worms_vec);

    void send_game_errormessage(uint8_t code);
};

#endif  // SOCKETS_2023C2_ABRAIDA_SERVER_PROTOCOL_GAMEINTERFACE_H
