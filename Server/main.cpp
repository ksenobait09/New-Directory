#include <QCoreApplication>
#include "server.h"
#include "database.h"
#include "user.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    int nPort = 2323;
    server.run(nPort);
    // Тест базовых методов бизнес логики
    User user("test", "test");
    User user2("test2", "test2");
    user.addContact("test2");
    return a.exec();
}
