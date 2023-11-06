#include "join_game_dialog.h"

#include "ui_join_game_dialog.h"

JoinGameDialog::JoinGameDialog(Client& client, QWidget* parent):
        QDialog(parent), ui(new Ui::JoinGameDialog), client(client) {
    ui->setupUi(this);
    /*
        model = new QStringListModel(this);

        this->ui->game_list->setModel(model);

        QStringList listaDeTexto;

        LobbyState l = client.request_game_list();

        for (const auto& p : l.game_list) {
            QString id = QString::number(p.first);
            QString scenario = QString::fromStdString(p.second);
            listaDeTexto.append(QString("%1  |  %2").arg(id).arg(scenario));
        }
            model->setStringList(listaDeTexto);
    */
}


JoinGameDialog::~JoinGameDialog() { delete ui; }

void JoinGameDialog::on_join_clicked() {
    bool valid_id;
    int id = this->ui->id_partida->toPlainText().toInt(&valid_id);

    // label validacion
    if (!valid_id) {
        QString msg = QString("id no valido");
        ui->msg_validacion->setText(msg);
    } else {
        try {
            LobbyState l = client.join_game(id);

            QString id = QString::number(l.id);
            QString msg = QString("Se ha unido a partida %1").arg(id);
            ui->msg_validacion->setText(msg);

            // recv_scenario() tiene que devolver el scenario?
            // o lo maneja el cliente directamente todo
            Scenario scenario = client.receive_scenario();
            QApplication::exit();
            client.start_joined_game();

        } catch (ErrorLobby& e) {
            QString msg = QString(e.what());
            ui->msg_validacion->setText(msg);
            std::cerr << e.what() << std::endl;
        }
    }
}
