#include "networking.h"
#include <QtNetwork>

Networking::Networking(QObject *parent, QString host, QString user)
    : QTcpSocket(parent)
{
   socket = new QTcpSocket;
   socket->connectToHost(host, 2323);
   if(!socket->waitForConnected()) {
       qDebug() << "error" << socket->errorString();
   } else {
       qDebug()<<"success";
       QTcpSocket *socketIn = new QTcpSocket;
       QTcpSocket *socketOut = new QTcpSocket;
       quint16 socketInPort = socketIn->localPort();
       quint16 socketOutPort = socketOut->localPort();
       QString cmd = "REGS";
       cmd += socketInPort + "&";
       cmd += socketOutPort + "&";
       cmd += user;
       socket->write(cmd.toUtf8());
       socket->close();
       delete socket;
   }

}
