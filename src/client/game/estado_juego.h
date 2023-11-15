#ifndef ESTADO_JUEGO_H
#define ESTADO_JUEGO_H

#include <map>
#include <vector>

#include "entity_info.h"
#include "worm.h"

class EstadoJuego {
private:
    std::vector<Worm> worms;
    std::map<uint16_t, std::unique_ptr<EntityInfo>> entities_info;
public:
    explicit EstadoJuego(std::map<uint16_t, std::unique_ptr<EntityInfo>>&& entities);

    std::map<uint16_t, std::unique_ptr<EntityInfo>>& get_updated_info();

};

#endif