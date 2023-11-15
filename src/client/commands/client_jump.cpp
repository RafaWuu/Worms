//
// Created by xguss on 07/11/23.
//

#include "client_jump.h"

void Jump::serialize(ClientProtocol& protocol) {
    return protocol.serialize_jump();
}

Jump::Jump(){

}


