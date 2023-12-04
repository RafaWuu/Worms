#include "estado_juego.h"


EstadoJuego::EstadoJuego(uint16_t current_worm, float remaining_time, float wind,
                         std::map<uint16_t, std::unique_ptr<EntityInfo>>&& entities):
        entities_info(std::move(entities)) {
    this->current_worm = current_worm;
    this->remaining_time = remaining_time;
    this->wind = wind;
}


std::map<uint16_t, std::unique_ptr<EntityInfo>>& EstadoJuego::get_updated_info() {
    return entities_info;
}

uint16_t EstadoJuego::get_current_worm() const { return current_worm; }
