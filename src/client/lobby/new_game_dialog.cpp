#include "new_game_dialog.h"

#include <iostream>

#include "ui_new_game_dialog.h"

NewGameDialog::NewGameDialog(Client& client, QWidget* parent): QDialog(parent), ui(new Ui::NewGameDialog), client(client) {
    ui->setupUi(this);
}

NewGameDialog::~NewGameDialog() { delete ui; }

void NewGameDialog::on_play_clicked() {
    // Creo que no hace falta ingresar un ID al crear una partida (???)
    // int id = this->ui->nom_escenario->toPlainText().toInt(&valid_id);
    
    std::string escenario = this->ui->nom_escenario->toPlainText().toStdString();
    
    if (escenario.empty()) {
        QString msg = QString("entrada no valido");
        ui->msg_validacion->setText(msg);
    } else {
        client.crear_partida(escenario);
        this->close();
        QApplication::exit(1);
    }
}
