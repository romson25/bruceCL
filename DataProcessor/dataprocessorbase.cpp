#include "dataprocessorbase.h"

DataProcessorBase::DataProcessorBase()
{}

QByteArray DataProcessorBase::prepareInstruction(Instruction instruction)
{
    return (instruction == Instruction::takePhoto) ? takePhoto : endScanning;
}

void DataProcessorBase::removeBod(QByteArray &data)
{
    data.replace(0,1,"");
}
void DataProcessorBase::removeEod(QByteArray &data)
{
    data.chop(1);
}
bool DataProcessorBase::containsEod(QByteArray &data)
{
    return data.right(1) == eod;
}
