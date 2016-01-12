#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    connect(server, &QTcpServer::newConnection, this,   &TcpServer::newConnection);

    connect(&dataProcessor,  &TcpServerDataProcessor::message,              this,   &TcpServer::message);
    connect(&dataProcessor,  &TcpServerDataProcessor::receivedImage,        this,   &TcpServer::receivedImage);
    connect(&dataProcessor,  &TcpServerDataProcessor::receivedInstruction,  this,   &TcpServer::receivedInstruction);
}

void TcpServer::closeConnection ()
{
    socket->close();
    server->close();
}
void TcpServer::sendInstruction (Instruction instruction)
{
    send(dataProcessor.prepareInstruction(instruction));
}

void TcpServer::openConnection  ()
{
    if(!server->listen(QHostAddress::Any, 6850))
        emit message(MessageType::warning, "Użyty port jest już zajęty. Uruchom tylko jedną instacje programu");

    QHostAddress localhostIP{QHostAddress::LocalHost};

    quint16 portNumber{server->serverPort()};
    QString port{QString::number(portNumber)};

    foreach (QHostAddress availableIP, QNetworkInterface::allAddresses())
    {
        if(availableIP != localhostIP && availableIP.toIPv4Address())
        {
            QString ip(availableIP.toString());
            emit serverAddressChanged(ip, port);
            return;
        }
    }
    emit message(MessageType::criticalError, "Brak połączenia z internetem");
}

void TcpServer::connected       ()
{
    emit connectionStatusChanged(ConnectionStatus::connected);
    emit message(MessageType::log, "Nawiązano połączenie");
}
void TcpServer::disconnected    ()
{
    emit connectionStatusChanged(ConnectionStatus::disconnected);
    emit message(MessageType::log, "Połączenie zakończone");
}
void TcpServer::readyRead       ()
{
    while( socket->canReadLine() )
    {
        dataProcessor.read( socket->readLine() );
    }
}

void TcpServer::newConnection   ()
{
    socket = server->nextPendingConnection();

    connect(socket, &QTcpSocket::connected,     this,   &TcpServer::connected);
    connect(socket, &QTcpSocket::disconnected,  this,   &TcpServer::disconnected);
    connect(socket, &QTcpSocket::readyRead,     this,   &TcpServer::readyRead);
    
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(emitInternalError(QAbstractSocket::SocketError)));

    emit connectionStatusChanged(ConnectionStatus::connected);
}

void TcpServer::send(const QByteArray &data)
{
    socket->write(data);
}
void TcpServer::emitInternalError(QAbstractSocket::SocketError errorType)
{
    int e = (int)errorType;
    QString error = QString::number(e);

    emit message(MessageType::internalError, error);
}
