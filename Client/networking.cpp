#include "networking.h"
#include <QtNetwork>

Networking::Networking(QObject *parent)
    : QTcpSocket(parent)
{
   QTcpSocket *socket = new QTcpSocket;
   socket->connectToHost(host, 2323);
   if(!socket->waitForConnected()) {
       qDebug() << "error" << socket->errorString();
   } else {
       qDebug()<<"success";

       socketIn = new QTcpSocket;
       socketOut = new QTcpSocket;

       connect(socketIn, SIGNAL(readyRead()), this, SLOT(getData()));

       quint16 socketInPort = socketIn->localPort();
       quint16 socketOutPort = socketOut->localPort();
       QString cmd = "REGS";
       cmd += QString::number(socketInPort) + "&";
       cmd += QString::number(socketOutPort) + "&";
       cmd += user;
       socket->write(cmd.toUtf8());
       socket->close();
       delete socket;
   }
}

void Networking::getData() {
    QTcpSocket* socket = this;
    QString typePacket;
    QString message;

    message = socket->readAll();
    typePacket = message.mid(0,4);

    // manage packet types using first N bytes
    if(typePacket == "REGS") {
        quint16 port = message.mid(4, 4).toInt();
        // check if the line below errored due to non constant write to class member
        socketOut->connectToHost(host, port, WriteOnly);
        connect(socketOut, SIGNAL(readyRead()), this, SLOT(sendData()));
    }
}

void Networking::sendData() {

}
