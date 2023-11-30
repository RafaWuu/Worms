#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include <SDL2pp/SDL2pp.hh>

#include "../game/beam.h"
#include "../game/scenario.h"
#include "../game/worm.h"
#include "weapons/weapon_selector.h"

#include "entities_factory.h"
#include "entity.h"
#include "player.h"
#include "scenario_beam.h"
#include "../sound/sound_controller.h"
#include "hud.h"
// Contiene a los objetos renderizables (x ahora solo los gusanos/Players)
class WorldView {
private:
    TextureController& texture_controller;
    EntityFactory entity_factory;

    SoundController& sound_controller;

    uint16_t current_worm;

    // Ground and Beams
    std::map<uint16_t, std::shared_ptr<Entity>> static_entities;
    // Worms, missiles, ...
    std::map<uint16_t, std::shared_ptr<Entity>> dynamic_entities;

    SDL2pp::Rect camera;
    void render_background(SDL2pp::Renderer& renderer);
    std::shared_ptr<Hud> hud;
    WeaponSelector& weapon_selector;

public:
    WorldView(TextureController& texture_controller, std::unique_ptr<Scenario> scenario,
              std::map<uint16_t, SDL2pp::Color>& color_map, WeaponSelector& weapon_selector,
              uint16_t current_worm, std::vector<uint16_t>& my_worms_id, SoundController& sound_controller,
              std::shared_ptr<Hud> hud);

    void update(std::map<uint16_t, std::unique_ptr<EntityInfo>>& updated_info, int current_worm);

    void render(SDL2pp::Renderer& renderer);

    void update_camera(float& x, float& y, float& w, float& h);

    void add_entities(std::map<uint16_t, std::unique_ptr<EntityInfo>>& source,
                      std::map<uint16_t, std::shared_ptr<Entity>>& destination,
                      std::map<uint16_t, SDL2pp::Color>& color_map,
                      std::vector<uint16_t> my_worms_id);
};

#endif
