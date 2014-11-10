
//#define _TESTS

#ifndef _TESTS

#include "client.h"
#include <iostream>
#include <QApplication>

int main(int argc, char** argv)
{
    std::string ip;
    std::getline( std::cin, ip );

    QApplication app(argc, argv);

    Client client;
    client.start( ip.c_str(), 8888 );

    return app.exec();
}

#endif

#ifdef _TESTS

#include <iostream>
#include <QApplication>
#include "client.h"

int main( int argc, char** argv )
{
    QApplication app( argc, argv );

   // freopen( "tests\\output.txt", "w", stdout );
   // freopen( "tests\\input.txt", "r", stdin );



    Client client;
    client.start( "127.0.0.1", 8888 );

    return app.exec();
}

#endif
