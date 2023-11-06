//
// Created by xguss on 04/11/23.
//

#include "server_gameobject.h"

#define OBJECT_LOG_SRC "../log/object_log.txt"

ObjectType GameObject::get_id(){
    return BOUNDARIE;
}

Log &GameObject::getLog(){
    static Log log_(OBJECT_LOG_SRC);
    return log_;
}

GameObject::GameObject()= default;
