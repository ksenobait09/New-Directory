#ifndef SERVER_H
#define SERVER_H

#include <QStringList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QMultiMap>

class Server : public QTcpServer
{

Q_OBJECT

public:
    Server(QObject *parent = 0);
    void run(int nPort);

    // that's bad
    QMultiMap<QString, QTcpSocket*> chatToSocket;
    void sendMessage(QTcpSocket* socket, QString message);

protected:

private:
    QHash<QString, QTcpServer*> inConnections;
    QHash<QString, QTcpSocket*> outConnections;

private slots:
    void onConnection();
    void readyRead();
    void clientInConnected();
    void clientOutConnected();
};

#endif
