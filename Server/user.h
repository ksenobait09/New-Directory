#ifndef USER_H
#define USER_H

#include <QObject>
#include "database.h"

class User : public QObject
{
    Q_OBJECT
public:
    QString login;
    QString password;
    int id;
    Database& db = Database::Instance();

    User(QString login, QString password);

    int addContact(QString login);

    bool sendMessage(int chatId, QString message);

    static QString hashPassword(QString password);
    QString getChatsJSON();


signals:


public slots:
private:


};

#endif // USER_H
