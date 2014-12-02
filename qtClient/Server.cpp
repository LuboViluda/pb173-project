#include <iostream>
#include "Server.h"
#include "Client.h"
#include <time.h>

Server::Server( int port, QObject* parent )
:   QObject( parent ),
    client( NULL )
{
    connect( &server, SIGNAL( newConnection() ),this, SLOT( acceptConnection() ) );
    server.listen( QHostAddress::Any, port );

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

   if( !strncmp( buffer, "key1", 4) )
   {
       srand (time(NULL));
       for(int i = 0; i < 16; i++)
       {
           key[i] = rand() % 256;
       }

       std::string buffer((const char*)key);
       buffer = "key2" + buffer;
       client->write(buffer.c_str(), buffer.size());
       strncpy((char*)key + 16, buffer.c_str() + 4, 16);
   }


    if((table->counter * 16) % 20480 == 0)
    {
        ecb_prepare_table(table);
    }
    unsigned char* input = (unsigned char *) malloc(1024 * sizeof(unsigned char));
    unsigned char* output = (unsigned char *) malloc(1024 * sizeof(unsigned char));
    memcpy(input,buffer,strlen(buffer));
    xor_table(output, input, table->p_table, 1024);

    std::cout << output << std::endl;
}
