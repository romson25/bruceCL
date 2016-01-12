#ifndef USBPORTDATAPROCESSOR_H
#define USBPORTDATAPROCESSOR_H

#include "DataProcessor/dataprocessorbase.h"

class UsbPortDataProcessor : public QObject, public DataProcessorBase
{
    Q_OBJECT
public:
    explicit UsbPortDataProcessor(QObject *parent = 0);

    void read(QByteArray data);
    QByteArray prepareConfiguration(float motorStepsNumber);

signals:
    void receivedInstruction (Instruction);
    void message (MessageType, QString, QString = "UsbPortDataProcessor");
};

#endif // USBPORTDATAPROCESSOR_H
