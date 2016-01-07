#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    connect(socket, &QTcpSocket::connected,     this,   &TcpClient::connected);
    connect(socket, &QTcpSocket::disconnected,  this,   &TcpClient::disconnected);
    connect(socket, &QTcpSocket::readyRead,     this,   &TcpClient::readyRead);

    connect(&dataProcessor, &TcpClientDataProcessor::message,               this, &TcpClient::message);
    connect(&dataProcessor, &TcpClientDataProcessor::receivedInstruction,   this, &TcpClient::receivedInstruction);

    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(emitInternalError(QAbstractSocket::SocketError)));
}

void TcpClient::closeConnection()
{
    socket->close();
}
void TcpClient::sendInstruction(Instruction instruction)
{
    send(dataProcessor.prepareInstruction(instruction));
}

void TcpClient::openConnection(QString ip, QString port)
{
    socket->connectToHost(ip,port.toInt());

    if(!socket->waitForConnected(3000))
        emit message(MessageType::warning, "Minął czas oczekiwania na połączenie");
}
void TcpClient::sendImage(QString path)
{
    send(dataProcessor.prepareImage(path));
}

void TcpClient::connected()
{
    emit connectionStatusChanged(ConnectionStatus::connected);
    emit message(MessageType::log, "Nawiązano połączenie");
}
void TcpClient::disconnected()
{
    emit connectionStatusChanged(ConnectionStatus::disconnected);
    emit message(MessageType::log, "Połączenie zakończone");
}
void TcpClient::readyRead()
{
    dataProcessor.read(socket->readAll());
}

void TcpClient::send(const QByteArray &data)
{
    socket->write(data);
}
void TcpClient::emitInternalError(QAbstractSocket::SocketError errorType)
{
    int e = (int)errorType;
    QString error = QString::number(e);

    emit message(MessageType::internalError, error);
}
