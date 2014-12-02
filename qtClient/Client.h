
#pragma once

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include "../crypto_crt/crypto.hpp"
#define STR_IP( ip ) ip.toString().toStdString()

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject* parent = NULL );
    Client( bool peer, QObject* parent = NULL);
    ~Client();

    void start( QString address, quint16 port );
    void ConnectToPeer(std::string ip);
public slots:
    void Connected();
    void SendMessage(std::string);
    void ReceiveData();
    void HandleError( QAbstractSocket::SocketError socketError );
private:
    QTcpSocket m_client;
    bool m_connected;
    prepare_table* table;

    std::string m_name;
    std::string m_pass;

    enum SocketError {
        ConnectionRefusedError,
        RemoteHostClosedError,
        HostNotFoundError,
        SocketAccessError,
        SocketResourceError,
        SocketTimeoutError,                     /* 5 */
        DatagramTooLargeError,
        NetworkError,
        AddressInUseError,
        SocketAddressNotAvailableError,
        UnsupportedSocketOperationError,        /* 10 */
        UnfinishedSocketOperationError,
        ProxyAuthenticationRequiredError,
        SslHandshakeFailedError,
        ProxyConnectionRefusedError,
        ProxyConnectionClosedError,             /* 15 */
        ProxyConnectionTimeoutError,
        ProxyNotFoundError,
        ProxyProtocolError,
        OperationError,
        SslInternalError,                       /* 20 */
        SslInvalidUserDataError,
        TemporaryError,

        UnknownSocketError = -1
    };
};
