#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include <vector>

#include <string.h>

#include "../common/common_socket.h"
#include "../common/common_baseprotocol.h"

// DTO para renderizar
struct Gusano {
    std::uint8_t id = 0;
    std::uint16_t pos_x = 0;
    std::uint16_t pos_y = 0;
    std::uint8_t cant_vida = 0;
};
struct EstadoJuego {
    std::uint8_t dir = 0;
    std::vector<Gusano> gusanos;
};

class ClientProtocol : public BaseProtocol {

public:
    explicit ClientProtocol(Socket socket);

    void send_move(uint8_t dir);

    EstadoJuego recv_msg();
    /* Shutdown y close del socket */
    void close();
};

#endif
