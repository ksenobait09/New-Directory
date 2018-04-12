#ifndef DATABASE_H
#define DATABASE_H
#include <QObject>
#include <QSqlDatabase>

class Database : public QObject {
    Q_OBJECT
public:
    Database();
    ~Database();
private:
    QSqlDatabase db;
};
#endif // DATABASE_H
