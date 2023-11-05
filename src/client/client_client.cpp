#include "client_client.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../common/common_liberror.h"
#include "../common/common_socket.h"
#include "commands/client_move.h"
#include "commands/client_stop_moving.h"

#include "client_protocol.h"

using namespace SDL2pp;

#define SUCCESS 0
#define FAILURE 1

Client::Client(const std::string& hostname, const std::string& servicename):
        hostname(hostname),
        servicename(servicename),
        socket(hostname.c_str(), servicename.c_str()),
        protocol(std::move(socket)),
        messages_to_send(1000) {

    sender = new ClientSender(protocol, messages_to_send);
    receiver = new ClientReceiver(protocol, messages_received);
}

Client::~Client() { kill(); }

void Client::kill() {
    messages_to_send.close();
    messages_received.close();

    protocol.kill();
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
LobbyState Client::join_game(int& id) {
    protocol.send_join_game(id);
    return protocol.receive_confirmation();
}
LobbyState Client::request_game_list() {
    protocol.request_game_list();
    return protocol.receive_game_list();
}

Scenario Client::receive_scenario() { 
    Scenario received_scenario = protocol.receive_scenario();
    this->scenario = std::make_unique<Scenario>(received_scenario);

    // Hace falta que lo devuelva? El Lobby despues lo manejara?
    return received_scenario; 
}

static uint8_t get_id_assigned_worm(std::map<uint8_t, uint16_t>& distribution) {
    // Cual es el id del cliente? Hardcodeo un 0 por ahora para probarlo
    uint16_t my_id = 0;
    uint8_t assigned_worm = -1;
    
    for (auto pair : distribution) {
        if (pair.second == my_id) {
            assigned_worm = pair.first;
            break;
        }
    }

    return assigned_worm;
}

void Client::start_game() { 
    protocol.send_start_game(); 

    // Que worm le corresponde a cada cliente (id_worm, id_client)
    std::map<uint8_t, uint16_t> distribution = protocol.receive_worms_distribution();

    uint8_t assigned_worm = get_id_assigned_worm(distribution);
    id_assigned_worm = assigned_worm;
}

int Client::start() {
    sender->start();
    receiver->start();
    int frame_delay = 1000 / 60;

    SDL sdl(SDL_INIT_VIDEO);  //--->crear clase que maneje la vista

    // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
    Window window("Worms", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                  SDL_WINDOW_RESIZABLE);
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    while (running) {
        uint32_t frame_start = SDL_GetTicks();

        running = handle_events();
        render(renderer);

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

bool Client::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    return false;
                case SDLK_LEFT:
                    std::cout << "LEFT" << std::endl;
                    move_left();
                    break;
                case SDLK_RIGHT:
                    std::cout << "RIGHT" << std::endl;
                    move_right();
                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    std::cout << "STOP LEFT" << std::endl;
                    stop_moving();
                    break;
                case SDLK_RIGHT:
                    std::cout << "STOP RIGHT" << std::endl;
                    stop_moving();
                    break;
            }
        }
    }

    return true;
}

void Client::render(Renderer& renderer) {
    // actualizar vista harcodeado
    SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.Get());

    std::shared_ptr<EstadoJuego> estado;
    if (messages_received.try_pop(estado)) {
        std::vector<Worm> worms = estado->get_worms();

        for (int i = 0; i < worms.size(); i++) {
            // Hardcodeado; cada worm deberia hacer su propio render
            // Hay que convertir las posiciones a pixeles
            float x = worms[i].get_pos_x();
            float y = worms[i].get_pos_y();
            std::cout << "x: " << x << " y: " << y << std::endl;
            SDL_Rect rect = {x, y, 100, 100};
            SDL_SetRenderDrawColor(renderer.Get(), 255, 0, 0, 255);
            SDL_RenderFillRect(renderer.Get(), &rect);
        }

        SDL_RenderPresent(renderer.Get());
    }
}

void Client::move_left() {
    std::shared_ptr<Move> move_command = std::make_shared<Move>(Move::Direction::Left);
    std::shared_ptr<Command> command = move_command;

    messages_to_send.push(command);
}

void Client::move_right() {
    std::shared_ptr<Move> move_command = std::make_shared<Move>(Move::Direction::Right);
    std::shared_ptr<Command> command = move_command;

    messages_to_send.push(command);
}

void Client::stop_moving() {
    std::shared_ptr<StopMoving> stop_moving = std::make_shared<StopMoving>();
    std::shared_ptr<Command> command = stop_moving;

    messages_to_send.push(command);
}
