#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QAbstractSocket>

#include "Connection/iconnection.h"
#include "tcpserverdataprocessor.h"
#include "brucecl_global.h"

class BRUCECL_MK3SHARED_EXPORT TcpServer : public QObject, public IConnection
{
    Q_OBJECT
    Q_INTERFACES(IConnection)
public:
    explicit TcpServer(QObject *parent = 0);

signals:
    void connectionStatusChanged    (ConnectionStatus);
    void receivedInstruction        (Instruction);
    void message                    (MessageType, QString, QString = "TcpServer");

        void serverAddressChanged   (QString, QString);
        void receivedImage          (QImage&);

public slots:
    void closeConnection    ();
    void sendInstruction    (Instruction);

        void openConnection ();

private slots:
    void connected          ();
    void disconnected       ();
    void readyRead          ();

        void emitInternalError  (QAbstractSocket::SocketError);
        void newConnection  ();

private:
    void send(const QByteArray &);

        QTcpServer              *server         {new QTcpServer};
        QTcpSocket              *socket         {new QTcpSocket};
        TcpServerDataProcessor  dataProcessor   {};
};

#endif // TCPSERVER_H
