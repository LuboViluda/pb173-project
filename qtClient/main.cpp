#include "client.h"
#include "server.h"
#include <QString>
#include <iostream>
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Server server;
    Client client(true);
   /* std::string ip;
    std::getline( std::cin, ip );
    client.start( "", 8888 ); */

    //test client - client
    client.start("127.0.0.1", 8888);


    return app.exec();
}
