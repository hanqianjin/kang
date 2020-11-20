CONFIG      += plugin debug
TARGET      = $$qtLibraryTarget(bitviewplugin)
TEMPLATE    = lib

DEFINES += BITVIEW_BUILD


HEADERS     = bitviewplugin.h
SOURCES     = bitviewplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L.
#greaterThan(QT_MAJOR_VERSION, 4) {
#    QT += designer
#} else {
#    CONFIG += designer
#}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(bitview.pri)
