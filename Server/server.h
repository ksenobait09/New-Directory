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
    Server();
    void run(int nPort);

    static Server& Instance() {
            static Server server;
            return server;
        }

    // chatId refferencing sockets for rooms
    QMultiMap<QString, QTcpSocket * > chatToSocket;

    QTcpSocket * getOutConnection(QString login) { return outConnections[login]; }
    void sendMessage(QTcpSocket * socket, QString message);

protected:

private:
    QHash<QString, QTcpServer * > inConnections;
    QHash<QString, QTcpSocket * > outConnections;

private slots:
    void onConnection();
    void readyRead();
    void clientInConnected();
    void clientOutConnected();
};

#endif
