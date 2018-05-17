#include "server.h"
#include <stdlib.h>

Server::Server() {

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
    QString message;
    quint16 inPort, outPort;
    QString data = socket->readAll();
    QString typePacket = data.left(4);

    if(typePacket == "REGS") {
        inPort = data.mid(4, 4).toInt();
        outPort = data.mid(8, 4).toInt();
        message = data.split('&')[6];

        QTcpServer *socketIn = new QTcpServer;
        QTcpSocket *socketOut = new QTcpSocket;

        socketOut->bind(QHostAddress::AnyIPv4);

        socketOut->connectToHost(socket->peerAddress().toString(), inPort);
        socketIn->listen(QHostAddress::AnyIPv4, outPort);

        inConnections[message] = socketIn;
        outConnections[message] = socketOut;

        connect(socketIn, SIGNAL(newConnection()), this, SLOT(clientInConnected()));
        connect(socketOut, SIGNAL(connected()), this, SLOT(clientOutConnected()));
    } else if (typePacket == "MSGP") {
        QStringList data = message.split("&");
        QString login = data[2];
        QString chatId = data[4];
        QString message = data[6];
        qDebug() << login << endl;
        qDebug() << chatId << endl;
        qDebug() << message << endl;
    }

    socket->disconnect();
}

void Server::clientInConnected() {
    QTcpSocket *socket = this->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(prepareData()));
}

void Server::clientOutConnected() {
    QTcpSocket *socket = this->nextPendingConnection();
}
