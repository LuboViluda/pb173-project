#include <iostream>
#include "Server.h"
#include "Client.h"

Server::Server( int port, QObject* parent )
:   QObject( parent ),
    client( NULL )
{
    connect( &server, SIGNAL( newConnection() ),this, SLOT( acceptConnection() ) );
    server.listen( QHostAddress::Any, port );

    unsigned char key[32] = "key_private_hahaha";
    prepare_table* table = (prepare_table *) malloc(sizeof(prepare_table));
    table->p_table = NULL;
    table->table_length = 20480;
    table->counter = 0;
    memcpy(table->key, (const char*) key, 32);
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

    if((table->counter * 16) % 20480 == 0)
    {
        ecb_prepare_table(table);
    }
    unsigned char* input = (unsigned char *) malloc(1024 * sizeof(unsigned char));
    unsigned char* output = (unsigned char *) malloc(1024 * sizeof(unsigned char));
    memcpy(input,buffer,strlen(buffer));
    xor_table(output, input, table->p_table, 1024);

    std::cout << output << std::endl;
    table->counter = table->counter + 64;
}
