#-------------------------------------------------
#
# Project created by QtCreator 2018-05-22T13:21:52
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HomeApp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TRANSLATIONS+=bithomechina.ts \
              bithomeenglish.ts

SOURCES += \
        main.cpp \
        rsahala.cpp \
        runstateshm.cpp \
        modethread.cpp

HEADERS += \
        rsahala.h \
        RunStateShm.h \
        runstateshm.h \
        modethread.h \
        homesoftbus.h

FORMS += \
        rsahala.ui

RESOURCES += \  
    bitresource.qrc

DISTFILES += \
    Image/home/btn_5g.png \
    Image/home/btn_interfere.png \
    Image/home/btn_lte_ftt.png \
    Image/home/btn_lte_tdd.png \
    Image/home/btn_pm.png \
    Image/home/btn_rtsa.png \
    Image/home/btn_sa.png \
    Image/home/btn_system.png \
    Image/home/logo_inno_white.png \
    Image/btn_5g.png \
    Image/btn_interfere.png \
    Image/btn_lte_ftt.png \
    Image/btn_lte_tdd.png \
    Image/btn_pm.png \
    Image/btn_rtsa.png \
    Image/btn_sa.png \
    Image/btn_system.png

