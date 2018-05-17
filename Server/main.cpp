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
    User user("test", "test");
    return a.exec();
}
