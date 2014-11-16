#include "client.h"
#include "server.h"
#include <iostream>
#include <QHostAddress>
#include <QThread>

Client::Client( QObject* parent )
:   QObject( parent ),
    m_connected( false ),
    m_name( "User1" ),
    m_pass("123456")
{
    connect( &m_client, SIGNAL( connected() ), this, SLOT( Connected() ) );
    connect( &m_client, SIGNAL( readyRead() ), this, SLOT( ReceiveData() ) );
    connect( &m_client, SIGNAL( error( QAbstractSocket::SocketError ) ),
             this, SLOT( HandleError( QAbstractSocket::SocketError ) ) );
    //connect( &m_client, SIGNAL( bytesWritten(qint64)) , this, SLOT( SendMessage() ) );
}

Client::Client( bool peer, QObject* parent )
:   QObject( parent ),
    m_connected( false ),
    m_name( "User1" ),
    m_pass("123456")
{
    connect( &m_client, SIGNAL( connected() ), this, SLOT( Connected() ) );
    connect( &m_client, SIGNAL( readyRead() ), this, SLOT( ReceiveData() ) );
    connect( &m_client, SIGNAL( error( QAbstractSocket::SocketError ) ),
             this, SLOT( HandleError( QAbstractSocket::SocketError ) ) );
    connect( &m_client, SIGNAL( bytesWritten(qint64)) , this, SLOT( SendMessage() ) );
}

Client::~Client()
{
    if(m_connected)
    {
        m_client.write("lo", 3);
    }
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
              << m_client.peerPort() << "." << std ::endl;
}

void Client::ReceiveData()
{
    char buffer[ 1024 ] = { 0 };
    m_client.read( buffer, m_client.bytesAvailable() );
    std::cout << buffer << std::endl;

    if( !strncmp( buffer, "rld", 3) )
    {
        m_connected = true;
        std::string loginMsg = LOGIN_MSG( m_name, m_pass );
        m_client.write( loginMsg.c_str(), loginMsg.size() + 1 );
        m_client.flush();
    }
    else if(!strncmp (buffer, "li", 2))
    {
         m_client.write( "rul ", 5 );
    }
    else if(!strncmp (buffer, "ul", 2))
    {
        std::string temp(buffer, 3, strlen(buffer) - 2);
        std::cout << temp << std::endl;
    }
    else if(!strncmp (buffer, "ip", 2))
    {
        std::string ip(buffer, 3, strlen(buffer) - 2);
        std::cout << ip << std::endl;
        m_client.close();
        ConnectToPeer(ip);
    }
    else if(!strncmp (buffer, "rc", 2))
    {
        std::string user(buffer, 3, strlen(buffer) - 2);
        std::cout << " User " <<user << " wants to establish connection." << std::endl;
        std::cout << "[y] for accept, [n] for refuse" << std::endl;
        std::string line;
        std::getline( std::cin, line );
        if(!strncmp(line.c_str(), "y", 1))
        {
            m_client.write( "ac ", 4 );
            m_client.close();
            Server server;
        }
        else
        {
            m_client.write( "rc ", 4 );
        }
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
    case ConnectionRefusedError:
        std::cout << "ConnectionRefusedError." << std::endl;
        break;
    case RemoteHostClosedError:
        std::cout << "RemoteHostClosedError." << std::endl;
        break;
    case HostNotFoundError:
        std::cout << "HostNotFoundError." << std::endl;
        break;
    case SocketTimeoutError:
        std::cout << "SocketTimeoutError." << std::endl;
        break;
    case NetworkError:
        std::cout << "NetworkError." << std::endl;
        break;
    case SslHandshakeFailedError:
        std::cout << "SslHandshakeFailedError." << std::endl;
        break;
    default:
        std::cout << "Unknown error while connecting." << std::endl;
        break;
    }
}

void Client::SendMessage()
{
    if(m_connected)
    {
        std::string line;
        std::getline( std::cin, line );
        m_client.write( line.c_str(), line.size() + 1 );
    }
    else
    {
        m_client.write("#Pending...", 12);
    }
}

void Client::ConnectToPeer(std::string ip)
{
    Client client(true);
    client.start( ip.c_str(), 8888 );
}
