#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QStringListModel>

#include <networking.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private:
    QString userName;

    Networking *net;
    QStringListModel *Model;
//    QListView *ListView;
    QStringList List;

    ~MainWindow();

public slots:
    void recieveData(QString name);
    void recieveContact(QString name);

private slots:
    void on_txtInput_returnPressed();

    void on_btnSend_clicked();

    void on_btnLogout_clicked();

    void on_btnNewChat_clicked();

    void on_btnSettings_clicked();

//    void showSelectedItem(QModelIndex);

    void on_btnDeleteChat_clicked();

signals:
    void enteredText(QString text);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
