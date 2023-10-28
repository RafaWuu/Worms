#include <iostream>
#include <sstream>
#include <string>

#include "client_client.h"

int main(int argc, char const* argv[]) {

    // Cuando este el server el cliente se inicializa con el hostname y el servicename
    // Client client(argv[1], argv[2]);

    Client client("", "");
    return client.start();
}
