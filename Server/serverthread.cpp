#include "serverthread.h"

#include <QtNetwork>

ServerThread::ServerThread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
    qDebug()<<"Thread created";
}

//Тело потока. Отдаём данные в сокет
void ServerThread::run()
{
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }
    text="Connection succesful";

    // Четыре строчки ниже - магия, про которую прочёл в документации.
    // Без них не работает
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << text;
    tcpSocket.write(block);

    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
}
