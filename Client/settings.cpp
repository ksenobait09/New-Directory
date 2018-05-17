#include "settings.h"
#include "authorization.h"
#include "ui_settings.h"
#include "mainwindow.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_btnCancel_clicked()
{
    ui->txtNewPassword->clear();
    ui->txtOldPassword->clear();
    ui->txtNewUsername->clear();

    this->hide();
}

void Settings::on_btnSaveUsername_clicked()
{
    MainWindow *main = new MainWindow(this);
    emit setName(ui->txtNewUsername->text());
    connect(this, SIGNAL(setName(QString)), main, SLOT(recieveData(QString)));

    ui->txtNewUsername->clear();
    ui->lblIsSuccess->setText("Successfuly changed username!");

}

void Settings::on_btnSavePassword_clicked()
{
    Authorization *auth = new Authorization(this);

    if (ui->txtOldPassword->text() == auth->getPass() && ui->txtNewPassword->text() != ""){
        ui->txtNewPassword->clear();
        ui->txtOldPassword->clear();
        ui->lblIsSuccess->setText("OK!");
    } else {
        ui->txtNewPassword->clear();
        ui->txtOldPassword->clear();
        ui->lblIsSuccess->setText("Wrong old pass or new pass is empty!");
    }
}
