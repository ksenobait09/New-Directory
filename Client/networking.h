#ifndef NETWORKING_H
#define NETWORKING_H

#include <QTcpSocket>
#include <QString>
#include <QHostAddress>

class Networking : public QTcpSocket {

    Q_OBJECT

public:

    Networking(QObject *parent = 0);

public slots:

    void getData();
    void sendData();

signals:


private:

    QTcpSocket *socketIn = nullptr;
    QTcpSocket *socketOut = nullptr;
    QHostAddress host;
    QString user = "null";

};

#endif // NETWORKING_H
