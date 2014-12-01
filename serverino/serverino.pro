TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt

QT += network
QT += widgets
QT += sql

SOURCES += main.cpp \
    ClientThread.cpp \
    Console.cpp \
    Server.cpp \
    ../LogFile/logfile.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ClientThread.h \
    Console.h \
    Server.h \
    ../LogFile/logfile.h \
    ../ProtocolMsg.h

