#include "dataprocessorbase.h"

DataProcessorBase::DataProcessorBase()
{}

QByteArray DataProcessorBase::prepareInstruction(Instruction instruction)
{
    return (instruction == Instruction::takePhoto) ? takePhoto : endScanning;
}

void DataProcessorBase::removeBod   (QByteArray &data)
{
    data.replace(0, bodLength, "");
}
void DataProcessorBase::removeEod   (QByteArray &data)
{
    data.chop(eodLength);
}
bool DataProcessorBase::containEod  (QByteArray &data)
{
    return data.right(eodLength) == eod;
}
