#include "worldview.h"

WorldView::WorldView(TextureController& texture_controller,
    std::unique_ptr<Scenario> scenario): texture_controller(texture_controller), entity_factory(texture_controller),
        entities()
    {

    for (auto& entity_info: scenario->get_entities_info()){
        entities.emplace(entity_info.first, entity_factory.create(*entity_info.second));
    }
}

void WorldView::update(std::map<uint16_t, std::unique_ptr<EntityInfo>>& updated_info) {
    for (auto& info:updated_info) {
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
    SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.Get());

    for (auto& entity:entities) {
        entity.second->render(renderer);
    }

    renderer.Present();
}