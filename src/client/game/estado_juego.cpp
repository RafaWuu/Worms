#include "estado_juego.h"


EstadoJuego::EstadoJuego(std::map<uint16_t, std::unique_ptr<EntityInfo>>&& entities):
        entities_info(std::move(entities)) {}


std::map<uint16_t, std::unique_ptr<EntityInfo>>& EstadoJuego::get_updated_info() {
    return entities_info;
}
