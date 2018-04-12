#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>
#include <QString>

namespace Ui {
class Authorization;
}

class Authorization : public QDialog
{
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = 0);
    ~Authorization();

private slots:
    void on_btnCancel_clicked();
    void on_btnLogin_clicked();

signals:
    void setName(QString name);

private:
    Ui::Authorization *ui;
};

#endif // AUTHORIZATION_H
