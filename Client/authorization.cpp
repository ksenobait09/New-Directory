#include "authorization.h"
#include "ui_authorization.h"

Authorization::Authorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authorization)
{
    ui->setupUi(this);
}

Authorization::~Authorization()
{
    delete ui;
}

//Кнопка авторизации пользваотеля с никнеймом
void Authorization::on_btnLogin_clicked()
{
    emit setName(ui->txtUsername->text());
    this->hide();
}
//Кнопка отмены авторизации
void Authorization::on_btnCancel_clicked() {hide();}
