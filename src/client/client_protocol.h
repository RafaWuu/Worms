#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include <string.h>

#include "../common/common_baseprotocol.h"
#include "../common/common_socket.h"
#include "game/estado_juego.h"
#include "game/scenario.h"
#include "lobby/lobby_state.h"

#include "common_log.h"

struct ErrorLobby: public std::runtime_error {
    ErrorLobby(): std::runtime_error("Error occurred joining/creating game") {}
};

class ClientProtocol: public BaseProtocol {
protected:
    Log& getLog();

public:
    explicit ClientProtocol(Socket socket);

    std::vector<uint8_t> serialize_move(int dir);
    std::vector<uint8_t> serialize_stop_move();

    EstadoJuego recv_msg();
    void receive_worm(std::vector<Worm>& worms);

    void send_create_game(std::string& escenario);
    void send_join_game(const int& id);
    LobbyState receive_confirmation();

    Scenario receive_scenario();
    void receive_beam(std::vector<Beam> beams);

    std::map<uint8_t, uint16_t> receive_worms_distribution();

    void request_game_list();
    LobbyState receive_game_list();

    void send_start_game();

    /* Shutdown y close del socket */
    void close();

    void get_my_id(uint16_t& id);

    void set_worm_id(uint16_t i);

    uint8_t worm_id = 0;

    std::vector<uint8_t> serialize_jump(uint8_t type);
};

#endif
