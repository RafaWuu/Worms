#ifndef ESTADO_JUEGO_H
#define ESTADO_JUEGO_H

#include <map>
#include <vector>

#include "entity_info.h"
#include "worm.h"

class EstadoJuego {
private:
    uint16_t current_worm;
    float remaining_time;
    float wind;
    std::vector<Worm> worms;
    std::map<uint16_t, std::unique_ptr<EntityInfo>> entities_info;

public:
    EstadoJuego(uint16_t current_worm, float remaining_time, float wind,
                std::map<uint16_t, std::unique_ptr<EntityInfo>>&& entities);

    std::map<uint16_t, std::unique_ptr<EntityInfo>>& get_updated_info();

    uint16_t get_current_worm() const;

    float get_wind();
};

#endif