#include <iostream>
#include "Client.h"
using namespace std;

int main( int argc, char** argv )
{
    QCoreApplication app(argc, argv);

   //Server server;

    Client client;
    client.start("127.0.0.1", 8889);

    return app.exec();
}

