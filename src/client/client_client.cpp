#include "client_client.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../common/common_liberror.h"
#include "../common/common_socket.h"
#include "commands/client_move.h"

#include "client_protocol.h"

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

#define SUCCESS 0
#define FAILURE 1

Client::Client(const std::string& hostname, const std::string& servicename):
        hostname(hostname), 
        servicename(servicename), 
        socket(hostname.c_str(), 
        servicename.c_str()), 
        protocol(std::move(socket)),
        messages_to_send(1000){

    sender = new ClientSender(protocol, messages_to_send);
    receiver = new ClientReceiver(protocol, messages_received);

    sender->start();
    receiver->start();
}

Client::~Client() {
    kill();
}

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

int Client::start() {
    int frame_delay = 1000 / 60;

    SDL sdl(SDL_INIT_VIDEO); //--->crear clase que maneje la vista
    
    // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
	Window window("Worms",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			640, 480,
			SDL_WINDOW_RESIZABLE);
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Rect rect {10,10,50,50};
    
    while (1) {
        uint32_t frame_start = SDL_GetTicks();
		// Event processing:
		// - If window is closed, or Q or Escape buttons are pressed,
		//   quit the application
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
            
			if (event.type == SDL_QUIT) {
				return 0;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: case SDLK_q:
					return 0;
                case SDLK_LEFT:
                    std::cout << "LEFT" << std::endl;

                    move_left();
                    break;
                case SDLK_RIGHT:
                    std::cout << "RIGHT" << std::endl;

                    move_right();
                    break;
                case SDLK_UP:
                    std::cout << "UP" << std::endl;
                    break;
                }
			}
		}
        // actualizar vista harcodeado
        EstadoJuego estado;
        if(messages_received.try_pop(estado)){
            if (estado.dir == 0x01) rect.x -=10;
            else if (estado.dir == 0x02) rect.x +=10;
        }
        SDL_SetRenderDrawColor(renderer.Get(), 0, 0, 0, 255);
        SDL_RenderClear(renderer.Get());

        SDL_SetRenderDrawColor(renderer.Get(), 255, 0, 0, 255);
        SDL_RenderFillRect(renderer.Get(), &rect);

        SDL_RenderPresent(renderer.Get());

        int frame_time = SDL_GetTicks()- frame_start;
        if (frame_delay > frame_time){
            SDL_Delay(frame_delay - frame_time);
        }
	}
    SDL_DestroyRenderer(renderer.Get());
    SDL_DestroyWindow(window.Get());
    SDL_Quit();
    return SUCCESS;
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
