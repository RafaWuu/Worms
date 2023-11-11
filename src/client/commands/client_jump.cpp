//
// Created by xguss on 07/11/23.
//

#include "client_jump.h"

std::vector<uint8_t> Jump::serialize(ClientProtocol& protocol) {
    return protocol.serialize_jump();
}

Jump::Jump(){

}


