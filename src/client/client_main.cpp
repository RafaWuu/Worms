#include <QApplication>
#include <iostream>
#include <sstream>
#include <string>

#include "lobby/mainwindow.h"

#include "client_client.h"
int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cerr << "Ingrese hostname y servicename" << std::endl;
        return 1;
    }

    Client client(argv[1], argv[2]);
    // lobby QT
    try
    {   
        QApplication app(argc, argv);
        MainWindow w(client);
        w.show();
        if(app.exec() == 1) return 1;
    }
    catch(const std::exception& e)
    {   //debug
        std::cerr << e.what() << std::endl;
    }
    
    return client.start();
}
