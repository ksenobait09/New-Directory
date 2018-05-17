#include "newcontact.h"
#include "ui_newcontact.h"
#include "mainwindow.h"

NewContact::NewContact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewContact)
{
    ui->setupUi(this);
}

NewContact::~NewContact()

{
    delete ui;
}

void NewContact::on_addContact_clicked()
{
//    MainWindow *main = new MainWindow(this);
//    connect(this, SIGNAL(sendContact(QString)), main, SLOT(recieveContact(QString)));
//    emit sendContact(ui->txtUsername->text());
}

void NewContact::on_btnCancel_clicked()
{
    ui->txtUsername->clear();
    hide();
}
