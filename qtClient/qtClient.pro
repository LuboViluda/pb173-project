TEMPLATE = app
CONFIG += console
CONFIG += app_bundle
CONFIG += qt

QT += network
QT += widgets

SOURCES += main.cpp \
    Client.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Client.h

