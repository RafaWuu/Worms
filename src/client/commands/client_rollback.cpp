//
// Created by xguss on 10/11/23.
//

#include "client_rollback.h"

void Rollback::serialize(ClientProtocol& protocol) {
    return protocol.serialize_rollback();
}

Rollback::Rollback(){

}