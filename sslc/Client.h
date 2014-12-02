
#pragma once

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QSslSocket>

class Client: public QObject
{
    Q_OBJECT

public:
    Client(QObject* parent = 0);
    ~Client();

    void start(QString address, quint16 port);
public slots:
    void startTransfer();


private:
    QSslSocket client;
};


