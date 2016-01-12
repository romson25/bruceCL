#include "tcpclientdataprocessor.h"

TcpClientDataProcessor::TcpClientDataProcessor(QObject *parent) : QObject(parent)
{}

const QByteArray& TcpClientDataProcessor::prepareImage(QString path)
{
    QFile image(path);

    if(!image.open(QFile::ReadOnly))
    {
        emit message(MessageType::criticalError, "Problem z otwarciem pliku ze zdjęciem");
        return NULL;
    }

    static QByteArray imageData{};
    imageData.clear();

    imageData = imageBod + image.readAll() + eod;

    return imageData;
}
void TcpClientDataProcessor::read(QByteArray data)
{
    if(data == takePhoto)
        emit receivedInstruction(Instruction::takePhoto);
    else if(data == endScanning)
        emit receivedInstruction(Instruction::endScanning);
    else
        emit message(MessageType::criticalError, "Problem z interpretacją otrzymanych danych");
}
