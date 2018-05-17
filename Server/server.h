#ifndef SERVER_H
#define SERVER_H

#include <QStringList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

class Server : public QTcpServer
{

Q_OBJECT

public:
    Server(QObject *parent = 0);
    void run(int nPort);
protected:

private:
    QHash<QString, QTcpSocket*> inConnections;
    QHash<QString, QTcpSocket*> outConnections;

private slots:
    void onConnection();
    void readyRead();
};

#endif
