
#pragma once

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>

#include <map>

struct User
{
    User() {}
    User( std::string p, std::string k )
    :   m_password( p ), m_publicKey( k )
    {}

    std::string m_password;
    std::string m_publicKey;

};
typedef std::map<std::string, User> UserList;

#define echo std::cout << __FILE__ << ": " << __LINE__ << " " << std::endl;

class Server: public QTcpServer
{
Q_OBJECT

public:
    Server( QObject* parent = 0 );
    ~Server();

    inline static const UserList& GetUserList() { return m_userList; }

protected:
    void incomingConnection( qintptr socketDescriptor );

private:

    static UserList m_userList;

};
