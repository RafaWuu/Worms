#include "mainwindow.h"
#include <QFontDatabase>
#include <QCloseEvent>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(std::shared_ptr<Client> client, QWidget* parent):
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        new_game(nullptr),
        join_game(nullptr),
        client(client) {
    ui->setupUi(this);
    ui->start_game->setEnabled(false);

    }

MainWindow::~MainWindow() {
    delete ui;
    if (new_game != nullptr)
        delete new_game;
    if (join_game != nullptr)
        delete join_game;
}
void MainWindow::closeEvent(QCloseEvent* event) { QApplication::exit(1); }
void MainWindow::on_new_game_button_clicked() {
    new_game = new NewGameDialog(this->client);
    if (new_game->exec() == NEW_GAME_SUCCESS) {
        ui->start_game->setEnabled(true);
        ui->join_game_button->setEnabled(false);
        ui->new_game_button->setEnabled(false);
    }
}

void MainWindow::on_join_game_button_clicked() {
    join_game = new JoinGameDialog(this->client);
    if (join_game->exec() == JOIN_GAME_SUCCESS) {
        close();
        QApplication::closeAllWindows();
        client->start();
    }
}

void MainWindow::on_start_game_clicked() {
    client->start_game();
    close();
    QApplication::closeAllWindows();
    client->start();
}
