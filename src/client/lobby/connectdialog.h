#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>

#include "./mainwindow.h"
#include "client_client.h"
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class ConnectDialog; }
QT_END_NAMESPACE

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    ConnectDialog(QWidget *parent = nullptr);
    ~ConnectDialog();

private slots:
    void on_connect_button_clicked();
    void closeEvent(QCloseEvent *event);

private:
    Ui::ConnectDialog *ui;
    MainWindow* main_window;
};
#endif // CONNECTDIALOG_H
