#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <string.h>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "commands/client_command.h"

#include "client_protocol.h"
#include "client_receiver.h"
#include "client_sender.h"
#include <memory>


class Client {
private:
    std::string hostname;
    std::string servicename;

    // Descomentar cuando este el server y se pueda conectar
    Socket socket;
    ClientProtocol protocol;

    ClientSender* sender;
    ClientReceiver* receiver;

    // Por ahora que sea un array de chars, despues cambiarlo a una clase propia
    Queue<std::shared_ptr<Command>> messages_to_send;
    Queue<std::shared_ptr<EstadoJuego>> messages_received;

public:
    Client(const std::string& hostname, const std::string& servicename);
    ~Client();
    Client(const Client& other) = delete;
    Client& operator=(const Client&) = delete;

    bool handle_events();
    void render(SDL2pp::Renderer& renderer);

    void kill();
    int start();

    void crear_partida(std::string& escenario);

    void move_left();
    void move_right();
    void stop_moving();
};

#endif
