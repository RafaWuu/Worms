

#include "server_gameobject.h"

#include "game/world/server_gameworld.h"

#define OBJECT_LOG_SRC "../log/object_log.txt"

Log& GameObject::getLog() {
    static Log log_(OBJECT_LOG_SRC);
    return log_;
}
void GameObject::update(GameWorld& world) {}

void GameObject::delete_body() {}
