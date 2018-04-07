#include "server.h"
#include "serverthread.h"

#include <stdlib.h>

Server::Server(QObject *parent)
    : QTcpServer(parent)
{

}

// Перегрузка обработки входящих соединений:
// Создаем ещё один поток
//
void Server::incomingConnection(qintptr socketDescriptor)
{
    ServerThread *thread = new ServerThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

// Запуск сервера
void Server::run(int nPort) {
    if (!this->listen(QHostAddress::Any, nPort)) {
        qInfo()<<"Server Error";
        qInfo()<<"Unable to start the server:";
        qInfo()<<this->errorString();
        this->close();
        return;
    }
    qInfo()<<"Server succesful started";
}
