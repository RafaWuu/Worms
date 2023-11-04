#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "new_game_dialog.h"
#include "join_game_dialog.h"
#include "../client_client.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Client& client, QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_new_game_button_clicked();

    void on_join_game_button_clicked();

    void closeEvent(QCloseEvent *event);

    void on_start_game_clicked();

private:
    Ui::MainWindow *ui;
    NewGameDialog* new_game;
    JoinGameDialog* join_game;
    Client& client;
};
#endif // MAINWINDOW_H
