
#pragma once

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QtSql/QtSql>

#include <map>
#include <string>

#include "../LogFile/logfile.h"
extern LogFile* g_log;
class ClientThread;

struct User
{
    User() {}
    User( std::string ip )
    :   m_ip( ip )
    {}

    std::string m_ip;

};
typedef std::map<std::string, User> UserList;

class Server: public QTcpServer
{
Q_OBJECT

public:
    Server( QObject* parent = 0 );
    virtual ~Server();

protected:
    void incomingConnection( qintptr socketDescriptor );

public:
    static UserList m_userList;
    static std::map<std::string, ClientThread*> m_threadList;
    static QSqlDatabase m_db;

};
