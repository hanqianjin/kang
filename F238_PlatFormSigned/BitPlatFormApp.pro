#-------------------------------------------------
#
# Project created by QtCreator 2018-12-11T16:26:53
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BitPlatFormApp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS\          
           #QT_NO_DEBUG_OUTPUT
           #QT_MESSAGELOGCONTEXT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS +=  -L/home/bob/Documents/BitSaAnaView/output -lbitsaplugin \
         -L/home/bob/Documents/BitRtsaAnaView/output -lbitrtsaplugin \
         -L/home/bob/Documents/BitView/BitView/output -lbitviewplugin

INCLUDEPATH +=  /home/bob/Documents/BitSaAnaView \
                /home/bob/Documents/BitRtsaAnaView \
                /home/bob/Documents/BitView

SOURCES += \
        main.cpp \
        bitplatform.cpp \    
        shmengine.cpp \
        loadctrlrunparam.cpp \
        plusmode.cpp \
        setwid.cpp \
        comset.cpp \
        networkset.cpp \
        dsdtset.cpp \
        sysinfo.cpp \
        hswinfo.cpp \
        licemana.cpp \
        scpidef/scpidef.cpp \
        libscpi/src/debug.c \
        libscpi/src/error.c \
        libscpi/src/fifo.c \
        libscpi/src/ieee488.c \
        libscpi/src/minimal.c \
        libscpi/src/parser.c \
        libscpi/src/units.c \
        libscpi/src/utils.c \
        scpidef/sa_scpi_freq.cpp \
        scpidef/sa_scpi_amp.cpp \
        scpidef/sa_scpi_bw.cpp \
        scpidef/sa_scpi_sweep.cpp \
        scpidef/sa_scpi_trace.cpp \
        scpidef/sa_scpi_marker.cpp \
        multicommu/localcommunicate.cpp \
        multicommu/scpiport.cpp \
        multicommu/scpiport_gpib.cpp \
        multicommu/scpiport_internet.cpp \
        multicommu/scpiport_uart.cpp \
        multicommu/scpiport_usb.cpp \
        multicommu/threadmsg.cpp \
    remoteinterface.cpp \
    macrobus.cpp

HEADERS += \
        bitplatform.h \
        softbus.h \
        macrobus.h \
        loadctrlrunparam.h \
        shmengine.h \        
        plusmode.h \
        setwid.h \
        comset.h \
        networkset.h \
        dsdtset.h \
        sysinfo.h \
        hswinfo.h \
        licemana.h \
        libscpi/inc/scpi/config.h \
        libscpi/inc/scpi/constants.h \
        libscpi/inc/scpi/debug.h \
        libscpi/inc/scpi/error.h \
        libscpi/inc/scpi/fifo.h \
        libscpi/inc/scpi/ieee488.h \
        libscpi/inc/scpi/minimal.h \
        libscpi/inc/scpi/parser.h \
        libscpi/inc/scpi/scpi.h \
        libscpi/inc/scpi/types.h \
        libscpi/inc/scpi/units.h \
        libscpi/inc/scpi/utils_private.h \
        scpidef/scpidef.h \        
        scpidef/sa_scpi_freq.h \
        scpidef/sa_scpi_amp.h \
        scpidef/sa_scpi_bw.h \
        scpidef/sa_scpi_sweep.h \
        scpidef/sa_scpi_trace.h \
        scpidef/sa_scpi_marker.h \
        multicommu/lib_usb.h \
        multicommu/localcommunicate.h \
        multicommu/scpiport.h \
        multicommu/scpiport_gpib.h \
        multicommu/scpiport_internet.h \
        multicommu/scpiport_uart.h \
        multicommu/scpiport_usb.h \
        multicommu/threadmsg.h \
        multicommu/type.h \
    remoteinterface.h

FORMS += \
        bitplatform.ui \
        plusmode.ui \
        setwid.ui \
        comset.ui \
        networkset.ui \
        dsdtset.ui \
        sysinfo.ui \
        hswinfo.ui \
        licemana.ui

RESOURCES += \
    bitresources.qrc
