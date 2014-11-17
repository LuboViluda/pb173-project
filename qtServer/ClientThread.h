
#pragma once

#include <QObject>
#include <QThread>
#include <QTcpSocket>

#include "Server.h"

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

public slots:
    void Read();
    void deleteLater();

protected:
    void ProcessMsg( std::string str );

private:
    QTcpSocket* m_socket;
    int m_socketDescriptor;
    State m_state;

    static const UserList& m_userList;
    std::string m_username;

    const std::string MSG_REQUEST_LOGIN_DATA = "rld  ";

};
