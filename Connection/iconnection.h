#ifndef ICONNECTION
#define ICONNECTION

#include <QObject>

#include "connectionstatus.h"
#include "DataProcessor/instruction.h"
#include "DataProcessor/messagetype.h"

class IConnection
{
public:
    virtual ~IConnection(){}

//_signals:
    virtual void connectionStatusChanged(ConnectionStatus)  = 0;
    virtual void receivedInstruction(Instruction)           = 0;
    virtual void message(MessageType, QString, QString)     = 0;

//_public slots:
    virtual void closeConnection()              = 0;
    virtual void sendInstruction(Instruction)   = 0;

//_private slots:
    virtual void connected()    = 0;
    virtual void disconnected() = 0;
    virtual void readyRead()    = 0;

//_private:
    virtual void send(const QByteArray &)  = 0;
};

Q_DECLARE_INTERFACE(IConnection,"com.bruceCL.IConnection/1.0")

#endif // ICONNECTION
