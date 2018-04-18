#include "QMessageBox"
#include "QDebug"
#include <networking.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    userName = "NoName";
//    ui->setupUi(this);
    ui->txtInput->setFocus();

    Authorization *auth = new Authorization(this);
    auth->setModal(true);
    auth->setWindowTitle("Enter your nickname");
    auth->show();
//Подаем сигнал из окна авторизации и по слоту принимаем его в MainWindow в функции
    connect(auth, SIGNAL(setName(QString)), this, SLOT(recieveData(QString)));
    net = new Networking();
}

MainWindow::~MainWindow()
{
    delete net;
    delete ui;
}
//Получаем данные из окна авторизации(пока что никнейм пользователя)
void MainWindow::recieveData(QString name){
    userName = name;
}

//Нажимаем на кнопку отправки сообщ.
void MainWindow::on_btnSend_clicked()
{
    emit enteredText(ui->txtInput->text()); //Подача сигнала для отправки через enter
    if(ui->txtInput->text() == "\0" || ui->txtInput->text() == " ") //Нельзя отправить без текста
    {
        ui->txtInput->clear();
        ui->txtInput->setFocus();
    }  else {
        ui->txtChat->append(userName + ": " + ui->txtInput->text());
        net->broadcastData(ui->txtInput->text());
        ui->txtInput->clear();
        ui->txtInput->setFocus();
    }
}

//При исп. Enter делаем то же, что и при нажатии на кнопку
void MainWindow::on_txtInput_returnPressed()
{
    on_btnSend_clicked();
}

//Вызываем окно авторизации при нажатии на кнопку
void MainWindow::on_btnAuth_clicked()
{
    Authorization authWindow;
    authWindow.setModal(true);
    authWindow.exec();
}
