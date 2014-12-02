#include "server.h"
#include <iostream>
#include <QByteArray>
#include <QSslCertificate>
#include <QSslKey>
using namespace std;

Server::Server(QObject* parent) :
    QTcpServer(parent)
{
    listen(QHostAddress::Any, 8889);
}

void Server::error( QAbstractSocket::SocketError err )
{
    std::cout << err << "-" << socket->errorString().toStdString() << std::endl;
}

void Server::startRead()
{
    char buffer[1024] = { 0 };
    socket->read(buffer, socket->bytesAvailable());
    cout << buffer << endl;
    //socket->close();
}

void Server::incomingConnection(int socketDescriptor)
{
    socket = new QSslSocket;
    connect( socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));

    connect(socket, SIGNAL(encrypted()),
            this, SLOT(startRead()));

    socket->setProtocol( QSsl::AnyProtocol );
    socket->ignoreSslErrors();
    socket->setPeerVerifyMode(QSslSocket::VerifyNone);
    socket->setPrivateKey("../server.key", QSsl::Rsa, QSsl::Pem, "hrochokobra");
    socket->setLocalCertificate( "../server.crt", QSsl::Pem );
    socket->setProtocol(QSsl::TlsV1SslV3);
    if (socket->setSocketDescriptor(socketDescriptor))
    {
        connect(socket, SIGNAL(encrypted()), this, SLOT(ready()));
        connect(socket, SIGNAL(connected()), this, SLOT(ready()));
        addPendingConnection(socket);

        socket->startServerEncryption();
    }
}

Server::~Server()
{
    //delete socket;
}
