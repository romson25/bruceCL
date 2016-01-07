#ifndef TCPSERVERDATAPROCESSOR_H
#define TCPSERVERDATAPROCESSOR_H

#include "photogram.h"
#include "DataProcessor/dataprocessorbase.h"

class TcpServerDataProcessor : public QObject, public DataProcessorBase
{
    Q_OBJECT
public:
    explicit TcpServerDataProcessor(QObject *parent = 0);

    void read(QByteArray);

signals:
    void receivedPhotogram(Photogram&);
    void receivedInstruction(Instruction);
    void message (MessageType, QString, QString = "TcpClientDataProcessor");

public slots:
    void angleChanged(float);
    void removeOldestPhotogram();

private:
    bool isImage(QByteArray &);
    void createPhotogram();

    QVector<Photogram> photograms {};
    QVector<QByteArray> rawImages {};

    float angle {};
};

#endif // TCPSERVERDATAPROCESSOR_H
