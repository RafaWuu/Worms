#include "join_game_dialog.h"

#include "ui_join_game_dialog.h"



JoinGameDialog::JoinGameDialog(std::shared_ptr<Client> client, QWidget* parent):
        QDialog(parent), ui(new Ui::JoinGameDialog), client(client) {

    ui->setupUi(this);
    connect(ui->game_list, &QListView::clicked, this, &JoinGameDialog::onScenarioListItemClicked);

    model = new QStringListModel(this);

    this->ui->game_list->setModel(model);

    QStringList listaDeTexto;

    LobbyState l = client->request_game_list();

    for (const auto& p: l.game_list) {
        listaDeTexto.append(GameInfoView::toString(p));
    }
    model->setStringList(listaDeTexto);
}

void JoinGameDialog::onScenarioListItemClicked(const QModelIndex &index) {
    std::string selected_list_item = model->data(index, Qt::DisplayRole).toString().toStdString();

    unsigned first = selected_list_item.find(':');
    unsigned last = selected_list_item.find('-');
    std::string selected_scenario = selected_list_item.substr(first + 2, last - (first + 2)); 

    QString scenario_name = QString::fromStdString(selected_scenario);
    ui->id_partida->setText(scenario_name);
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
            LobbyState l = client->join_game(id);

            QString msg = QString("Esperando que la partida inicie...");
            ui->msg_validacion->setText(msg);

            QWidget::repaint();

            client->receive_scenario();
            client->start_joined_game();
            done(JOIN_GAME_SUCCESS);
        } catch (ErrorLobby& e) {
            QString msg = QString(e.what());
            ui->msg_validacion->setText(msg);
            std::cerr << e.what() << std::endl;
        }
    }
}
