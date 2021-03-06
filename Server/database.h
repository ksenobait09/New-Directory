#ifndef DATABASE_H
#define DATABASE_H
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

// Singletone and proxy patterns
class Database {
public:
    static Database& Instance();

    bool isRegistered(QString login);

    int userRegister(QString Login, QString Password);

    int userLogin(QString Login, QString Password);

    int createChat(QString creatorLogin, QString otherLogin);

    int getUserIdByLogin(QString login);

    QVariantList getChatsForUser(int userId);

    QVariantList getChatMessagesForUser(int chatId, int userId);

    QVariantList getChatMembers(int chatId, int excludeUserId = -1);

protected:

private:
    ~Database();
    Database(Database const&) = delete;
    Database();
    Database& operator= (Database const&) = delete;
    QSqlDatabase db;
};
#endif // DATABASE_H
