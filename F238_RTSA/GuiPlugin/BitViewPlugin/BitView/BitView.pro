CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(bitviewplugin)
TEMPLATE    = lib

HEADERS     = bitviewplugin.h
SOURCES     = bitviewplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
#greaterThan(QT_MAJOR_VERSION, 4) {
#    QT += designer
#} else {
#    CONFIG += designer
#}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(bitview.pri)
