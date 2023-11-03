//
// Created by xguss on 31/10/23.
//

#include "server_clientstate.h"


ClientState::ClientState(uint16_t client_id, ServerProtocol& gp):
        client_id(client_id), gp(gp), is_alive(true) {}
