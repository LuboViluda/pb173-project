#include "client.h"
#include "server.h"
#include <QString>
#include <iostream>
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Client * client = new Client();
    std::string serverIP = "88.88.88.100";
    client->start(serverIP.c_str(), 8888);


    return app.exec();
}
