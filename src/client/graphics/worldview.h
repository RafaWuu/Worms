#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include <SDL2pp/SDL2pp.hh>

#include "../game/beam.h"
#include "../game/scenario.h"
#include "../game/worm.h"
#include "../sound/sound_controller.h"
#include "weapons/weapon_selector.h"

#include "entities_factory.h"
#include "entity.h"
#include "explosion_entity.h"
#include "hud.h"
#include "player.h"
#include "scenario_beam.h"
#include "wind.h"
// Contiene a los objetos renderizables (x ahora solo los gusanos/Players)
class WorldView {
private:
    SDL2pp::Renderer& renderer;
    SDL2pp::Window& window;

    TextureController& texture_controller;
    EntityFactory entity_factory;

    SoundController& sound_controller;


    // Ground and Beams
    std::map<uint16_t, std::shared_ptr<Entity>> static_entities;
    // Worms, missiles, ...
    std::map<uint16_t, std::shared_ptr<Entity>> dynamic_entities;

    SDL2pp::Rect camera;
    void render_background();
    Hud* hud;
    WeaponSelector& weapon_selector;

    Wind wind;

public:
    WorldView(SDL2pp::Renderer& renderer, SDL2pp::Window& window,
              TextureController& texture_controller, std::unique_ptr<Scenario> scenario,
              std::map<uint16_t, SDL2pp::Color>& color_map, WeaponSelector& weapon_selector,
              std::vector<uint16_t>& my_worms_id, SoundController& sound_controller, Hud* hud);

    void update(std::map<uint16_t, std::unique_ptr<EntityInfo>>& updated_info,
                std::shared_ptr<EstadoJuego>& state);

    void render();

    void update_camera(float& x, float& y, float& w, float& h);

    void add_entities(std::map<uint16_t, std::unique_ptr<EntityInfo>>& source,
                      std::map<uint16_t, std::shared_ptr<Entity>>& destination,
                      std::map<uint16_t, SDL2pp::Color>& color_map,
                      std::vector<uint16_t> my_worms_id);

    void render_game_over(const std::string& status);
};

#endif
