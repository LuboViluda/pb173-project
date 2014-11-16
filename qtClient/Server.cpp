#include <iostream>
#include "Server.h"

Server::Server( QObject* parent )
:   QObject( parent ),
    client( NULL )
{
    connect( &server, SIGNAL( newConnection() ),this, SLOT( acceptConnection() ) );
    server.listen( QHostAddress::Any, 8888 );

    std::cout << "#Waiting for another client... " << std::endl;
}

Server::~Server()
{
    server.close();
}

void Server::acceptConnection()
{
    client = server.nextPendingConnection();
    client->write( "OK", 3 );

    connect( client, SIGNAL(bytesWritten(qint64)), this, SLOT( startRead() ) );
}

void Server::startRead()
{
    char buffer[ 1024 ] = {0};
    client->read( buffer, client->bytesAvailable() );
    std::cout << buffer << std::endl;
}

void Server::sendMessage()
{
    std::string line;
    std::getline( std::cin, line );
    client->write( line.c_str(), line.size() + 1 );
}
