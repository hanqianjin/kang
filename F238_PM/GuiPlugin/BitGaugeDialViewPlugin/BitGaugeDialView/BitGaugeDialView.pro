CONFIG      += plugin debug
TARGET      = $$qtLibraryTarget(bitgaugedialviewplugin)
TEMPLATE    = lib

DEFINES += BITVIEW_BUILD


QMAKE_CXXFLAGS += -std=c++11


HEADERS     = \
    bitgaugedialviewplugin.h
SOURCES     = \
    bitgaugedialviewplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L.

#greaterThan(QT_MAJOR_VERSION, 4) {
#    QT += designer
#} else {
#    CONFIG += designer
#}

greaterThan(QT_MAJOR_VERSION, 4){
 QT += widgets
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(bitgaugedialview.pri)

CONFIG += console
