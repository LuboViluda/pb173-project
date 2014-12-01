#include <iostream>

using namespace std;

#include "server.h"
#include "../ProtocolMsg.h"
#include <QApplication>

LogFile* g_log = LogFile::get_logFile( "log.txt" );

int main( int argc, char** argv )
{
    //QApplication app( argc, argv );
    //Server server;

    Msg::Buffer buffer( 1024 );

    buffer << Msg::LoginData << Msg::UsernameHeader << "Pes" << Msg::PasswordHeader << "Charlie";
    std::string a,b,c,d,e;
    buffer >> a >> b >> c >> d >> e;
    std::cout << a << b << c << d << e;
std::cout << std::endl << buffer.IsEmpty();
    //return app.exec();
}
