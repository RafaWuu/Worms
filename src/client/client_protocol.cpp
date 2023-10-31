#include "client_protocol.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <arpa/inet.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE 1

#define BYTE 1

#define MOVE_CODE 1

ClientProtocol::ClientProtocol(Socket socket): BaseProtocol(std::move(socket)) {}

void ClientProtocol::send_move(uint8_t dir) {

    send_1byte_number(MOVE_CODE);
    send_1byte_number(dir);
}

EstadoJuego ClientProtocol::recv_msg(){
    EstadoJuego estado;
    uint8_t cod_op;
    recv_1byte_number(cod_op);
    recv_1byte_number(estado.dir);
    return estado;
}


