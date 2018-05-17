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

        QTcpServer *socketIn = new QTcpServer;
        QTcpSocket *socketOut = new QTcpSocket;

        socketOut->connectToHost(socket->peerAddress().toString(), outPort);
        socketIn->listen(QHostAddress::AnyIPv4, inPort);

        inConnections[params] = socketIn;
        outConnections[params] = socketOut;

        connect(socketIn, SIGNAL(newConnection()), this, SLOT(clientInConnected()));
        connect(socketOut, SIGNAL(connected()), this, SLOT(clientOutConnected()));
    }

    socket->close();
}

void Server::clientInConnected() {
    QTcpSocket *socket = this->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(prepareData()));
}

void Server::clientOutConnected() {
    QTcpSocket *socket = this->nextPendingConnection();
    // socket should be connected to writing module
}
