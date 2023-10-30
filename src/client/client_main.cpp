#include <iostream>
#include <sstream>
#include <string>

#include "client_client.h"

int main(int argc, char const* argv[]) {

    if (argc != 3)
    {
        std::cerr << "Ingrese hostname y servicename" << std::endl;
        return 1;
    }
    
    Client client(argv[1], argv[2]);

    return client.start();
}
