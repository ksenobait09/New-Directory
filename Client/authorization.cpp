#include "authorization.h"
#include "ui_authorization.h"
#include "mainwindow.h"

QString Authorization::getPass()
{
    QString pass = Password;
    return pass;
}

QString Authorization::getName()
{
    QString username = Login;
    return username;
}

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
//    qDebug() << "Closing the connection to Database file on exist";
//    myDB.close();

//Авторизация пользователя
void Authorization::on_btnLogin_clicked()
{   //Валидация данных
    if (ui->txtUsername->text() == Login && ui->txtPassword->text() == Password){
        MainWindow *main = new MainWindow(this);
        main->show();

        connect(this, SIGNAL(setName(QString)), main, SLOT(recieveData(QString)));
        emit setName(ui->txtUsername->text());

        hide();
    } else {
        ui->lblResult->setText("Invalid Username or Password");
        ui->txtUsername->clear();
        ui->txtPassword->clear();
    }
}

// Подключение БД
//    myDB = QSqlDatabase::addDatabase("QSQLITE");

//    QString pathToDB = QDir::currentPath() + QString('messenger.sqlite');
//    myDB.setDatabaseName(pathToDB);

//    QFileInfo checkFile(pathToDB);

//    if (checkFile.isFile()) {
//        if (myDB.open()) {
//            ui->lblResult->setText("Connected to Database File");
//        }
//        else {
//            ui->lblResult->setText("Database File was not opened");
//        }
//    }
//    else {
//        ui->lblResult->setText("Database File does not exist");
//    }

//    Тянем данные из БД
//    QString Username, Password;
//    Username = ui->txtUsername->text();
//    Password = ui->txtPassword->text();

//    if (!myDB.isOpen()) {
//        qDebug() << "No connection to Database";
//        return;
//    }

//    QSqlQuery qry;

//    if (qry.exec("SELECT Username, Password, Role FROM Users WHERE Username=\'" + Username +
//                 "\' AND Password=\'" + Password + "\'"))
//    {
//        if (qry.next()) {
//            ui->lblResult->setText("[+] Valid Username and Password");
//            QString msg = "Username = " + qry.value(0).toString() + "\n" +
//                    "Password = " + qry.value(1).toString() + "\n";
//            QMessageBox::warning(this, "Login was successful", msg);
//        }
//        else {
//            ui->lblResult->setText("[-] Wrong Username or Password");
//        }
//    }
//    else {
//        ui->lblResult->setText("[-] Wrong query");
//    }
