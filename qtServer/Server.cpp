
#include <iostream>
#include <sstream>

#include "Server.h"
#include "Console.h"
#include "ClientThread.h"

QSqlDatabase Server::m_db = QSqlDatabase::addDatabase( "QSQLITE" );
std::map<std::string, ClientThread*> Server::m_threadList;
UserList Server::m_userList;

Server::Server( QObject* parent )
:   QTcpServer( parent )
{
    listen( QHostAddress::Any, 8888 );

    g_log->make_log( "Server started." );

    std::cout << "Server started at: " << serverAddress().toString().toStdString()
              << ":" << serverPort() << "." << std::endl;

    m_db.setDatabaseName( "users.db3" );
    m_db.open();

    QSqlQuery query( m_db );
    if( query.exec( "CREATE TABLE users( username text, password text )" ) )
        std::cout << "Table created." << std::endl;
    else
        std::cout << "Table creation error " << query.lastError().text().toStdString() << std::endl;

   /* QSqlQuery query2( m_db );
    if( query2.exec( "INSERT INTO users VALUES( 'User1', '123456', '2asg1458ah49had' )" ) )
        std::cout << "Query insterd." << std::endl;
    else
        std::cout << "Table creation error " << query.lastError().text().toStdString() << std::endl;*/

    Console* c = new Console( this );
    c->start();
}

Server::~Server()
{
    g_log->make_log( "Server shutdown." );
    close();
}

void Server::incomingConnection( qintptr socketDescriptor )
{
    std::stringstream logStream;
    logStream << "Connection on socket " << socketDescriptor << ".";
    g_log->make_log( logStream.str() );

    ClientThread* thread = new ClientThread( socketDescriptor, this );
    connect( thread, SIGNAL( finished() ), thread, SLOT( deleteLater() ) );    

    thread->start();
}

