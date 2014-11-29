#include "client.h"
#include "server.h"
#include <iostream>
#include <QHostAddress>
#include <QThread>
#include "inputthread.h"
#include "crypt.h"
#define test 1

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
}

Client::Client(bool peer, QObject* parent )
:   QObject( parent ),
    m_connected( false ),
    m_name( "User1" ),
    m_pass("123456")
{
    connect( &m_client, SIGNAL( connected() ), this, SLOT( Connected() ) );
    connect( &m_client, SIGNAL( readyRead() ), this, SLOT( ReceiveDataP2P() ) );
    connect( &m_client, SIGNAL( error( QAbstractSocket::SocketError ) ),
             this, SLOT( HandleError( QAbstractSocket::SocketError ) ) );
    InputThread * thread = new InputThread(this);
    connect(thread, SIGNAL(inputSignal(std::string) ), this, SLOT (SendMessage(std::string)));
    thread->start();
    generate_random_iv(iv);
    generate_key("test",key);
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
    //test
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
#ifdef _TEST
        m_client.write( "t ", 2 );
        m_client.write( TEST_DATA_OUT, strlen( TEST_DATA_OUT ) + 1 );
#else
         m_client.write( "rul ", 5 );
#endif
    }
#ifdef _TEST
    else if( !strncmp( buffer, "t", 1 ) )
    {
        std::string temp( buffer, 2, strlen( buffer ) - 1 );
        if( !temp.compare( TEST_DATA_IN ) )
        {
            std::cout << "TEST: login and data sending works." << std::endl;
        }
        else
        {
            std::cout << "TEST: login or data sending does not work( or both )." << std::endl;
        }
    }
#endif
    else if(!strncmp (buffer, "ul", 2))
    {
        std::string temp(buffer, 3, strlen(buffer) - 2);
        std::cout << temp << std::endl;
        std::cout << "Choose user: " << std::endl;
        std::string user;
        std::getline(std::cin, user);
        user = "rc " + user;
        m_client.write(user.c_str(), user.size()+1);
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
            //Server server;
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

void Client::ReceiveDataP2P()
{
    if(test == 2)
    {
        char buffer[ 1024 ] = { 0 };
        m_client.read( buffer, m_client.bytesAvailable() );
        //std::cout << buffer << std::endl;
        if( !strncmp( buffer, "test", 4)  )
        {
            if( !strncmp( buffer, "test 987654321", 14) )
            {
                std::cout << "Test1 passed" << std::endl;
            }
            else
            {
                std::cout << "Test1 failed" << std::endl;

            }
        }
        if( !strncmp( buffer, "test", 4)  )
        {
            if( strncmp( buffer, "test 087654321", 14) )
            {
                std::cout << "Test2 passed" << std::endl;
            }
            else
            {
                std::cout << "Test2 failed" << std::endl;

            }
        }

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

void Client::SendMessage(std::string line)
{
    if(test == 0)
    {
        m_client.write( line.c_str(), line.size() + 1 );
    }
    if(test == 1)
    {
        unsigned char* ln = (unsigned char*)line.c_str();
        unsigned char *enc_line;
        std::cout << ln;
        encryption(ln, line.size(),iv, key, &enc_line);
        char *out = (char*)enc_line;
        m_client.write( out, strlen(out) );
    }
    if(test == 2)
    {
         m_client.write( "123456789 tset", 16);
    }
}

void Client::ConnectToPeer(std::string ip)
{
   // Client client(true);
   // client.start( ip.c_str(), 8888 );
}
