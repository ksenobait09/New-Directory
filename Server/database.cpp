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
    query.prepare("SELECT id FROM users WHERE login = :login and password := password");
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



Database::~Database() {
    db.close();
}
