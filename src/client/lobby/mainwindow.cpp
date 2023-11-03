#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , new_game (nullptr)
    , join_game (nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (new_game != nullptr) delete new_game;
    if (join_game != nullptr) delete join_game;
}
void MainWindow::closeEvent(QCloseEvent *event) {
    QApplication::exit(1);
}
void MainWindow::on_new_game_button_clicked()
{
    new_game = new NewGameDialog ();
    new_game ->show();
}

void MainWindow::on_join_game_button_clicked()
{
    join_game = new JoinGameDialog ();
    join_game -> show();
}
