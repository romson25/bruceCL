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
}
QByteArray UsbPortDataProcessor::prepareConfiguration(float rotateNumber)
{
    QByteArray bod{1, (char)DataType::configuration};
    QByteArray content = QByteArray::number(rotateNumber);

    return bod + content + eod;
}
