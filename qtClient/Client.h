
#pragma once

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>

//#define _TEST
#ifdef _TEST
    #define TEST_DATA_OUT   "123456789abcdefgh"
    #define TEST_DATA_IN    "hgfedcba987654321"
#endif

#define LOGIN_MSG( name, pass ) std::string( "ld u " + name + " p " + pass + " ")
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
    void ReceiveDataP2P();
    void HandleError( QAbstractSocket::SocketError socketError );
private:
    QTcpSocket m_client;
    bool m_connected;
    unsigned char iv[16];
    unsigned char key[16];

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
