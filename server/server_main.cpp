
#include <iostream>

#include "server_server.h"

#define ERROR_BADARGUMENTS 1

// Devuelve 0 si el cliente cierra la conexion luego de mandar un comando, 1 en caso de error
// o cierre prematuro
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: Expected " << argv[0] << " <puertoservicename>"
                  << " <escenarios>\n";
        return ERROR_BADARGUMENTS;
    }

    try {
        Server server(argv[1]);
        server.run();
    } catch (std::exception& e) {
        std::cerr << "Exception caught in main thread: '" << e.what() << "'" << std::endl;
    }
}
