#include "join_game_dialog.h"
#include "ui_join_game_dialog.h"

JoinGameDialog::JoinGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinGameDialog)
{
    ui->setupUi(this);
}

JoinGameDialog::~JoinGameDialog()
{
    delete ui;
}

void JoinGameDialog::on_join_clicked()
{
    bool valid_id;
    int id = this->ui->id_partida->toPlainText().toInt(&valid_id);

    // label validacion
    if (!valid_id){
        QString msg = QString("id no valido");
        ui->msg_validacion->setText(msg);
    }
    else{
        // cliente.unirse_a_partida(id);
        this->close();
        QApplication::exit(1);
    }
}

