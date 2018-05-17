#ifndef NETWORKING_H
#define NETWORKING_H

#include <QTcpSocket>
#include <QString>
#include <QHostAddress>

class Networking : public QTcpSocket {

    Q_OBJECT

public:

    static Networking& Instance() {
            static Networking net;
            return net;
        }

    QTcpSocket * getSocketOut() { return socketOut; }
    QTcpSocket * getSocketIn() { return socketIn; }

    void sendData(QString type, QString message, QString login, QString chatId);
    void parseData(QString data);

public slots:

    void getData();
    void sendData();
    void getDataFromSocketIn();

signals:


private:

   Networking();
   ~Networking() = default;
   Networking(Networking const&) = delete;
   Networking& operator= (Networking const&) = delete;

    QTcpSocket *socketIn = nullptr;
    QTcpSocket *socketOut = nullptr;
    QHostAddress host;
    QString user = "null";

};

#endif // NETWORKING_H
