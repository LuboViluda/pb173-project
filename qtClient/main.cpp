#include "client.h"
#include "server.h"
#include <QString>
#include <iostream>
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    std::string test;
    std::getline(std::cin, test);
    if(!test.compare("1"))
    {
        Server* server = new Server(8889);
    }
    if(!test.compare("2"))
    {
        Server* server = new Server(8888);
    }

    std::getline(std::cin, test);

    Client * client = new Client(true);
    std::string ip;
    /*std::getline( std::cin, ip );
    client->start( ip.c_str(), 8888 ); */
    if(!test.compare("1"))
    {
        client->start("127.0.0.1", 8888);
    }
    if(!test.compare("2"))
    {
        client->start("127.0.0.1", 8889);
    }
    return app.exec();
}
