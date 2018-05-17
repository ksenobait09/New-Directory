#ifndef NEWCONTACT_H
#define NEWCONTACT_H

#include <QDialog>

namespace Ui {
class NewContact;
}

class NewContact : public QDialog
{
    Q_OBJECT

public:
    explicit NewContact(QWidget *parent = 0);
    ~NewContact();

signals:
    void sendContact(QString name);

private slots:
    void on_addContact_clicked();

    void on_btnCancel_clicked();

private:
    Ui::NewContact *ui;
};

#endif // NEWCONTACT_H
