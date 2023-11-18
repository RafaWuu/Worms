#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <string.h>

#include "../common/common_baseprotocol_socket.h"
#include "../common/common_socket.h"
#include "game/estado_juego.h"
#include "game/ground.h"
#include "game/proyectil.h"
#include "game/scenario.h"
#include "lobby/lobby_state.h"

#include "common_log.h"

struct ErrorLobby: public std::runtime_error {
    ErrorLobby(): std::runtime_error("Error occurred joining/creating game") {}
};

class ClientProtocol {
private:
    BaseProtocol& baseProtocol;

protected:
    Log& getLog();

public:
    explicit ClientProtocol(BaseProtocol& bp);
    void serialize_move(int dir);
    void serialize_stop_move();
    void serialize_jump();
    void serialize_rollback();
    void serialize_aim(float x, float y);
    void serialize_stop_aim();
    void serialize_fire();


    std::shared_ptr<EstadoJuego> recv_msg();
    std::map<uint16_t, uint16_t> receive_worms_distribution();
    std::unique_ptr<Scenario> receive_scenario();

    std::unique_ptr<Worm> receive_worm();
    std::unique_ptr<Beam> receive_beam();
    std::unique_ptr<Ground> receive_ground();
    std::unique_ptr<Proyectil> receive_proyectil();

    void get_my_id(uint16_t& id);
    void set_worm_id(uint16_t i);

    LobbyState receive_confirmation();

    LobbyState receive_game_list();
    void send_join_game(const int& id);
    void send_create_game(std::string& escenario);
    void request_game_list();

    void send_start_game();


    uint8_t worm_id = 0;

    /* Shutdown y close del socket */
    void close();

    void serialize_power_attack();
};

#endif
