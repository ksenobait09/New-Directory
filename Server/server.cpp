#include "server.h"
#include <stdlib.h>

Server::Server(QObject *parent)
    : QTcpServer(parent)
{

}

void Server::run(int nPort) {
    connect(this, SIGNAL(newConnection()), this, SLOT(onConnection()));
    if (!this->listen(QHostAddress::AnyIPv4, nPort)) {
        qInfo()<<"Server Error";
        qInfo()<<"Unable to start the server:";
        qInfo()<<this->errorString();
        this->close();
        return;
    }
    qInfo()<<"Server succesful started";
}

void Server::onConnection()
{
    QTcpSocket *socket = this->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Server::readyRead() {
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QString params;
    quint16 inPort, outPort;
    QByteArray typePacket = socket->read(4);
    if(typePacket == "REGS") {
        inPort = socket->read(5).toInt();
        outPort = socket->read(5).toInt();
        params = socket->read(32);

        QTcpSocket *socketIn = new QTcpSocket;
        QTcpSocket *socketOut = new QTcpSocket;

        socketIn->connectToHost(socket->peerAddress().toString(),inPort);
        socketOut->connectToHost(socket->peerAddress().toString(), outPort);

        inConnections[params] = socketIn;
        outConnections[params] = socketOut;
    }

    socket->close();
}
