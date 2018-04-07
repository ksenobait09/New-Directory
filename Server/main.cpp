#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    int nPort = 2323;
    server.run(nPort);

    return a.exec();
}
