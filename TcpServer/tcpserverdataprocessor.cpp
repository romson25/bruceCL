#include "tcpserverdataprocessor.h"

TcpServerDataProcessor::TcpServerDataProcessor  (QObject *parent) : QObject(parent)
{}

void TcpServerDataProcessor::read               (QByteArray data)
{
    if( data == takePhoto )
        emit receivedInstruction(Instruction::takePhoto);
    else if( data == endScanning )
        emit receivedInstruction(Instruction::endScanning);
    else
        readImage(data);
}

bool TcpServerDataProcessor::constainImageBod   (QByteArray &data)
{
    return data.left(bodLength) == imageBod;
}
void TcpServerDataProcessor::readImage          (QByteArray &data)
{
    if( containEod(data) )
    {
        if( constainImageBod(data) )    //--otrzymano zdjęcie w jednym pakiecie
        {
            rawImage = std::move(data);
            createImageFromData();

            emit receivedImage(image);
        }
        else                            //--KONIEC ZDJĘCIA
        {
            rawImage.push_back(std::move(data));
            createImageFromData();

            emit receivedImage(image);
        }
    }
    else
    {
        if( constainImageBod(data) )    //--POCZĄTEK ZDJĘCIA
            rawImage = std::move(data);
        else                            //--ŚRODEK ZDJĘCIA
            rawImage.push_back(std::move(data));
    }
}
void TcpServerDataProcessor::createImageFromData()
{
    removeBod(rawImage);
    removeEod(rawImage);
    image = QImage::fromData(rawImage, "JPG");
    rawImage.clear();

    //TODO: wrzuć tutaj obsługę wyjątku gdyby coś miało pójść nie tak
}
