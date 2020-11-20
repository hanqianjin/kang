#-------------------------------------------------
#
# Project created by QtCreator 2019-01-25T09:05:19
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = F238SCPI
TEMPLATE = app

//INCLUDEPATH += ../libscpi/inc/
//LIBS += ../libscpi/dist/libscpi.a

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        f238scpi.cpp \
        libscpi/src/units.c\
        libscpi/src/utils.c\
        libscpi/src/debug.c\
        libscpi/src/error.c\
        libscpi/src/fifo.c\
        libscpi/src/ieee488.c\
        libscpi/src/minimal.c\
        libscpi/src/parser.c\
        scpidef/scpidef.cpp \
    localcommunicate.cpp \
    scpiport.cpp \
    scpiport_gpib.cpp \
    scpiport_internet.cpp \
    scpiport_uart.cpp \
    scpiport_usb.cpp \
    threadmsg.cpp \
    scpidef/scpidef_frequency.cpp
HEADERS += \
        f238scpi.h \
        libscpi/inc/scpi/config.h\
        libscpi/inc/scpi/constants.h\
        libscpi/inc/scpi/debug.h\
        libscpi/inc/scpi/error.h\
        libscpi/inc/scpi/fifo.h\
        libscpi/inc/scpi/ieee488.h\
        libscpi/inc/scpi/minimal.h\
        libscpi/inc/scpi/parser.h\
        libscpi/inc/scpi/scpi.h\
        libscpi/inc/scpi/types.h\
        libscpi/inc/scpi/units.h\
        libscpi/inc/scpi/utils_private.h\
        scpidef/scpidef.h \
    lib_usb.h \
    localcommunicate.h \
    scpiport.h \
    scpiport_gpib.h \
    scpiport_internet.h \
    scpiport_uart.h \
    scpiport_usb.h \
    threadmsg.h \
    type.h \
    scpidef/scpidef_frequency.h
FORMS += \
        f238scpi.ui \

