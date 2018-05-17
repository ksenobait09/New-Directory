#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

signals:
    void setName(QString name);
    void setPassword(QString pass);

private slots:
    void on_btnCancel_clicked();

    void on_btnSaveUsername_clicked();

    void on_btnSavePassword_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
