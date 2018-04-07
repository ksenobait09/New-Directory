#ifndef SERVER_H
#define SERVER_H

#include <QStringList>
#include <QTcpServer>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);
    void run(int nPort);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

};

#endif
