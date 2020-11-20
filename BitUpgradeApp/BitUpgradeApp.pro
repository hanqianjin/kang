#-------------------------------------------------
#
# Project created by QtCreator 2019-11-26T13:33:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BitGradeApp
TEMPLATE = app

QMAKE_CXXFLAGS += -g
QMAKE_CFLAGS += -g

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#LIBS +=  -L/home/bob/Documents/BitSaAnaView/arm_output -lbitsaplugin \
#     -L/home/bob/Documents/FileManaSys/arm_output -lsafilemanagerplugin \


#INCLUDEPATH +=   /home/bob/Documents/BitSaAnaView \
#                /home/bob/Documents/FileManaSys \

SOURCES += \
        main.cpp \
        bitupgrade.cpp \
    upaction.cpp

HEADERS += \
        bitupgrade.h \
    upaction.h

FORMS += \
        bitupgrade.ui
