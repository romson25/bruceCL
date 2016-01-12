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

    void removeBod  (QByteArray &);
    void removeEod  (QByteArray &);
    bool containEod (QByteArray &);

    const QByteArray special    {"<>-!-<>\n"};
    const QByteArray eod        {"k"+special};

    const QByteArray imageBod           { (char)DataType::image         + special };
    const QByteArray unknownBod         { (char)DataType::unknown       + special };
    const QByteArray configurationBod   { (char)DataType::configuration + special };

    const QByteArray takePhoto          { (char)Instruction::takePhoto  + special };
    const QByteArray endScanning        { (char)Instruction::endScanning+ special };

    const int eodLength { eod.length() };
    const int bodLength { imageBod.length() };
};

#endif // DATAPROCESSORBASE_H
