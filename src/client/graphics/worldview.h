#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include <SDL2pp/SDL2pp.hh>

#include "../game/beam.h"
#include "../game/scenario.h"
#include "../game/worm.h"

#include "entities_factory.h"
#include "entity.h"
#include "player.h"
#include "scenario_beam.h"
// Contiene a los objetos renderizables (x ahora solo los gusanos/Players)
class WorldView {
private:
    TextureController& texture_controller;
    EntityFactory entity_factory;
    std::map<uint16_t, std::shared_ptr<Entity>> entities;
    SDL2pp::Rect camera;
    void render_background(SDL2pp::Renderer& renderer);

public:
    WorldView(TextureController& texture_controller, std::unique_ptr<Scenario> scenario);

    void update(std::map<uint16_t, std::unique_ptr<EntityInfo>>& updated_info);

    void render(SDL2pp::Renderer& renderer);

    void update_camera(float& x, float& y, float& w, float& h);
};

#endif
