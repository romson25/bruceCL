#ifndef TCPSERVERDATAPROCESSOR_H
#define TCPSERVERDATAPROCESSOR_H

#include <QImage>
#include "DataProcessor/dataprocessorbase.h"

class TcpServerDataProcessor : public QObject, public DataProcessorBase
{
    Q_OBJECT
public:
    explicit TcpServerDataProcessor(QObject *parent = 0);

    void read(QByteArray);

signals:
    void receivedImage      (QImage&);
    void receivedInstruction(Instruction);
    void message            (MessageType, QString, QString = "TcpClientDataProcessor");

private:
    bool constainImageBod        (QByteArray &);
    void readImage          (QByteArray &);
    void createImageFromData();

    QImage image {};
    QByteArray rawImage {};
};

#endif // TCPSERVERDATAPROCESSOR_H
