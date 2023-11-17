#ifndef NEW_GAME_DIALOG_H
#define NEW_GAME_DIALOG_H

#include <QDialog>
#include <memory>

#include "../client_client.h"

namespace Ui {
class NewGameDialog;
}

class NewGameDialog: public QDialog {
    Q_OBJECT

public:
    explicit NewGameDialog(std::shared_ptr<Client> client, QWidget* parent = nullptr);
    ~NewGameDialog();

private slots:

    void on_play_clicked();

private:
    Ui::NewGameDialog* ui;
    std::shared_ptr<Client> client;
};

#endif  // NEW_GAME_DIALOG_H
