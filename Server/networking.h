#ifndef NETWORKING_H
#define NETWORKING_H

#include <QTcpSocket>

class Networking : public QTcpSocket {

    Q_OBJECT

public:
    Networking(QObject *parent = 0);

public slots:
    size_t readyRead();
    void sendToServer(QString message);
    //void displayError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *socket; //socket: addr:port
    QDataStream *in;


};

#endif // NETWORKING_H
