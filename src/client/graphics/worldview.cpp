#include "worldview.h"

WorldView::WorldView(SDL2pp::Renderer& renderer,TextureController& texture_controller, std::unique_ptr<Scenario> scenario,
                     std::map<uint16_t, SDL2pp::Color>& color_map, WeaponSelector& weapon_selector,
                     std::vector<uint16_t>& my_worms_id, SoundController& sound_controller,
                     Hud* hud):
        renderer(renderer),
        texture_controller(texture_controller),
        entity_factory(texture_controller),
        weapon_selector(weapon_selector),
        sound_controller(sound_controller),
        wind(texture_controller, 0),
        hud(hud){
    camera = SDL2pp::Rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    add_entities(scenario->get_dynamic_entities_info(), dynamic_entities, color_map, my_worms_id);
    add_entities(scenario->get_static_entities_info(), static_entities, color_map, my_worms_id);
}

void WorldView::update(std::map<uint16_t, std::unique_ptr<EntityInfo>>& updated_info, std::shared_ptr<EstadoJuego>& state) {

    // Remove dynamic entities the server doesn't send (already exploded missiles, ...)

    for (auto it = dynamic_entities.begin(); it != dynamic_entities.end();) {
        if (updated_info.find(it->first) == updated_info.end()) {
            it = dynamic_entities.erase(it);
        } else {
            ++it;
        }
    }
    hud->update_time(state->get_remaining_time());
    for (auto& info: updated_info) {
        auto it = dynamic_entities.find(info.first);
        if (it != dynamic_entities.end()) {
            it->second->update(FRAME_RATE);
            it->second->update_info(info.second.get(), sound_controller);

        } else {
            dynamic_entities.emplace(info.first, entity_factory.create(*info.second));
        }
    }

    this->wind.change_wind(state->get_wind());
}

void WorldView::render() {
    renderer.SetDrawColor(SDL2pp::Color(0, 0, 0, 255));
    renderer.Clear();
    render_background();

    for (auto& entity: static_entities) {
        entity.second->render(renderer, camera);
    }
    for (auto& entity: dynamic_entities) {
        entity.second->render(renderer, camera);
    }

    weapon_selector.render(renderer);

    wind.render(renderer, camera);
    hud->render();
    renderer.Present();

}

static std::unique_ptr<SDL2pp::Font> get_font(int size) {
    try {
        std::string path = std::string(ASSETS_PATH)+"Vera.ttf";
        return std::make_unique<SDL2pp::Font> (path, size);
    } catch (SDL2pp::Exception& e) {
        std::cerr<<"Error font: "<<e.what()<<std::endl; 
    }
    
}

void WorldView::render_game_over(const std::string& game_status) {
    renderer.SetDrawColor(SDL2pp::Color(0, 0, 0, 255));
    renderer.Clear();
    render_background();

    for (auto& entity: static_entities) {
        entity.second->render(renderer, camera);
    }
    for (auto& entity: dynamic_entities) {
        entity.second->render(renderer, camera);
    }

    weapon_selector.render(renderer);

    wind.render(renderer, camera);
    hud->render();

    std::unique_ptr<SDL2pp::Font> font = get_font(48);
    SDL2pp::Texture status_text(renderer,
                                font->RenderText_Blended(game_status, SDL2pp::Color{255, 0, 0, 255}));
    renderer.Copy(status_text, SDL2pp::NullOpt,
                  SDL2pp::Rect(0, status_text.GetWidth(), status_text.GetWidth(),
                               status_text.GetHeight()));
    
    std::this_thread::sleep_for(std::chrono::seconds(4));
}

void WorldView::render_background() {
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
        // si entity_info es un worm creo a player con un constructor propio??
        // if (Worm* worm = dynamic_cast<Worm*>(*entity.info.second.get()));
        // Player(entity_info worm, color, hud); else..
        auto entity = entity_factory.create(*entity_info.second);

        if (Player* player = dynamic_cast<Player*>(entity.get())) {
            auto color = color_map[player->get_id()];
            player->set_color(color);
            player->set_hud(hud);
            auto worm = dynamic_cast<Worm*>(entity_info.second.get());
            player->set_health(worm->get_health());
            // Si es mi gusano le agrego el crosshair
            if (std::find(my_worms_id.begin(), my_worms_id.end(), player->get_id()) !=
                my_worms_id.end())
                player->add_crosshair();
            destination.emplace(entity_info.first, std::move(entity));
        }else{
            destination.emplace(entity_info.first, std::move(entity));
        }
    }
}