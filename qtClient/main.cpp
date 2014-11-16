#include "client.h"
#include "server.h"
#include <iostream>
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    std::string ip;
    //std::getline( std::cin, ip );
    Client client;
    client.start( "88.88.88.100", 8888 );
    return app.exec();
}
