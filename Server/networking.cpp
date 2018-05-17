#include "networking.h"
#include <QtNetwork>

Networking::Networking(QObject *parent)
    : QTcpSocket(parent)
{
   QObject::connect(socket, SIGNAL(connected()), this, SLOT(readyRead()));
   QObject::connect(socket, SIGNAL(readChannelFinished()), this, SLOT(sendToServer()));
   QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
               this, SLOT(displayError(QAbstractSocket::SocketError)));

   socket->connectToHost("127.0.0.1", 2323);
   if(!socket->waitForConnected()) {
       qDebug()<<"error"<<socket->errorString();
   } else {
       qDebug()<<"success";
   }
}

size_t Networking::readyRead() {
    if(!socket->waitForReadyRead()) {
        qDebug()<<"error"<<socket->errorString();
    }
    QByteArray byteArray;
    while(socket->bytesAvailable() > 0) {
        byteArray = socket->readAll();
    }

    return *byteArray;
}

void Networking::sendToServer(QString message) {
    QByteArray byteArray = message.toUtf8();
    socket->write(byteArray);
    if(!socket->waitForBytesWritten()) {
        qDebug()<<"error"<<socket->errorString();
    }
}
