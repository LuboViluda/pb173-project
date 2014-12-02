#include <iostream>
#include "Server.h"
using namespace std;

int main( int argc, char** argv )
{
    QCoreApplication app(argc, argv);

    Server server;


    return app.exec();
}

