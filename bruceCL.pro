#-------------------------------------------------
#
# Project created by QtCreator 2015-10-23T21:23:56
#
#-------------------------------------------------

QT += network
QT += serialport

TARGET   = bruceCL
TEMPLATE = lib
CONFIG  += c++11

DEFINES += BRUCECL_LIBRARY

SOURCES += \
    DataProcessor/dataprocessorbase.cpp \
    TcpServer/tcpserver.cpp \
    TcpServer/tcpserverdataprocessor.cpp \
    UsbPort/usbport.cpp \
    UsbPort/usbportdataprocessor.cpp \
    TcpClient/tcpclient.cpp \
    TcpClient/tcpclientdataprocessor.cpp

HEADERS +=\
        brucecl_global.h \
    Connection/connectionstatus.h \
    Connection/iconnection.h \
    DataProcessor/datatype.h \
    DataProcessor/messagetype.h \
    DataProcessor/instruction.h \
    DataProcessor/dataprocessorbase.h \
    TcpServer/tcpserver.h \
    TcpServer/tcpserverdataprocessor.h \
    TcpClient/tcpclient.h \
    TcpClient/tcpclientdataprocessor.h \
    UsbPort/usbport.h \
    UsbPort/usbportdataprocessor.h \
    brucecl_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_imgcodecs
