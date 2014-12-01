#include "client.h"
#include "server.h"
#include <QString>
#include <iostream>
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Server * serverino = new Server(7777);
    Client * client = new Client();
    std::string serverIP = "88.88.88.101";
    client->start(serverIP.c_str(), 8888);


    return app.exec();
}
