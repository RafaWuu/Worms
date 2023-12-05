#include "estado_juego.h"


EstadoJuego::EstadoJuego(uint16_t current_worm, float remaining_time, float wind,
                         std::map<uint16_t, std::unique_ptr<EntityInfo>>&& entities, bool game_over , uint16_t winner_id):
        entities_info(std::move(entities)) {
    this->current_worm = current_worm;
    this->remaining_time = remaining_time;
    this->wind = wind;
    this->game_over = game_over;
    this->winner_id = winner_id;
}


std::map<uint16_t, std::unique_ptr<EntityInfo>>& EstadoJuego::get_updated_info() {
    return entities_info;
}

uint16_t EstadoJuego::get_current_worm() const { return current_worm; }
float EstadoJuego::get_remaining_time() { return remaining_time; }
float EstadoJuego::get_wind() { return wind; }

bool EstadoJuego::is_game_over() {
    return game_over;
}

uint16_t EstadoJuego::get_winner_id() {
    return winner_id;
}