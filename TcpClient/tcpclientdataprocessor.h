#ifndef TCPCLIENTDATAPROCESSOR_H
#define TCPCLIENTDATAPROCESSOR_H

#include "QFile"

#include "DataProcessor/dataprocessorbase.h"

class TcpClientDataProcessor : public QObject, public DataProcessorBase
{
    Q_OBJECT
public:
    explicit TcpClientDataProcessor(QObject *parent = 0);

    const QByteArray& prepareImage(QString path);
    void read(QByteArray);

signals:
    void receivedInstruction (Instruction);
    void message (MessageType, QString, QString = "TcpClientDataProcessor");
};

#endif // TCPCLIENTDATAPROCESSOR_H
