#ifndef USER_H
#define USER_H

#include <QObject>
#include "database.h"
#include "server.h"

class User : public QObject
{
    Q_OBJECT
public:
    QString login;
    QString password;
    int id;
    Database& db = Database::Instance();
    Server& server = Server::Instance();

    User(QString login, QString password);

    int addContact(QString login);

    bool sendMessage(int chatId, QString message);

    static QString hashPassword(QString password);
    QString getChatsJSON();


signals:


public slots:
private:
    // store users vs chat channels
    QHash<QString, QString> chatChannels;

};

#endif // USER_H
