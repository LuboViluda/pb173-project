#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSslSocket>

class Server: public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject * parent = 0);
    void incomingConnection(int handle);
    ~Server();

public slots:
    void startRead();
    void error( QAbstractSocket::SocketError err );

private:
    QSslSocket* socket;
};

#endif // SERVER_H
