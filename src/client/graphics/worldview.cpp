#include "worldview.h"

WorldView::WorldView(TextureController& texture_controller, std::unique_ptr<Scenario> scenario,
                     std::map<uint16_t, SDL2pp::Color>& color_map, WeaponSelector& weapon_selector,
                     uint16_t current_worm, std::vector<uint16_t>& my_worms_id, SoundController& sound_controller,
                     std::shared_ptr<Hud> hud):
        texture_controller(texture_controller),
        entity_factory(texture_controller),
        weapon_selector(weapon_selector),
        current_worm(current_worm),
        sound_controller(sound_controller){
    hud = hud;
    camera = SDL2pp::Rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    add_entities(scenario->get_dynamic_entities_info(), dynamic_entities, color_map, my_worms_id);
    add_entities(scenario->get_static_entities_info(), static_entities, color_map, my_worms_id);
}

void WorldView::update(std::map<uint16_t, std::unique_ptr<EntityInfo>>& updated_info, int current_worm) {

    // Remove dynamic entities the server doesn't send (already exploded missiles, ...)
    for (auto it = dynamic_entities.begin(); it != dynamic_entities.end();) {
        if (updated_info.find(it->first) == updated_info.end()) {
            it = dynamic_entities.erase(it);
        } else {
            ++it;
        }
    }
        // hud->update_current_worm(current_worm);
    for (auto& info: updated_info) {
        auto it = dynamic_entities.find(info.first);
        if (it != dynamic_entities.end()) {
            it->second->update(FRAME_RATE);
            it->second->update_info(info.second.get(), sound_controller);

        } else {
            dynamic_entities.emplace(info.first, entity_factory.create(*info.second));
        }
    }
}

void WorldView::render(SDL2pp::Renderer& renderer) {
    renderer.SetDrawColor(SDL2pp::Color(0, 0, 0, 255));
    renderer.Clear();
    render_background(renderer);
    hud->render(renderer);
    for (auto& entity: static_entities) {
        entity.second->render(renderer, camera);
    }
    for (auto& entity: dynamic_entities) {
        entity.second->render(renderer, camera);
    }

    weapon_selector.render(renderer);

    renderer.Present();
}

void WorldView::render_background(SDL2pp::Renderer& renderer) {
    auto background = texture_controller.get_texture(SCENARIO_BACKGROUND);
    renderer.Copy(*background, SDL2pp::NullOpt, SDL2pp::Rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
}
// offset segun la posicion del objeto a enfocar.
void WorldView::update_camera(float& x, float& y, float& w, float& h) {

    camera.x = (x + w / 2) * PPM - SCREEN_WIDTH / 2;
    camera.y = ((-1) * y + h / 2) * PPM - SCREEN_HEIGHT / 2;

    if (camera.x < 0)
        camera.x = 0;

    if (camera.y < 0)
        camera.y = 0;

    if (camera.x > LEVEL_WIDTH - camera.w)
        camera.x = LEVEL_WIDTH - camera.w;

    if (camera.y > LEVEL_HEIGHT - camera.h)
        camera.y = LEVEL_HEIGHT - camera.h;
}

void WorldView::add_entities(std::map<uint16_t, std::unique_ptr<EntityInfo>>& source,
                             std::map<uint16_t, std::shared_ptr<Entity>>& destination,
                             std::map<uint16_t, SDL2pp::Color>& color_map,
                             std::vector<uint16_t> my_worms_id) {

    for (auto& entity_info: source) {

        auto entity = entity_factory.create(*entity_info.second);

        if (Player* player = dynamic_cast<Player*>(entity.get())) {
            auto color = color_map[player->get_id()];
            player->set_color(color);
            player->set_hud(hud);
            // Si es mi gusano le agrego el crosshair
            if (std::find(my_worms_id.begin(), my_worms_id.end(), player->get_id()) !=
                my_worms_id.end())
                player->add_crosshair();
        }

        destination.emplace(entity_info.first, std::move(entity));
    }
}