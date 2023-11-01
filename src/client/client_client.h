#include <string>

#include <string.h>

#include "../common/common_socket.h"
#include "../common/common_queue.h"

#include "client_receiver.h"
#include "client_sender.h"
#include "client_protocol.h"
#include "commands/client_command.h"

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
    Queue<EstadoJuego> messages_received;

public:
    Client(const std::string& hostname, const std::string& servicename);
    ~Client();
    
    void kill();

    int start();
    void move_left();
    void move_right();
};
