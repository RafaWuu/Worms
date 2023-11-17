#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

#include "../client_client.h"

#include "join_game_dialog.h"
#include "new_game_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(std::shared_ptr<Client>, QWidget* parent = nullptr);
    ~MainWindow();

private slots:

    void on_new_game_button_clicked();

    void on_join_game_button_clicked();

    void closeEvent(QCloseEvent* event);

    void on_start_game_clicked();

private:
    Ui::MainWindow* ui;
    NewGameDialog* new_game;
    JoinGameDialog* join_game;
    std::shared_ptr<Client> client;
};
#endif  // MAINWINDOW_H
