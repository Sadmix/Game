#include "connectwindow.h"
#include "ui_connectwindow.h"

ConnectWindow::ConnectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectWindow)
{
    ui->setupUi(this);
}

ConnectWindow::~ConnectWindow()
{
    delete ui;
}

void ConnectWindow::on_cancelBtn_clicked()
{
    emit closeApp();
    close();
}

void ConnectWindow::on_pushButton_2_clicked()
{
    emit setName(name);
    emit connectToHost(ip);
}

void ConnectWindow::on_ipEdit_textEdited(const QString &arg1)
{
    ip = arg1;

}

void ConnectWindow::showMessage(){
    QMessageBox::information(this, "Error", "Failed to connect");
}

void ConnectWindow::on_nameEdit_textChanged(const QString &arg1)
{
    name = arg1;
}

