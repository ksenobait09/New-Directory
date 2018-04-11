#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->txtInput->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSend_clicked()
{
    emit enteredText(ui->txtInput->text());
    ui->txtChat->append("Username: " + ui->txtInput->text());
    ui->txtInput->clear();
    ui->txtInput->setFocus();
}

void MainWindow::on_txtInput_returnPressed()
{
    on_btnSend_clicked();
}

//Писал для тестов, может пригодится
//void MainWindow::on_pushButton_clicked()
//{
//    ui->label->setText("Button pressed");
//}

//void MainWindow::on_SendButton_clicked()
//{
//    QMessageBox::StandardButton reply = QMessageBox::question(this, "Title",
//                                                              "Close App?",
//                                                              QMessageBox::Yes | QMessageBox::No);

//    if(reply == QMessageBox::Yes){
//        QApplication::quit();
//    } else {
//        qDebug() << "No button pressed";
//    }
//}
