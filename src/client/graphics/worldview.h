#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include <SDL2pp/SDL2pp.hh>

#include "player.h"
#include "../game/worm.h"

// Contiene a los objetos renderizables (x ahora solo los gusanos/Players)
class WorldView {
private:
    TextureController& texture_controller;
    std::vector<Player> players;
public:
    WorldView(TextureController& texture_controller, std::vector<Worm> worms);

    void update(std::vector<Worm> worms);

    void render(SDL2pp::Renderer& renderer);
};

#endif
