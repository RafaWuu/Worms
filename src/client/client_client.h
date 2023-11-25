#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <map>
#include <memory>
#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <string.h>
#include <chrono>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "commands/client_command.h"
#include "commands/client_jump.h"
#include "game/scenario.h"
#include "graphics/worldview.h"

#include "client_event_handler.h"
#include "client_protocol.h"
#include "client_receiver.h"
#include "client_sender.h"


class Client {
private:
    // remover estos atributos si solo se usan para construir el socket
    std::string hostname;
    std::string servicename;

    Socket socket;
    SocketBaseProtocol bp;
    ClientProtocol protocol;

    std::unique_ptr<Scenario> scenario;

    ClientSender* sender;
    ClientReceiver* receiver;

    uint8_t id_assigned_worm;
    uint16_t my_id;
    std::map<uint16_t, SDL2pp::Color> color_map;  // sdl color o 3 ints(r,g,b)
    // Por ahora que sea un array de chars, despues cambiarlo a una clase propia
    Queue<std::shared_ptr<Command>> messages_to_send;
    Queue<std::shared_ptr<EstadoJuego>> messages_received;

    uint16_t get_id_assigned_worm(const std::map<uint16_t, uint16_t>& distribution);
    void assign_worms_color(const std::map<uint16_t, uint16_t>& distribution);

    void manage_frame_rate(std::chrono::time_point<std::chrono::high_resolution_clock>& start);

public:
    Client(const std::string& hostname, const std::string& servicename);
    ~Client();
    Client(const Client& other) = delete;
    Client& operator=(const Client&) = delete;

    bool handle_events(WeaponSelector& weapon_selector);
    void update(WorldView& worldview);

    void kill();
    int start();

    LobbyState crear_partida(std::string& escenario);
    LobbyState join_game(const int& id);
    LobbyState request_game_list();
    void receive_scenario();
    void start_game();


    void start_joined_game();


    EventHandler event_handler;
};

#endif
