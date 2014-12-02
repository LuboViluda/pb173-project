
#pragma once

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QtSql/QtSql>

#include <map>

#include "../LogFile/logfile.h"
extern LogFile* g_log;

struct User
{
    User() {}
    User( std::string k, std::string ip )
    :   m_publicKey( k ), m_ip( ip )
    {}

    std::string m_publicKey;
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
    static QSqlDatabase m_db;

};
