
#include <iostream>
#include "Server.h"

Server::Server( QObject* parent )
:   QObject( parent ),
    client( NULL )
{
    connect( &server, SIGNAL( newConnection() ),
        this, SLOT( acceptConnection() ) );

    server.listen( QHostAddress::Any, 8888 );

    std::cout << "Server started at: " << server.serverAddress().toString().toStdString()
              << ":" << server.serverPort() << "." << std::endl;
}

Server::~Server()
{
    server.close();
}

void Server::acceptConnection()
{
    echo
    client = server.nextPendingConnection();
    client->write( "Yo'", 4 );

    connect( client, SIGNAL( readyRead() ),
      this, SLOT( startRead() ) );
}

void Server::startRead()
{
    char buffer[ 1024 ] = {0};
    client->read( buffer, client->bytesAvailable() );
    std::cout << buffer << std::endl;
}
