
#include "ClientThread.h"
#include <iostream>
#include "Server.h"

UserList Server::m_userList = UserList();

Server::Server( QObject* parent )
:   QTcpServer( parent )
{
   // connect( &m_socket, SIGNAL( newConnection() ),
      //  this, SLOT( acceptConnection() ) );

    listen( QHostAddress::Any, 8888 );

    std::cout << "Server started at: " << serverAddress().toString().toStdString()
              << ":" << serverPort() << "." << std::endl;

    m_userList[ "User1" ] = User( "123456", "" );
    m_userList[ "User2" ] = User( "456", "" );
    m_userList[ "Pes" ] = User( "487", " " );
    m_userList[ "User5" ] = User( "4516", "" );
}

Server::~Server()
{
    close();
}

void Server::incomingConnection( qintptr socketDescriptor )
{
    // We have a new connection
    qDebug() << socketDescriptor << " Connecting...";

    // Every new connection will be run in a newly created thread
    ClientThread* thread = new ClientThread( socketDescriptor, this );

    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect( thread, SIGNAL( finished() ), thread, SLOT(deleteLater() ) );

    thread->start();
}

/*void Server::acceptConnection()
{    
    QTcpSocket* client = m_socket.nextPendingConnection();
/*
    ClientThread* ct = new ClientThread( client );
    QThread* thread = new QThread( this );
    connect( thread, SIGNAL( finished() ), thread, SLOT( deleteLater() ) );
    ct->moveToThread( thread );
    thread->start();
*/
    /*echo
    ClientThread* thread = new ClientThread( client->socketDescriptor(), this );
    echo
    connect( thread, SIGNAL( finished() ), thread, SLOT( deleteLater() ) );
    echo
    thread->start();*/
    /*connect( client, SIGNAL( readyRead() ),
      this, SLOT( startRead() ) );*/
//}

/*void Server::startRead()
{
    char buffer[ 1024 ] = {0};
    client->read( buffer, client->bytesAvailable() );
    std::cout << buffer << std::endl;
}*/
