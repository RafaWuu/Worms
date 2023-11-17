#include "client_client.h"

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../common/common_liberror.h"
#include "../common/common_socket.h"
#include "commands/client_jump.h"
#include "commands/client_move.h"
#include "commands/client_rollback.h"
#include "commands/client_stop_moving.h"
#include "graphics/worldview.h"

#include "client_protocol.h"


#define SUCCESS 0
#define FAILURE 1

Client::Client(const std::string& hostname, const std::string& servicename):
        hostname(hostname),
        servicename(servicename),
        socket(hostname.c_str(), servicename.c_str()),
        bp(std::move(socket)),
        protocol(bp),
        messages_to_send(1000),
        messages_received(1000),
        event_handler() {

    sender = new ClientSender(protocol, messages_to_send);
    receiver = new ClientReceiver(protocol, messages_received);

    protocol.get_my_id(my_id);  // Reubicar
    id_assigned_worm = 0;
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

    delete sender;
    delete receiver;
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

void Client::receive_scenario() { this->scenario = protocol.receive_scenario(); }

uint16_t Client::get_id_assigned_worm(const std::map<uint16_t, uint16_t>& distribution) {
    // Cual es el id del cliente? Hardcodeo un 0 por ahora para probarlo
    uint16_t assigned_worm = -1;
    uint16_t id = my_id;

    auto it = std::find_if(distribution.begin(), distribution.end(),
                           [id](const auto& p) { return p.second == id; });

    return it->first;
}

void Client::start_joined_game() {
    // Que worm le corresponde a cada cliente (id_worm, id_client)
    std::map<uint16_t, uint16_t> distribution = protocol.receive_worms_distribution();

    uint16_t assigned_worm = get_id_assigned_worm(distribution);
    id_assigned_worm = assigned_worm;
}

void Client::start_game() {
    protocol.send_start_game();

    // Que worm le corresponde a cada cliente (id_worm, id_client)
    std::map<uint16_t, uint16_t> distribution = protocol.receive_worms_distribution();

    uint16_t assigned_worm = get_id_assigned_worm(distribution);
    id_assigned_worm = assigned_worm;
}

int Client::start() {
    protocol.set_worm_id(id_assigned_worm);  // Reubicar

    sender->start();
    receiver->start();
    int frame_delay = 1000 / 60;

    SDL2pp::SDL sdl(SDL_INIT_VIDEO);  //--->crear clase que maneje la vista

    // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
    SDL2pp::Window window("Worms", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                          SDL_WINDOW_RESIZABLE);
    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
    // renderer.SetLogicalSize(1920,1080);

    TextureController texture_controller(renderer);
    WorldView worldview(texture_controller, std::move(this->scenario));

    bool running = true;
    while (running) {
        uint32_t frame_start = SDL_GetTicks();

        running = handle_events();
        update(worldview);
        worldview.render(renderer);

        int frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time) {
            SDL_Delay(frame_delay - frame_time);
        }
    }

    SDL_DestroyRenderer(renderer.Get());
    SDL_DestroyWindow(window.Get());
    SDL_Quit();
    return SUCCESS;
}

void Client::update(WorldView& worldview) {
    std::shared_ptr<EstadoJuego> estado;
    if (messages_received.try_pop(estado)) {
        std::map<uint16_t, std::unique_ptr<EntityInfo>>& updated_states =
                estado->get_updated_info();
        worldview.update(updated_states);
    }
}

bool Client::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        try {
            auto c = event_handler.handle(event);
            if (c != nullptr)
                messages_to_send.push(c);
        } catch (QuitGameClientInput& e) {
            return false;
        }
    }

    return true;
}
