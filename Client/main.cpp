#include "mainwindow.h"
#include <QApplication>
//#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    QLabel *label = new QLabel("Привет");
//    label->resize(250, 300);
//    label->show();


    return a.exec();
}
