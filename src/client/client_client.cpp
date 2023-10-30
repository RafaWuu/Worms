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

Client::Client(const std::string& hostname, const std::string& servicename):
        hostname(hostname), servicename(servicename), socket(hostname.c_str(), servicename.c_str()), 
        protocol(std::move(socket)), sender(protocol, messages_to_send), 
        receiver(protocol, messages_received) {

    sender.start();
    receiver.start();
}

Client::~Client() {
    kill();
}

void Client::kill() {
    messages_to_send.close();
    messages_received.close();
    
    protocol.kill();
    sender.kill();
    receiver.kill();

    sender.join();
    receiver.join();
}

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
	}

    return SUCCESS;
}

void Client::move_left() {
    // hardcodeado
    std::vector<uint8_t> message = {0x01, 0x01};

    messages_to_send.push(message);
}

void Client::move_right() {
    std::vector<uint8_t> message = {0x01, 0x02};

    messages_to_send.push(message);
}
