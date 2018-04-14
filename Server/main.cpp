#include <QCoreApplication>
#include "server.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    int nPort = 2323;
    Database d;
    server.run(nPort);

    return a.exec();
}
