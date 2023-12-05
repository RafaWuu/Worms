#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <chrono>
#include <map>
#include <memory>
#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <string.h>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "commands/client_command.h"
#include "commands/client_jump.h"
#include "game/scenario.h"
#include "graphics/hud.h"

#include "client_event_handler.h"
#include "client_protocol.h"
#include "client_receiver.h"
#include "client_sender.h"

class WorldView;

class Client {
private:
    Socket socket;
    SocketBaseProtocol bp;
    ClientProtocol protocol;

    std::unique_ptr<Scenario> scenario;

    std::unique_ptr<ClientSender> sender;
    std::unique_ptr<ClientReceiver> receiver;

    std::vector<uint16_t> my_worms_id_vec;
    uint16_t my_id;
    uint16_t current_worm;
    std::map<uint16_t, uint16_t> distribution;

    std::map<uint16_t, SDL2pp::Color> color_map;  // sdl color o 3 ints(r,g,b)
    // Por ahora que sea un array de chars, despues cambiarlo a una clase propia
    Queue<std::shared_ptr<Command>> messages_to_send;
    Queue<std::shared_ptr<EstadoJuego>> messages_received;

    void get_id_assigned_worm(const std::map<uint16_t, uint16_t>& distribution);
    void assign_worms_color(const std::map<uint16_t, uint16_t>& distribution);

    void manage_frame_rate(std::chrono::time_point<std::chrono::high_resolution_clock>& start);

public:
    Client(const std::string& hostname, const std::string& servicename);
    ~Client();
    Client(const Client& other) = delete;
    Client& operator=(const Client&) = delete;

    bool handle_events(WeaponSelector& weapon_selector, SoundController& sound_controller);
    void update(WorldView& worldview, bool& running);

    void kill();
    int start();

    LobbyState crear_partida(std::string& escenario);
    LobbyState join_game(const int& id);
    LobbyState request_game_list();
    void receive_scenario();
    void start_game();

    void handle_game_over(WorldView& worldview, std::shared_ptr<EstadoJuego> estado);


    void start_joined_game();


    EventHandler event_handler;

    LobbyState request_scenarios_list();
};

#endif
