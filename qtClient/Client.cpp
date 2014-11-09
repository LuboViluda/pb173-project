
#include "client.h"
#include <iostream>
#include <QHostAddress>

Client::Client( QObject* parent )
:   QObject( parent ),
    m_name( "Pes" )
{
    connect( &m_client, SIGNAL( connected() ), this, SLOT( Connected() ) );
    connect( &m_client, SIGNAL( readyRead() ), this, SLOT( ReceiveData() ) );
    connect( &m_client, SIGNAL( error( QAbstractSocket::SocketError ) ),
             this, SLOT( HandleError( QAbstractSocket::SocketError ) ) );
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
    std::cout << "Connected to: " << STR_IP( m_client.localAddress() ) << ":"
              << m_client.localPort() << "." << std::endl;
    std::string helloMsg = HELLO_MSG( m_name );
    m_client.write( helloMsg.c_str(), helloMsg.size() + 1 );
    m_client.flush();
}

void Client::ReceiveData()
{
    char buffer[1024] = {0};
    m_client.read( buffer, m_client.bytesAvailable() );
    std::cout << buffer << std::endl;
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
    std::string line;
    std::getline( std::cin, line );
    qint64 written = m_client.write( line.c_str(), line.size() + 1 );
    m_client.flush();
}
