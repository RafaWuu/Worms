#include <QApplication>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include "lobby/mainwindow.h"
#include "lobby/connectdialog.h"
#include "../common/common_liberror.h"

#include "client_client.h"

void connect_to_server(ConnectDialog& c, std::shared_ptr<Client>& client, std::unique_ptr<MainWindow>& w);

int main(int argc, char* argv[]) {
    // lobby QT
    try
    {   
        QApplication app(argc, argv);
        ConnectDialog c;

        c.show();

        app.exec();
    }
    catch(const std::exception& e)
    {   //debug
        std::cerr << e.what() << std::endl;
        return 1;
    }    
}
