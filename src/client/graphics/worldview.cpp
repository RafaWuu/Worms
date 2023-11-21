#include "worldview.h"

WorldView::WorldView(TextureController& texture_controller,
                    std::unique_ptr<Scenario> scenario,
                    std::map<uint16_t, SDL2pp::Color>& color_map, WeaponSelector& weapon_selector):
        texture_controller(texture_controller),
        entity_factory(texture_controller), 
        entities(),
        weapon_selector(weapon_selector) {

    camera = SDL2pp::Rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    for (auto& entity_info: scenario->get_entities_info()) {
        
        auto entity = entity_factory.create(*entity_info.second);

        if (Player* player = dynamic_cast<Player*>(entity.get())) { 
            auto color = color_map[player->get_id()];
            player->set_color(color);
        }

        entities.emplace(entity_info.first, std::move(entity) );
    }
}

void WorldView::update(std::map<uint16_t, std::unique_ptr<EntityInfo>>& updated_info) {
    for (auto& info: updated_info) {
        auto it = entities.find(info.first);
        if (it != entities.end()) {
            it->second->update(FRAME_RATE);
            it->second->update_info(info.second.get());

        } else {
            entities.emplace(info.first, entity_factory.create(*info.second));
        }
    }
}

void WorldView::render(SDL2pp::Renderer& renderer) {
    renderer.SetDrawColor(SDL2pp::Color(0, 0, 0, 255));
    renderer.Clear();
    render_background(renderer);
    for (auto& entity: entities) {
        entity.second->render(renderer, camera);
    }
    weapon_selector.render(renderer);

    renderer.Present();
}

void WorldView::render_background(SDL2pp::Renderer& renderer) {
    auto background = texture_controller.get_texture(SCENARIO_BACKGROUND);
    renderer.Copy(*background, SDL2pp::NullOpt, SDL2pp::Rect{0,0,640,480});
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
