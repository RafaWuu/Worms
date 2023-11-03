#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include <vector>

#include <string.h>

#include "../common/common_baseprotocol.h"
#include "../common/common_socket.h"
#include "game/estado_juego.h"

class ClientProtocol: public BaseProtocol {

public:
    explicit ClientProtocol(Socket socket);

    std::vector<uint8_t> serialize_move(int dir);
    std::vector<uint8_t> serialize_stop_move();

    EstadoJuego recv_msg();
    void recv_worm(std::vector<Worm>& worms);
    /* Shutdown y close del socket */
    void close();
};

#endif
