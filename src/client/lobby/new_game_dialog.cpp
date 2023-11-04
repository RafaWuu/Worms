#include "new_game_dialog.h"
#include "ui_new_game_dialog.h"
#include <iostream>
NewGameDialog::NewGameDialog(Client& client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGameDialog),
    client(client)
{
    ui->setupUi(this);
}

NewGameDialog::~NewGameDialog()
{
    delete ui;
}

void NewGameDialog::on_play_clicked()
{

    std::string escenario = this->ui->nom_escenario->toPlainText().toStdString();

    // label validacion
    if(escenario.empty()){
        QString msg = QString("entrada no valido");
        ui->msg_validacion->setText(msg);
        return;
    }
    try{
        LobbyState l = client.crear_partida(escenario);

        QString id = QString::number(l.id);
        QString msg = QString("Partida creada, el id es: %1").arg(id);
        ui->msg_validacion->setText(msg);

    }catch (ErrorLobby& e) {
        QString msg = QString(e.what());
        ui->msg_validacion->setText(msg);
        std::cerr<<e.what()<<std::endl;
    }
}
