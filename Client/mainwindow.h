#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "authorization.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString userName;

    ~MainWindow();

public slots:
    void recieveData(QString name);

private slots:
    void on_btnAuth_clicked();
    void on_txtInput_returnPressed();
    void on_btnSend_clicked();

signals:
    void enteredText(QString text);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
