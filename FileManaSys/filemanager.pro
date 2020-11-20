CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(safilemanagerplugin)
TEMPLATE    = lib

HEADERS     = safilemanagerplugin.h
SOURCES     = safilemanagerplugin.cpp
RESOURCES   = \
    filemanagerIcons.qrc
LIBS        += -L. 

DEFINES += QT_NO_DEBUG_OUTPUT
#greaterThan(QT_MAJOR_VERSION, 4) {
#    QT += designer
#} else {
#    CONFIG += designer
#}
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(safilemanager.pri)
