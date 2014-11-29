TEMPLATE = app
CONFIG += console
CONFIG += app_bundle
CONFIG += qt
CONFIG += c++11

QT += network
QT += widgets

SOURCES += main.cpp \
    Client.cpp \
    Server.cpp \
    inputthread.cpp \
    polarSSL/aes.c \
    polarSSL/aesni.c \
    polarSSL/entropy.c \
    polarSSL/entropy_poll.c \
    polarSSL/padlock.c \
    polarSSL/sha256.c \
    polarSSL/sha512.c \
    polarSSL/ctr_drbg.c \
    polarSSL/timing.c \
    crypt.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Client.h \
    Server.h \
    inputthread.h \
    polarSSL/aes.h \
    polarSSL/aesni.h \
    polarSSL/config.h \
    polarSSL/ctr_drbg.h \
    polarSSL/entropy.h \
    polarSSL/entropy_poll.h \
    polarSSL/check_config.h \
    polarSSL/padloc.h \
    polarSSL/padlock.h \
    polarSSL/platform.h \
    polarSSL/sha256.h \
    polarSSL/sha512.h \
    polarSSL/timing.h \
    crypt.h

