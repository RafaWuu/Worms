#include "new_game_dialog.h"

#include <iostream>
#include <memory>
#include <string>

#include "game/scenario.h"

#include "ui_new_game_dialog.h"

NewGameDialog::NewGameDialog(std::shared_ptr<Client> client, QWidget* parent):
        QDialog(parent), ui(new Ui::NewGameDialog), client(client) {
    ui->setupUi(this);
    this->ui->nom_escenario->setText("basic");

    model = new QStringListModel(this);

    this->ui->scenario_list->setModel(model);

    LobbyState l = client->request_scenarios_list();

    QStringList listaDeTexto;

    for (const auto& p: l.scenarios_map) {
        QString scenario = QString::fromStdString(p.first);
        QString players = QString::number(p.second);

        auto s = QString("Escenario: %1  -  Tamaño: %2 worms").arg(scenario, players);

        listaDeTexto.append(s);
    }
    model->setStringList(listaDeTexto);
}

NewGameDialog::~NewGameDialog() { delete ui; }

void NewGameDialog::on_play_clicked() {
    std::string escenario = this->ui->nom_escenario->toPlainText().toStdString();

    // label validacion
    if (escenario.empty()) {
        QString msg = QString("entrada no valido");
        ui->msg_validacion->setText(msg);
        return;
    }
    try {
        LobbyState l = client->crear_partida(escenario);

        QString id = QString::number(l.id);
        QString msg = QString("Partida creada, el id es: %1").arg(id);
        ui->msg_validacion->setText(msg);

        client->receive_scenario();
        done(NEW_GAME_SUCCESS);
    } catch (ErrorLobby& e) {
        QString msg = QString(e.what());
        ui->msg_validacion->setText(msg);
        std::cerr << e.what() << std::endl;
    }
}
