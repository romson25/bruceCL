#ifndef MESSAGETYPE
#define MESSAGETYPE

enum class MessageType : char
{
    internalError = 'i',  //--błąd, problem wewnątrz klasy Qt
    receivedError = 'r',  //--błąd, problem otrzymany z UsbPort lub TcpClient
    warning       = 'w',  //--log ostrzegawczy powstały w mojej klasie
    criticalError = 'c',  //--błąd, który bezpośrednio wpływa na pracę programu
    log           = 'l'   //--informacje które zbieram do oceny pracy programu
};

#endif // MESSAGETYPE

