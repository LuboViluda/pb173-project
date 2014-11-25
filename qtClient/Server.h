
#pragma once

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>

#define echo std::cout << __FILE__ << ": " << __LINE__ << " " << std::endl;

class Server: public QObject
{
Q_OBJECT

public:
    Server( int port, QObject * parent = 0 );
    ~Server();

public slots:
    void acceptConnection();
    void startRead();

private:
    QTcpServer server;
    QTcpSocket* client;

};
