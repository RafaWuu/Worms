#include "worldview.h"

WorldView::WorldView(TextureController& texture_controller,
    std::unique_ptr<Scenario> scenario): 
    texture_controller(texture_controller)
    {
    for (auto& worm : scenario->get_worms()) {
        Player player(texture_controller, worm.get_id());
        players.push_back(player);
    }

    for (auto& beam : scenario->get_beams()) {
        ScenarioBeam scenario_beam(texture_controller, 
                    beam.get_pos_x(),
                    beam.get_pos_y(),
                    beam.get_width(),
                    beam.get_height(),
                    beam.get_angle());
        beams.push_back(scenario_beam);
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
            // actualizo camara con la pos del gusano activo
        } 
    }
}

void WorldView::render(SDL2pp::Renderer& renderer) {
    SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.Get());
    
    //render scenario (beam, falta implementar ground(agua))
    for (auto& beam : beams) {
        beam.render(renderer); //camera.x, camera.y
    }
    //render jugador
    for (auto& player : players) {
        player.render(renderer); //camera.x, camera.y
    }

    renderer.Present();
}