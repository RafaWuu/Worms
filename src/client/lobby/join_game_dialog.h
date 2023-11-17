#ifndef JOIN_GAME_DIALOG_H
#define JOIN_GAME_DIALOG_H

#include <QDialog>
#include <QStringListModel>
#include <memory>

#include "../client_client.h"

#include "gameinfo_view.h"

namespace Ui {
class JoinGameDialog;
}

class JoinGameDialog: public QDialog {
    Q_OBJECT

public:
    explicit JoinGameDialog(std::shared_ptr<Client> client, QWidget* parent = nullptr);
    ~JoinGameDialog();

private slots:

    void on_join_clicked();

private:
    Ui::JoinGameDialog* ui;
    std::shared_ptr<Client> client;
    QStringListModel* model;
};

#endif  // JOIN_GAME_DIALOG_H
