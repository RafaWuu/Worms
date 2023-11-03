#ifndef ESTADO_JUEGO_H
#define ESTADO_JUEGO_H

#include <vector>
#include "worm.h"

class EstadoJuego {
private:
    std::vector<Worm> worms;
public:
    explicit EstadoJuego(const std::vector<Worm>& worms);

    std::vector<Worm> get_worms();
};

#endif