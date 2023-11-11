#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include <SDL2pp/SDL2pp.hh>

#include "player.h"
#include "../game/worm.h"

#include "scenario_beam.h"
#include "../game/beam.h"

#include "../game/scenario.h"
// Contiene a los objetos renderizables (x ahora solo los gusanos/Players)
class WorldView {
private:
    TextureController& texture_controller;
    std::vector<Player> players;
    std::vector<ScenarioBeam> beams;
public:
    WorldView(TextureController& texture_controller,
    std::unique_ptr<Scenario> scenario);

    void update(std::vector<Worm> worms);

    void render(SDL2pp::Renderer& renderer);
};

#endif
