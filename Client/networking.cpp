#include "networking.h"
#include <QtNetwork>

Networking::Networking() {
   QTcpSocket *socket = new QTcpSocket;
   socket->connectToHost(host, 2323);
   if(!socket->waitForConnected()) {
       qDebug() << "error" << socket->errorString();
   } else {
       qDebug()<<"success";

       socketIn = new QTcpSocket;
       socketOut = new QTcpSocket;

       socketIn->bind(QHostAddress::AnyIPv4);
       socketOut->bind(QHostAddress::AnyIPv4);

       connect(socketIn, SIGNAL(readyRead()), this, SLOT(getDataFromSocketIn()));

       quint16 socketInPort = socketIn->localPort();
       quint16 socketOutPort = socketOut->localPort();
       QString cmd = "REGS";
       cmd += "&" + QString::number(socketInPort) + "&";
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
    typePacket = message.left(4);

    // manage packet types using first N bytes
    if(typePacket == "ACKD") {
        quint16 port = message.mid(4, 4).toInt();
        // check if the line below errored due to non constant write to class member
        socketOut->connectToHost(host, port, WriteOnly);
    }
}

void Networking::sendData(QString type, QString message, QString login, QString chatId) {
    if(type == "MSGP") {
        type += "&" + login + "&";
        type += chatId + "&";
        type += message + "&";
        socketOut->write(type.toUtf8());
    } else {
        qDebug() << "Unknown packet type";
    }
}

void Networking::getDataFromSocketIn() {
    QTcpSocket * socket = this;
    QString data = socket->readAll();
    QString typePacket = data.left(4);

    if(typePacket == "NMSG") {
        data.remove(4);
        qDebug() << data;
        QStringList newData = parseData(data);
    }

}

QStringList Networking::parseData(QString data) {

}
