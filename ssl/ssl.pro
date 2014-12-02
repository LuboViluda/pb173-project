TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
QT += network

SOURCES += main.cpp \
    Server.cpp

include(deployment.pri)
qtcAddDeployment()

