#ifndef JOIN_GAME_DIALOG_H
#define JOIN_GAME_DIALOG_H

#include <QDialog>

namespace Ui {
class JoinGameDialog;
}

class JoinGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit JoinGameDialog(QWidget *parent = nullptr);
    ~JoinGameDialog();

private slots:

    void on_join_clicked();

private:
    Ui::JoinGameDialog *ui;
};

#endif // JOIN_GAME_DIALOG_H
