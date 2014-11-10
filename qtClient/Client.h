
#pragma once

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>

#define HELLO_MSG( name ) std::string( "Yo' from " + name )
#define STR_IP( ip ) ip.toString().toStdString()

class Client : public QObject
{
    Q_OBJECT
public:
    Client( QObject* parent = NULL );
    ~Client();

    void start( QString address, quint16 port );

public slots:
    void Connected();
    void SendMessage();
    void ReceiveData();
    void HandleError( QAbstractSocket::SocketError socketError );

private:
    QTcpSocket m_client;
    bool m_connected;

    std::string m_name;

};
