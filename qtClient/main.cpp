
#include "client.h"
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Client client;
    client.start( "127.0.0.1", 8888 );


    //client.SendMessage();

    return app.exec();
}
