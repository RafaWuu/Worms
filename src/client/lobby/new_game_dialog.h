#ifndef NEW_GAME_DIALOG_H
#define NEW_GAME_DIALOG_H

#include <QDialog>

#include "client_client.h"

namespace Ui {
class NewGameDialog;
}

class NewGameDialog: public QDialog {
    Q_OBJECT

public:
    NewGameDialog(Client& client, QWidget* parent = nullptr);
    ~NewGameDialog();

private slots:

    void on_play_clicked();

private:
    Ui::NewGameDialog* ui;
    Client& client;
};

#endif  // NEW_GAME_DIALOG_H
