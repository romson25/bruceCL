#include "usbportdataprocessor.h"

UsbPortDataProcessor::UsbPortDataProcessor(QObject *parent) : QObject(parent)
{}


void UsbPortDataProcessor::read(QByteArray data)
{
    static QByteArray receivedData{};
    receivedData += data;

    if(receivedData == takePhoto)
    {
        emit receivedInstruction(Instruction::takePhoto);
        receivedData.clear();
    }
    else if(receivedData == endScanning)
    {
        emit receivedInstruction(Instruction::endScanning);
        receivedData.clear();
    }
    //TODO:poprawić, napewno da się to napisać lepiej
}
QByteArray UsbPortDataProcessor::prepareConfiguration(float motorStepsNumber)
{
    QByteArray content = QByteArray::number(motorStepsNumber);
    QByteArray configuration { configurationBod + content + eod };

    return configuration;
}
