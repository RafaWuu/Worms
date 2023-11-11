//
// Created by xguss on 10/11/23.
//

#include "client_rollback.h"

std::vector<uint8_t> Rollback::serialize(ClientProtocol& protocol) {
    return protocol.serialize_rollback();
}

Rollback::Rollback(){

}