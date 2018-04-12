#ifndef NETWORKING_H
#define NETWORKING_H

#include <QTcpSocket>

class Networking : public QTcpSocket {

    Q_OBJECT

public:
    Networking(QObject *parent = 0);

    void broadcastData(QString message);

public slots:
    void readyRead();
    void readHandler();
    //void sendToServer();
    //void displayError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *socket = nullptr; //socket: addr:port
    QDataStream *in;


};

#endif // NETWORKING_H
