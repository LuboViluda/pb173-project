#include "client.h"
#include "server.h"
#include <iostream>
#include <QHostAddress>
#include <QThread>
#include "inputthread.h"
#include "../ProtocolMsg.h"

Client::Client( QObject* parent )
:   QObject( parent ),
    m_connected( false )
{
    connect( &m_client, SIGNAL( connected() ), this, SLOT( Connected() ) );
    connect( &m_client, SIGNAL( readyRead() ), this, SLOT( ReceiveData() ) );
    connect( &m_client, SIGNAL( error( QAbstractSocket::SocketError ) ),
             this, SLOT( HandleError( QAbstractSocket::SocketError ) ) );
}

Client::Client(bool peer, QObject* parent )
:   QObject( parent ),
    m_connected( false )
{
    connect( &m_client, SIGNAL( connected() ), this, SLOT( Connected() ) );
    connect( &m_client, SIGNAL( readyRead() ), this, SLOT( ReceiveDataP2P() ) );
    connect( &m_client, SIGNAL( error( QAbstractSocket::SocketError ) ),
             this, SLOT( HandleError( QAbstractSocket::SocketError ) ) );
    InputThread * thread = new InputThread(this);
    connect(thread, SIGNAL(inputSignal(std::string) ), this, SLOT (SendMessage(std::string)));
    thread->start();
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
    m_client.connectToHost(addr, port);
}

void Client::Connected()
{

    std::cout << "Connected to: " << STR_IP( m_client.peerAddress() ) << ":"
              << m_client.peerPort() << "." << std ::endl;
    m_connected = true;
}

void Client::ReceiveData()
{
    char buffer[ 1024 ] = { 0 };
    m_client.read( buffer, m_client.bytesAvailable() );
    //std::cout << buffer << std::endl;

    if( !strncmp( buffer, "ld", 2) )
    {
        std::cout << "Press 1 for register 2 for login" << std::endl;
        std::string menu;
        std::getline(std::cin, menu);

        std::cout << "Enter your name: ";
        std::getline(std::cin, m_name);
        std::cout << "Password: ";
        std::getline(std::cin, m_pass);

        if( !strncmp( menu.c_str(), "1", 1) )
        {
            std::string buffer;
            buffer = Msg::RegisterNewUser +" "+ Msg::UsernameHeader +" "+ m_name +" "+ Msg::PasswordHeader +" "+ m_pass;
            m_client.write(buffer.c_str(), buffer.size());
        }
        else if( !strncmp( menu.c_str(), "2", 1) )
        {
            std::string buffer;
            buffer = Msg::LoginData +" "+ Msg::UsernameHeader +" "+ m_name +" "+ Msg::PasswordHeader +" "+ m_pass;
            m_client.write(buffer.c_str(), buffer.size());
        }
        else
        {
            std::cout << "Invalid command" << std::endl;
        }
    }
    else if(!strncmp (buffer, "li", 2))
    {
         m_client.write( "rul ", 5 );
    }
    else if(!strncmp (buffer, "ul", 2))
    {
        std::string temp(buffer, 3, strlen(buffer) - 2);
        std::cout << temp << std::endl;
        std::cout << "Choose user: " << std::endl;
        std::string user;
        std::getline(std::cin, user);
        if(!strncmp (user.c_str(), "refresh", 7))
        {
            m_client.write( "rul ", 5 );
        }
        else if(!strncmp (user.c_str(), "dc", 2))
        {
            m_client.write( "lo ", 5 );
            m_client.close();
        }
        else
        {
            user = Msg::RequestUserDetails +" "+ user;
            m_client.write(user.c_str(), user.size()+1);
        }
    }
    else if(!strncmp (buffer, "ud ip", 5))
    {
        std::string ip(buffer, 6, strlen(buffer) - 5);
        ConnectToPeer(ip);
    }
    else
    {
        std::cout << "Server refused connection" << std::endl;
        m_client.close();
    }
}

void Client::ReceiveDataP2P()
{

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

}

void Client::ConnectToPeer(std::string ip)
{
   m_client.close();
   Client * clienterino = new Client(true);
   clienterino->start( ip.c_str(), 7777 );
}
