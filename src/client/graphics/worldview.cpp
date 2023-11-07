#include "worldview.h"

WorldView::WorldView(TextureController& texture_controller, std::vector<Worm> worms) : texture_controller(texture_controller) {
    for (auto& worm : worms) {
        Player player(texture_controller, worm.get_id());
        players.push_back(player);
    }
}

void WorldView::update(std::vector<Worm> worms) {
    for (auto worm : worms) {
        auto it = std::find_if(players.begin(), players.end(), [worm](const Player &player) {
            return player.get_id() == worm.get_id();
        });

        if (it != players.end()) {
            Player& player = *it;
            player.update(FRAME_RATE);
            player.update_info(worm);
        } 
    }
}

void WorldView::render(SDL2pp::Renderer& renderer) {
    SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.Get());

    for (auto& player : players) {
        player.render(renderer);
    }

    renderer.Present();
}