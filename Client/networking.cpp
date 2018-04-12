#include "networking.h"
#include <QtNetwork>

Networking::Networking(QObject *parent)
    : QTcpSocket(parent)
{
   socket = new QTcpSocket;

   //QObject::connect(socket, SIGNAL(connected()), this, SLOT(readyRead()));
   QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(readHandler()));
//   QObject::connect(socket, SIGNAL(readChannelFinished()), this, SLOT(sendToServer()));
//   QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
//               this, SLOT(displayError(QAbstractSocket::SocketError)));

   socket->bind(2324);
   socket->connectToHost("127.0.0.1", 2323);
   if(!socket->waitForConnected()) {
       qDebug()<<"error"<<socket->errorString();
   } else { qDebug()<<"success"; }

}

void Networking::readHandler() {
    qDebug() << "read handler";
    qDebug()<<socket->readAll();
}


void Networking::readyRead() {
    if(!socket->waitForReadyRead(500)) {
        qDebug()<<"error"<<socket->errorString();
    }
    QByteArray byteArray;
    byteArray = socket->readAll();
    qDebug() << byteArray;
}

void Networking::broadcastData(QString message) {
    QByteArray byteArray = message.toUtf8();
    socket->write(byteArray);
    if(!socket->waitForBytesWritten(1000)) {
        qDebug()<<"error"<<socket->errorString();
    } else {
        qDebug()<<"successfully sent";
    }
}
