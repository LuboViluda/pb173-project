
#include "client.h"
#include <iostream>
#include <QHostAddress>

Client::Client( QObject* parent )
:   QObject( parent ),
    m_connected( false ),
    m_name( "Pes" )
{
    connect( &m_client, SIGNAL( connected() ), this, SLOT( Connected() ) );
    connect( &m_client, SIGNAL( readyRead() ), this, SLOT( ReceiveData() ) );
    connect( &m_client, SIGNAL( error( QAbstractSocket::SocketError ) ),
             this, SLOT( HandleError( QAbstractSocket::SocketError ) ) );
    connect( &m_client, SIGNAL( bytesWritten( qint64 ) ), this, SLOT( SendMessage() ) );
}

Client::~Client()
{
    m_client.close();
}

void Client::start( QString address, quint16 port )
{
    QHostAddress addr( address );
    m_client.connectToHost( addr, port );
}

void Client::Connected()
{
    std::cout << "Connected to: " << STR_IP( m_client.peerAddress() ) << ":"
              << m_client.peerPort() << "." << std::endl;
    std::string helloMsg = HELLO_MSG( m_name );
    m_client.write( helloMsg.c_str(), helloMsg.size() + 1 );
    //m_client.flush();
}

void Client::ReceiveData()
{
    char buffer[ 1024 ] = { 0 };
    m_client.read( buffer, m_client.bytesAvailable() );
    std::cout << buffer << std::endl;

    if( !strcmp( buffer, "OK" ) )
    {
        m_connected = true;
    }
    else
    {
        std::cout << "Server refused connection" << std::endl;
        m_client.close();
    }
}

void Client::HandleError( QAbstractSocket::SocketError error )
{
    switch( error )
    {
    case QAbstractSocket::SocketError::ConnectionRefusedError:
        std::cout << "ConnectionRefusedError." << std::endl;
        break;
    case QAbstractSocket::SocketError::RemoteHostClosedError:
        std::cout << "RemoteHostClosedError." << std::endl;
        break;
    case QAbstractSocket::SocketError::HostNotFoundError:
        std::cout << "HostNotFoundError." << std::endl;
        break;
    case QAbstractSocket::SocketError::SocketTimeoutError:
        std::cout << "SocketTimeoutError." << std::endl;
        break;
    case QAbstractSocket::SocketError::NetworkError:
        std::cout << "NetworkError." << std::endl;
        break;
    case QAbstractSocket::SocketError::SslHandshakeFailedError:
        std::cout << "SslHandshakeFailedError." << std::endl;
        break;
    default:
        std::cout << "Unknown error while connecting." << std::endl;
        break;
    }
}

void Client::SendMessage()
{
    if( m_connected )
    {
        std::string line;
        std::getline( std::cin, line );
        qint64 written = m_client.write( line.c_str(), line.size() + 1 );
        //m_client.flush();
    }
}
