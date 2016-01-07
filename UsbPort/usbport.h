#ifndef USBPORT_H
#define USBPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QAbstractSocket>

#include "Connection/iconnection.h"
#include "usbportdataprocessor.h"
#include "brucecl_global.h"

class BRUCECL_MK3SHARED_EXPORT UsbPort : public QObject
{
    Q_OBJECT
public:
    explicit UsbPort(QObject *parent = 0);

signals:
    void connectionStatusChanged    (ConnectionStatus);
    void receivedInstruction        (Instruction);
    void message                    (MessageType, QString, QString = "UsbPort");

public slots:
    void closeConnection     ();
    void sendInstruction     (Instruction);

        void setRotateNumber (float);
        void openConnection  ();

private slots:
    void connected           ();
    void disconnected        ();
    void readyRead           ();

        void emitInternalError  (QSerialPort::SerialPortError);

private:
    void send(const QByteArray &);

        QSerialPort          *arduino       {new QSerialPort};
        UsbPortDataProcessor dataProcessor  {};
};

#endif // USBPORT_H
