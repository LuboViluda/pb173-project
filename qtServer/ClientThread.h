
#pragma once

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QSslSocket>

#include "Server.h"
#include "../ProtocolMsg.h"

#define LOG_THREAD "Thread: " << currentThreadId() << " | "

class ClientThread : public QThread
{
Q_OBJECT

    enum State
    {
        CONNECTED,
        LOGGED
    };

public:
    ClientThread( int socketDescriptor, QObject* parent = NULL );

    void run();
    void SendMsg( const std::string& msg );

public slots:
    void Read();
    void deleteLater();

protected:
    void ProcessMsg( std::string& str );

    void HandleLogin( std::stringstream& msg );
    void HandleRegistration( std::stringstream& msg );
    void SendUserList();
    void SendUserDetails( std::string& username );
    void LogOut();

private:
    QTcpSocket* m_socket;
    //QSslSocket* m_socket;
    int m_socketDescriptor;
    State m_state;

    std::string m_username;

    Msg::Buffer m_messages;

};


