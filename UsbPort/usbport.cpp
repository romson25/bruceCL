#include "usbport.h"

UsbPort::UsbPort(QObject *parent) : QObject(parent)
{
    connect(arduino, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(emitInternalError(QSerialPort::SerialPortError)));
    connect(arduino, &QSerialPort::readyRead,   this, &UsbPort::readyRead);

    connect(&dataProcessor, &UsbPortDataProcessor::message,             this, &UsbPort::message);
    connect(&dataProcessor, &UsbPortDataProcessor::receivedInstruction, this, &UsbPort::receivedInstruction);
}

void UsbPort::closeConnection()
{
    arduino->close();
}
void UsbPort::sendInstruction(Instruction instruction)
{
    send(dataProcessor.prepareInstruction(instruction));
}

void UsbPort::setStepsMotorNumber(float n)
{
    send(dataProcessor.prepareConfiguration(n));
}
void UsbPort::openConnection()
{
    if(arduino->isOpen())
    {
        emit message(MessageType::log, "Próba ponownego otwarcie otwartego już portu");
        return;
    }

    foreach (QSerialPortInfo i, QSerialPortInfo::availablePorts())
    {
        if(i.manufacturer().contains("arduino"))
        {
            arduino->setPort(i);
            arduino->open(QIODevice::ReadWrite) ? connected() : disconnected();
            return;
        }
    }
    emit message(MessageType::warning, "Arduino nie jest podłączone do komputera");
}

void UsbPort::connected()
{
    emit connectionStatusChanged(ConnectionStatus::connected);
    emit message(MessageType::log, tr("Nawiązano połączenie"));
}
void UsbPort::disconnected()
{
    emit connectionStatusChanged(ConnectionStatus::disconnected);
    emit message(MessageType::log, tr("Połączenie zakończone"));
}
void UsbPort::readyRead()
{
    dataProcessor.read( arduino->readAll() );
}

void UsbPort::send(const QByteArray &data)
{
    arduino->write(data);
}
void UsbPort::emitInternalError(QSerialPort::SerialPortError errorType)
{
    int e = (int)errorType;
    QString error = QString::number(e);

    emit message(MessageType::internalError, error);
}
