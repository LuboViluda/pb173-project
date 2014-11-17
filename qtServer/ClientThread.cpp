
#include <iostream>
#include <string>
#include <sstream>

#include "ClientThread.h"

const UserList& ClientThread::m_userList = Server::GetUserList();

ClientThread::ClientThread( int socketDescriptor, QObject* parent )
:   QThread( parent ),
    m_socket( NULL ),
    m_socketDescriptor( socketDescriptor ),
    m_state( CONNECTED )
{}

void ClientThread::deleteLater()
{
    std::cout << "Process deleted" << std::endl;
}

void ClientThread::run()
{
    m_socket = new QTcpSocket();
    m_socket->setSocketDescriptor( m_socketDescriptor );
    std::cout << "IP address " << m_socket->peerAddress().toString().toStdString() << ":"
              << m_socket->peerPort() << " connected." << std::endl;

    m_socket->write( MSG_REQUEST_LOGIN_DATA.c_str(), MSG_REQUEST_LOGIN_DATA.size() + 1 );

    connect( m_socket, SIGNAL( readyRead() ), this, SLOT( Read() ), Qt::DirectConnection );

    exec();
}

void ClientThread::Read()
{
    char buffer[ 1024 ] = { 0 };
    m_socket->read( buffer, m_socket->bytesAvailable() );
    std::cout << buffer << std::endl;

    ProcessMsg( std::string( buffer ) );
}

void ClientThread::ProcessMsg( std::string str )
{
    std::stringstream msg( str );
    std::string header;
    std::string value;
    switch( m_state )
    {
    case CONNECTED:
        msg >> header;
        if( !header.compare( "u" ) )
        {
            msg >> value;
            if( m_userList.find( value ) != m_userList.end() )
            {
                const User& user = m_userList.find( value )->second;
                msg >> header;
                if( !header.compare( "p" ) )
                {
                    msg >> value;
                    if( !user.m_password.compare( value ) )
                    {
                        m_socket->write( "li ", 4 );
                        m_state = LOGGED;
                        return;
                    }
                }
            }
        }
        m_socket->write( "e 1 ", 4 );
        m_socket->write( MSG_REQUEST_LOGIN_DATA.c_str(), MSG_REQUEST_LOGIN_DATA.size() + 1 );
        break;
    case LOGGED:
        msg >> header;
        if( !header.compare( "rul" ) )
        {
            m_socket->write( "ul ", 3 );
            for( UserList::const_iterator i = m_userList.begin(), e = m_userList.end(); i != e; i++ )
            {
                m_socket->write( i->first.c_str(), i->first.size() );
                m_socket->write( " ", 1 );
            }
            m_socket->write( "", 1 );
            return;
        }
        else if( !header.compare( "t" ) )
        {
            msg >> value;
            std::reverse( value.begin(), value.end() );
            m_socket->write( "t ", 2 );
            m_socket->write( value.c_str(), value.size() + 1 );
            return;
        }
        break;
    }
}
