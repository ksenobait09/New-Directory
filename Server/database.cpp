#include "database.h"
#include <QtSql>

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

Database::~Database() {
    db.close();
}
