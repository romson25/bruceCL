#ifndef DATAPROCESSORBASE_H
#define DATAPROCESSORBASE_H

#include <QObject>
#include <QDebug>

#include "DataProcessor/instruction.h"
#include "DataProcessor/datatype.h"
#include "DataProcessor/messagetype.h"

class DataProcessorBase
{
public:
    DataProcessorBase();

    QByteArray prepareInstruction(Instruction);

    void removeBod   (QByteArray &);
    void removeEod   (QByteArray &);
    bool containsEod (QByteArray &);

    const QByteArray eod        {"k"};
    const QByteArray takePhoto  {"tk"};
    const QByteArray endScanning{"ek"};
};

#endif // DATAPROCESSORBASE_H
