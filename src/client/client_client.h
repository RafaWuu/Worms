#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <memory>
#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <string.h>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "commands/client_command.h"
#include "game/scenario.h"
#include "graphics/worldview.h"

#include "client_protocol.h"
#include "client_receiver.h"
#include "client_sender.h"
#include "commands/client_jump.h"


class Client {
private:
    std::string hostname;
    std::string servicename;

    Socket socket;
    ClientProtocol protocol;

    std::unique_ptr<Scenario> scenario;

    ClientSender* sender;
    ClientReceiver* receiver;

    uint8_t id_assigned_worm;
    uint16_t my_id;
    // Por ahora que sea un array de chars, despues cambiarlo a una clase propia
    Queue<std::shared_ptr<Command>> messages_to_send;
    Queue<std::shared_ptr<EstadoJuego>> messages_received;

    uint8_t get_id_assigned_worm(std::map<uint8_t, uint16_t>& distribution);
    void jump();

    void rollback();
public:
    Client(const std::string& hostname, const std::string& servicename);
    ~Client();
    Client(const Client& other) = delete;
    Client& operator=(const Client&) = delete;

    bool handle_events();
    void render(SDL2pp::Renderer& renderer);
    void update(WorldView& worldview);

    void kill();
    int start();

    LobbyState crear_partida(std::string& escenario);
    LobbyState join_game(int& id);
    LobbyState request_game_list();
    Scenario receive_scenario();
    void start_game();

    void move_left();
    void move_right();
    void stop_moving();

    void start_joined_game();



};

#endif
