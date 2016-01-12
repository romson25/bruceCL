#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include <QAbstractSocket>

#include "Connection/iconnection.h"
#include "tcpclientdataprocessor.h"
#include "brucecl_global.h"

class BRUCECL_MK3SHARED_EXPORT TcpClient : public QObject, public IConnection
{
    Q_OBJECT
    Q_INTERFACES(IConnection)
public:
    explicit TcpClient(QObject *parent = 0);

signals:
    void connectionStatusChanged (ConnectionStatus);
    void receivedInstruction     (Instruction);
    void message                 (MessageType, QString, QString = "TcpClient");

public slots:
    void closeConnection    ();
    void sendInstruction    (Instruction);

        void openConnection (QString, QString);
        void sendImage      (QString);

private slots:
    void connected          ();
    void disconnected       ();
    void readyRead          ();

        void emitInternalError  (QAbstractSocket::SocketError);

private:
    void send(const QByteArray &);

        QTcpSocket              *socket       {new QTcpSocket};
        TcpClientDataProcessor  dataProcessor {};
};

#endif // TCPCLIENT_H
