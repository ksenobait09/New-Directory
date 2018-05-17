#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>
#include <QMessageBox>

namespace Ui {
class Authorization;
}

class Authorization : public QDialog
{
    Q_OBJECT

public:
    QString getPass();
    QString getName();
    explicit Authorization(QWidget *parent = 0);
    ~Authorization();

private slots:
    void on_btnLogin_clicked();

signals:
    void setName(QString name);

private:
    QString Password = "123";
    QString Login = "user";

    Ui::Authorization *ui;
//    QSqlDatabase myDB;
};

#endif // AUTHORIZATION_H
