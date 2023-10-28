#include "client_client.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../common/common_liberror.h"
#include "../common/common_socket.h"

#include "client_protocol.h"

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

#define SUCCESS 0
#define FAILURE 1

// Descomentar cuando este el server y se pueda conectar el socket

// Client::Client(const std::string& hostname, const std::string& servicename):
//         hostname(hostname), servicename(servicename), socket(hostname.c_str(), servicename.c_str()), 
//         protocol(std::move(socket)), sender(protocol, messages_to_send){

//     sender.start();
// }

Client::Client(const std::string& hostname, const std::string& servicename):
        hostname(hostname), servicename(servicename)
        {}


int Client::start() {
    std::string input;

    SDL sdl(SDL_INIT_VIDEO);

    // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
	Window window("Worms",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			640, 480,
			SDL_WINDOW_RESIZABLE);


    while (1) {

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
                    break;
                case SDLK_RIGHT:
                    std::cout << "RIGHT" << std::endl;
                    break;
                case SDLK_UP:
                    std::cout << "UP" << std::endl;
                    break;
                }
			}
		}
	}

    return SUCCESS;
}
