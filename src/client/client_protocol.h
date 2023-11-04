#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include <vector>
#include <stdexcept>
#include <string.h>

#include "../common/common_baseprotocol.h"
#include "../common/common_socket.h"
#include "game/estado_juego.h"
#include "lobby/lobby_state.h"

struct ErrorLobby: public std::runtime_error {
    ErrorLobby(): std::runtime_error("Error occurred joining/creating game") {}
};

class ClientProtocol: public BaseProtocol {

public:
    explicit ClientProtocol(Socket socket);

    std::vector<uint8_t> serialize_move(int dir);
    std::vector<uint8_t> serialize_stop_move();

    EstadoJuego recv_msg();
    void recv_worm(std::vector<Worm>& worms);

    void send_create_game(std::string& escenario);
    void send_join_game(int& id);
    LobbyState receive_confirmation();

    void request_game_list();
    LobbyState receive_game_list(); 

    void send_start_game();

    /* Shutdown y close del socket */
    void close();
};

#endif
