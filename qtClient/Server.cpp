#include <iostream>
#include "Server.h"
#define test 0

Server::Server( int port, QObject* parent )
:   QObject( parent ),
    client( NULL )
{
    connect( &server, SIGNAL( newConnection() ),this, SLOT( acceptConnection() ) );
    server.listen( QHostAddress::Any, port );

    std::cout << "#Waiting for another client... " << std::endl;
}

Server::~Server()
{
    server.close();
}

void Server::acceptConnection()
{
    client = server.nextPendingConnection();
    //client->write( "rld", 4 );
    connect(client, SIGNAL( readyRead()), this, SLOT(startRead()));
}

void Server::startRead()
{
    char buffer[ 1024 ] = {0};
    client->read( buffer, client->bytesAvailable() );
    if(test == 0)  std::cout << buffer << std::endl;
    if(test == 2)
    {
        std::reverse( buffer, &buffer[ strlen( buffer ) ] );
        client->write( buffer, strlen(buffer) +1 );
    }
}
