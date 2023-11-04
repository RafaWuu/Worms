#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include <vector>
#include <stdexcept>
#include <string.h>

#include "../common/common_baseprotocol.h"
#include "../common/common_socket.h"
#include "game/estado_juego.h"

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

    int16_t receive_confirmation_create();

    /* Shutdown y close del socket */
    void close();
};

#endif
