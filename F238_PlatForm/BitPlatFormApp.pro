#-------------------------------------------------
#
# Project created by QtCreator 2018-12-11T16:26:53
#
#-------------------------------------------------

QT       += core gui

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
    licemana.cpp

HEADERS += \
        bitplatform.h \
        softbus.h \
        macrobus.h \
        shmengine.h \
        loadctrlrunparam.h \
    plusmode.h \
    setwid.h \
    comset.h \
    networkset.h \
    dsdtset.h \
    sysinfo.h \
    hswinfo.h \
    licemana.h

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
