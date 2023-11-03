#include "new_game_dialog.h"

#include <iostream>

#include "ui_new_game_dialog.h"
NewGameDialog::NewGameDialog(QWidget* parent): QDialog(parent), ui(new Ui::NewGameDialog) {
    ui->setupUi(this);
}

NewGameDialog::~NewGameDialog() { delete ui; }

void NewGameDialog::on_play_clicked() {
    bool valid_id;
    bool valid_escenario;

    int escenario = this->ui->nom_escenario->toPlainText().toInt(&valid_escenario);
    int id = this->ui->nom_escenario->toPlainText().toInt(&valid_id);
    // label validacion
    if (!valid_escenario || !valid_id) {
        QString msg = QString("entrada no valido");
        ui->msg_validacion->setText(msg);
    } else {
        // cliente.crear_partida(id, escenario);
        this->close();
        QApplication::exit(1);
    }
}
