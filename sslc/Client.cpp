#include "client.h"
#include <QDebug>

Client::Client(QObject* parent) :
    QObject(parent)
{
    connect(&client, SIGNAL(encrypted()),
            this, SLOT(startTransfer()));
}

Client::~Client()
{
    client.close();
}

void Client::start(QString address, quint16 port)
{
    client.ignoreSslErrors();
    client.connectToHostEncrypted(address, port);
    if (!client.waitForEncrypted())  {
        qDebug() << client.errorString();
        return;
    }

    client.write("GET / HTTP/1.0\r\n\r\n");
    while (client.waitForReadyRead())
        qDebug() << client.readAll().data();
}

void Client::startTransfer()
{
    qDebug() << "startTransfer()";
    client.write("Hello, world", 13);
    //client.flush();
}
