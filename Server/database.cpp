#include "database.h"
#include <QtSql>
#include <QDebug>


Database::Database() {
    db = QSqlDatabase::addDatabase("QMYSQL", "new-directory");
    db.setHostName("127.0.0.1");
    //db.setPort(2322);
    db.setDatabaseName("new-directory");
    db.setUserName("new-directory");
    db.setPassword("new-directory");
    bool ok = db.open();
    if (ok) {
        qInfo() << "Database connected";
    } else {
        qInfo() << "Database connection failed: ";
        qInfo() << db.lastError();
    }
}
Database& Database::Instance() {
    // согласно стандарту, этот код ленивый и потокобезопасный
    static Database database;
    return database;
}

bool Database::isRegistered(QString login) {
    return getUserIdByLogin(login) > -1;
}

// регистрация пользователя, если его нет в базе, если он есть, возвращает -1
int Database::userRegister(QString login, QString password) {
    if (isRegistered(login)) {
        return -1;
    }
    QSqlQuery query(this->db);
    query.prepare("INSERT INTO users (login, password) VALUES (:login, :password)");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    // возникла ошибка или нет строки
    if (!query.exec()) {
        return -1;
    }

    return query.lastInsertId().toInt();
}

// Логин пользователя, в случае успеха возвращает id, в случае неудачи -1
int Database::userLogin(QString login, QString password) {
    QSqlQuery query(this->db);
    query.prepare("SELECT id FROM users WHERE login = :login and password := password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    // возникла ошибка или нет строки
    if (!query.exec() || !query.next()) {
        return -1;
    }
    return query.value(0).toInt();
}

int Database::getUserIdByLogin(QString login) {
    QSqlQuery query(this->db);
    query.prepare("SELECT id FROM users WHERE login = :login");
    query.bindValue(":login", login);
    // возникла ошибка или нет строки
    if (!query.exec() || !query.next()) {
        return -1;
    }
    return query.value(0).toInt();
}

int Database::createChat(QString creatorLogin, QString otherLogin){

    int creatorId = getUserIdByLogin(creatorLogin);
    int otherId = getUserIdByLogin(otherLogin);
    if (creatorId < 0 || otherId < 0) {
        return -1;
    }
    QSqlDatabase::database().transaction();
    QSqlQuery query(this->db);

    // Создаем чат
    if (!query.exec("INSERT INTO chats VALUES()")){
        QSqlDatabase::database().rollback();
        return -1;
    }
    int chatId = query.lastInsertId().toInt();

    // Добавляем создателя чата
    query.prepare("INSERT INTO chats_users (chat_id, user_id, status) VALUES(:chatId, :creatorId, 'accepted')");
    query.bindValue(":chatId", chatId);
    query.bindValue(":creatorId", creatorId);
    if (!query.exec()){
        QSqlDatabase::database().rollback();
        return -1;
    }

    // Добавляем всех остальных(пока лишь приглашенного в диалог)
    query.prepare("INSERT INTO chats_users (chat_id, user_id, status) VALUES(:chatId, :otherId, 'pending')");
    query.bindValue(":chatId", chatId);
    query.bindValue(":otherId", otherId);
    if (!query.exec()){
        QSqlDatabase::database().rollback();
        return -1;
    }
    QSqlDatabase::database().commit();
    return chatId;
}

QVariantList Database::getChatsForUser(int userId) {
    QVariantList chats;
    if (userId < 0) {
        throw 0;
    }
    // Получаем чаты пользователя
    QSqlQuery query(this->db);
    query.prepare("SELECT c.id, c.name, c.is_dialog, cu.status FROM chats c"
                    "JOIN chats_users cu ON cu.chat_id = c.id"
                    "WHERE cu.user_id = :userId");
    query.bindValue(":userId", userId);
    if (!query.exec()) {
        throw 0;
    }
    while(query.next()) {
        QVariantMap chat;
        chat.insert("id", query.value(0));
        chat.insert("name", query.value(1));
        chat.insert("is_dialog", query.value(2));
        chat.insert("status", query.value(3));
        chats.append(chat);
    }

    // собираем данные для каждого чата
    foreach (QVariant _chat, chats) {
        QVariantMap chat = chat;
        QVariantList members = getChatMembers(chat["id"].toInt(), userId);
        chat.insert("members",members);


        // Если диалог , то имя чата - логин собеседника
        if(chat["is_dialog"].toBool()) {
            chat.insert("name", chat["members"].toList().constFirst());
        }
        QVariantList messages = getChatMessagesForUser(chat["id"].toInt(), userId);
        chat.insert("messages",messages);

    }
    return chats;

}

// Возвращает всех пользователей чата(За исключением пользователя с  excludeUserId)
QVariantList Database::getChatMembers(int chatId, int excludeUserId) {
    // собираем пользователей каждого чата
    QSqlQuery query(this->db);
    QString sql = "SELECT login FROM chats_users cu JOIN users u ON u.id=cu.user_id WHERE cu.chat_id=:chatId";
    if (excludeUserId >=0) {
        sql += "AND u.id != :excludeUserId";
    }
    query.prepare(sql);
    query.bindValue(":chatId", chatId);
    if (excludeUserId >=0) {
        query.bindValue(":excludeUserId", excludeUserId);
    }
    if (!query.exec()) {
        throw 0;
    }
    QVariantList members;
    while(query.next()) {
        members.append(query.value(0));
    }
    return members;
}

// Возвращает всех пользователей чата(За исключением пользователя с  excludeUserId)
QVariantList Database::getChatMessagesForUser(int chatId, int userId) {
    // грузим сообщения для каждого чата
    QSqlQuery query(this->db);
    query.prepare("SELECT text, from_user_id, is_message_read FROM messages m"
                    "JOIN message_read r ON r.user_id=:userId AND r.message_id=m.id"
                    "WHERE m.chat_id=:chat_id"
                    "ORDER by m.date DESC");
    query.bindValue(":chatId", chatId);
    query.bindValue(":currentUserId", userId);
    query.exec();
    if (!query.exec()) {
        throw 0;
    }
    QVariantList messages;
    while(query.next()) {
        QVariantMap message;
        message.insert("text", query.value(0));
        message.insert("from_user_id", query.value(1));
        message.insert("is_message_read", query.value(2));
        messages.append(message);
    }
    return messages;
}

Database::~Database() {
    QJsonDocument itemDoc = QJsonDocument::fromJson(answer);
    db.close();
}
