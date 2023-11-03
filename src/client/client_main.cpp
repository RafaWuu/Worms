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
    QApplication app(argc, argv);
    MainWindow w;  // pasar ref de client y manejar desde lobby (crear/unir)
    w.show();
    app.exec();

    return client.start();
}
