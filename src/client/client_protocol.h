#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <string.h>

#include "../../configuration/configuration.h"
#include "../common/common_baseprotocol_socket.h"
#include "../common/common_socket.h"
#include "game/estado_juego.h"
#include "game/explosion.h"
#include "game/ground.h"
#include "game/projectile.h"
#include "game/provision.h"
#include "game/scenario.h"
#include "lobby/lobby_state.h"

#include "common_log.h"

struct ErrorLobby: public std::runtime_error {
    ErrorLobby(): std::runtime_error("Error occurred joining/creating game") {}
};

class ClientProtocol {
private:
    BaseProtocol& baseProtocol;
    Configuration& config;

protected:
    Log& getLog();

public:
    explicit ClientProtocol(BaseProtocol& bp);

    // TODO: pasar a uint16
    void serialize_move(uint8_t worm, int dir);
    void serialize_stop_move(uint8_t worm);
    void serialize_jump(uint8_t worm);
    void serialize_rollback(uint8_t worm);
    void serialize_aim(uint8_t worm, float x, float y);
    void serialize_stop_aim(uint8_t worm);
    void serialize_fire(uint8_t worm);
    void serialize_change_weapon(uint8_t worm, int weapon_id);
    void serialize_power_attack(uint8_t worm);


    std::shared_ptr<EstadoJuego> recv_msg();
    std::map<uint16_t, uint16_t> receive_worms_distribution();
    std::unique_ptr<Scenario> receive_scenario();

    std::unique_ptr<Worm> receive_worm_initial_status();
    std::unique_ptr<Worm> receive_worm();
    std::unique_ptr<Beam> receive_beam();
    std::unique_ptr<Ground> receive_ground();
    std::unique_ptr<Projectile> receive_projectile();
    std::unique_ptr<Explosion> receive_explosion();

    void get_my_id(uint16_t& id);
    void set_worm_id(uint16_t i);

    LobbyState receive_confirmation();

    LobbyState receive_game_list();
    void send_join_game(const int& id);
    void send_create_game(std::string& escenario);
    void request_game_list();

    void send_start_game();

    /* Shutdown y close del socket */
    void close();

    std::unique_ptr<Provision> receive_provision();
};

#endif
