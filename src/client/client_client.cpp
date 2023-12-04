#include "client_client.h"

#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <SDL2pp/Mixer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <unistd.h>

#include "../common/common_liberror.h"
#include "../common/common_socket.h"
#include "../configuration/configuration.h"
#include "commands/client_jump.h"
#include "commands/client_move.h"
#include "commands/client_rollback.h"
#include "commands/client_stop_moving.h"
#include "graphics/animation.h"
#include "graphics/weapons/weapon_selector.h"
#include "graphics/worldview.h"
#include "sound/sound_controller.h"

#include "client_protocol.h"

using namespace std::chrono;

#define SUCCESS 0
#define FAILURE 1

Client::Client(const std::string& hostname, const std::string& servicename):
        socket(hostname.c_str(), servicename.c_str()),
        bp(std::move(socket)),
        protocol(bp),
        messages_to_send(1000),
        messages_received(1000),
        event_handler(),
        my_worms_id_vec() {

    sender = std::make_unique<ClientSender>(protocol, messages_to_send);
    receiver = std::make_unique<ClientReceiver>(protocol, messages_received);

    protocol.get_my_id(my_id);  // Reubicar
    current_worm = 0;
}

Client::~Client() { kill(); }

void Client::kill() {
    messages_to_send.close();
    messages_received.close();

    protocol.close();
    sender->kill();
    receiver->kill();

    sender->join();
    receiver->join();
}

// lobby
LobbyState Client::crear_partida(std::string& escenario) {
    protocol.send_create_game(escenario);
    return protocol.receive_confirmation();
}
LobbyState Client::join_game(const int& id) {
    protocol.send_join_game(id);
    return protocol.receive_confirmation();
}
LobbyState Client::request_game_list() {
    protocol.request_game_list();
    return protocol.receive_game_list();
}

LobbyState Client::request_scenarios_list() {
    protocol.request_scenarios_list();
    return protocol.receive_scenarios_list();
}

void Client::receive_scenario() { this->scenario = protocol.receive_scenario(); }

void Client::get_id_assigned_worm(const std::map<uint16_t, uint16_t>& distribution) {
    my_worms_id_vec.clear();

    for (auto worm: distribution) {
        if (worm.second == my_id)
            my_worms_id_vec.push_back(worm.first);
    }
}
void Client::assign_worms_color(const std::map<uint16_t, uint16_t>& distribution) {
    for (auto& map: distribution) {
        color_map[map.first] = SDL2pp::Color(map.second * 100 % 255, map.second * 100 % 255 + 255,
                                             map.second * 100 % 255, 255);
    }
}
void Client::start_joined_game() {
    // Que worm le corresponde a cada cliente (id_worm, id_client)
    distribution = protocol.receive_worms_distribution();
    assign_worms_color(distribution);
    get_id_assigned_worm(distribution);
}

void Client::start_game() {
    protocol.send_start_game();

    // Que worm le corresponde a cada cliente (id_worm, id_client)
    distribution = protocol.receive_worms_distribution();
    assign_worms_color(distribution);  // puede ir en world_view
    get_id_assigned_worm(distribution);
}

int Client::start() {
    sender->start();
    receiver->start();

    SDL2pp::SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);  //--->crear clase que maneje la vista
    SDL2pp::Mixer mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS,
                        4096);  // audio
    SDL2pp::SDLTTF sdl_ttf;
    // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
    SDL2pp::Window window("Worms", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                          SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    SoundController sound_controller(mixer);
    sound_controller.set_background_music();

    TextureController texture_controller(renderer);
    WeaponSelector weapon_selector(renderer);
    Hud hud(renderer, distribution);

    WorldView worldview(renderer, texture_controller, std::move(this->scenario), color_map,
                        weapon_selector, current_worm, my_worms_id_vec, sound_controller, &hud);

    bool running = true;
    auto start = high_resolution_clock::now();
    while (running) {

        update(worldview);

        if (std::find(my_worms_id_vec.begin(), my_worms_id_vec.end(), current_worm) !=
            my_worms_id_vec.end()) {
            running = handle_events(weapon_selector, sound_controller);
        }

        worldview.render();

        manage_frame_rate(start);
    }

    return SUCCESS;
}

void Client::manage_frame_rate(time_point<high_resolution_clock>& start) {
    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<duration<double>>(end - start).count();

    auto rest = FRAME_RATE - elapsed;
    if (rest < 0) {
        auto behind = -rest;
        auto lost = behind - fmod(behind, FRAME_RATE);
        start += duration_cast<high_resolution_clock::duration>(duration<double>(lost));
    } else {
        std::this_thread::sleep_for(std::chrono::duration<double>(rest));
    }

    start += duration_cast<high_resolution_clock::duration>(duration<double>(FRAME_RATE));
}

void Client::update(WorldView& worldview) {
    std::shared_ptr<EstadoJuego> estado;
    while (messages_received.try_pop(estado)) {
        std::map<uint16_t, std::unique_ptr<EntityInfo>>& updated_states =
                estado->get_updated_info();
        current_worm = estado->get_current_worm();

        worldview.update(updated_states, current_worm);
        messages_received.clear();
    }

    if (std::find(my_worms_id_vec.begin(), my_worms_id_vec.end(), current_worm) !=
        my_worms_id_vec.end()) {
        // TODO: medio cuestionable porque si hay mensajes q todavia no se mandaron se van a enviar
        // con el worm nuevo
        sender->set_current_worm(current_worm);
    }
}

bool Client::handle_events(WeaponSelector& weapon_selector, SoundController& sound_controller) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        try {
            auto c = event_handler.handle(event, weapon_selector, sound_controller);
            if (c != nullptr)
                messages_to_send.push(c);
        } catch (QuitGameClientInput& e) {
            return false;
        }
    }

    return true;
}
