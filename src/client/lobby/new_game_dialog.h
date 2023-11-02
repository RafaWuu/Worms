#ifndef NEW_GAME_DIALOG_H
#define NEW_GAME_DIALOG_H

#include <QDialog>

namespace Ui {
class NewGameDialog;
}

class NewGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameDialog(QWidget *parent = nullptr);
    ~NewGameDialog();

private slots:

    void on_play_clicked();

private:
    Ui::NewGameDialog *ui;
};

#endif // NEW_GAME_DIALOG_H
