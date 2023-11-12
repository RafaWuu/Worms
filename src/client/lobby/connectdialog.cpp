#include "connectdialog.h"
#include "ui_connectdialog.h"
#include "src/common/common_liberror.h"
#include <exception>

ConnectDialog::ConnectDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConnectDialog)
    , main_window(nullptr)
{
    ui->setupUi(this);
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
    
    if (main_window) delete main_window;
}

void ConnectDialog::closeEvent(QCloseEvent* event) { QApplication::exit(1); }

void ConnectDialog::on_connect_button_clicked() {
    std::string hostname = this->ui->hostnameEdit->text().toStdString();    
    std::string servicename = this->ui->servicenameEdit->text().toStdString();    

    try {
        std::shared_ptr<Client> client = std::make_shared<Client> (hostname, servicename);

        main_window = new MainWindow(client);
        main_window->show();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        close();
    }


    hide();
}
