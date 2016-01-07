#include "tcpserverdataprocessor.h"

TcpServerDataProcessor::TcpServerDataProcessor(QObject *parent) : QObject(parent)
{}

void TcpServerDataProcessor::read(QByteArray data)
{
    if(containsEod(data))           //--jeżeli dane zawierają znak końca
    {
        switch (data.at(0))         //--spróbuj rozpoznać znak początku
        {
            case (char)Instruction::takePhoto:
                emit receivedInstruction(Instruction::takePhoto);
                break;
            case (char)Instruction::endScanning:
                emit receivedInstruction(Instruction::endScanning);
                break;
            case (char)DataType::image:         //--otrzymano zdjęcie w jednym pakiecie
                rawImages.push_back(data);      //--dodaj do kontenera nową paczkę danych
                removeBod(rawImages.last());    //--usuń znak początku
                createPhotogram();
                break;
            default:                        //--KONIEC ZDJĘCIA
                rawImages.last().push_back(data);   //--dodaj do kontenera
                createPhotogram();
                break;
        }
    }
    else
    {
        if(isImage(data))                   //--POCZĄTEK ZDJĘCIA
        {
            rawImages.push_back(data);              //--dodaj do kontenera nową paczkę danych
            removeBod(rawImages.last());            //--usuń znak początku
        }
        else                                //--ŚRODEK ZDJĘCIA
        {
            rawImages.last().push_back(data);       //--dodaj do kontenera
        }
    }
}
void TcpServerDataProcessor::angleChanged(float n)
{
    angle = n;
}
void TcpServerDataProcessor::removeOldestPhotogram()
{
    photograms.pop_front();
}

bool TcpServerDataProcessor::isImage(QByteArray &data)
{
    return data.at(0) ==(char)DataType::image;
}
void TcpServerDataProcessor::createPhotogram()
{
    removeEod(rawImages.last());                                //--usuń znak końca
    photograms.push_back(Photogram(rawImages.last(),angle));    //--stwórz photogram i dodaj do kontenera
    rawImages.clear();                                          //--wyczyść kontener w którym przechowywałeś surowe dane zdjęcia

    emit receivedInstruction(Instruction::takePhoto);
    emit receivedPhotogram(photograms.last());

    //wrzuć tutaj obsługę wyjątku gdyby coś miało pójść nie tak
}
