#include "QMessageBox"
#include "QDebug"
#include "networking.h"
#include "mainwindow.h"
#include "settings.h"
#include "authorization.h"
#include "newcontact.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);   
    ui->txtInput->setFocus();

    Authorization *auth = new Authorization(this);
    auth->setModal(true);
    auth->setWindowTitle("Enter your nickname");
    auth->show();
//Подаем сигнал из окна авторизации и по слоту принимаем его в MainWindow в функции
    connect(auth, SIGNAL(setName(QString)), this, SLOT(recieveData(QString)));
    //Создаем список
    Model = new QStringListModel(this);
    Model->setStringList(List);
    ui->ListView->setModel(Model);
    ui->ListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//Получаем данные из окна авторизации(пока что никнейм пользователя)
void MainWindow::recieveData(QString name){
    userName = name;
    ui->lblUser->setText(userName);
}

void MainWindow::recieveContact(QString name)
{
//    int row = Model->rowCount(); // в числовую переменную заносим общее количество строк
//    Model->insertRows(row, 1); // добавляем строки, количеством 1 шт.
//    QModelIndex index = Model->index(row); // создаем ссылку на элемент модели
//    ui->ListView->setCurrentIndex(index); // передаем этот индекс ListView
//    ui->ListView->edit(index); // переводим курсор на указанную позицию для ожидания ввода данных
}

//Нажимаем на кнопку отправки сообщ.
void MainWindow::on_btnSend_clicked()
{
    emit enteredText(ui->txtInput->text()); //Подача сигнала для отправки через enter
    if(ui->txtInput->text() == "\0" || ui->txtInput->text() == NULL) //Нельзя отправить без текста
    {
        ui->txtInput->clear();
        ui->txtInput->setFocus();
    }  else {
        ui->txtChat->append(userName + ": " + ui->txtInput->text());
        ui->txtInput->clear();
        ui->txtInput->setFocus();
    }
}

//При исп. Enter делаем то же, что и при нажатии на кнопку
void MainWindow::on_txtInput_returnPressed()
{
    on_btnSend_clicked();
}

//Вызываем окно авторизации при Logout
void MainWindow::on_btnLogout_clicked()
{
    this->hide();

    Authorization *authWindow = new Authorization(this);
    authWindow->show();
    authWindow->setModal(true);
}

void MainWindow::on_btnSettings_clicked()
{
    Settings *settWind = new Settings(this);
    settWind->exec();
}

void MainWindow::on_btnNewChat_clicked()
{
//    NewContact *contact = new NewContact(this);
//    contact->exec();

    int row = Model->rowCount(); // в числовую переменную заносим общее количество строк
    Model->insertRows(row, 1); // добавляем строки, количеством 1 шт.
    QModelIndex index = Model->index(row); // создаем ссылку на элемент модели
    ui->ListView->setCurrentIndex(index); // передаем этот индекс ListView
    ui->ListView->edit(index); // переводим курсор на указанную позицию для ожидания ввода данных

}

void MainWindow::on_btnDeleteChat_clicked()
{
    Model->removeRows(ui->ListView->currentIndex().row(),1);
}
