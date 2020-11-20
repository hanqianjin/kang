CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(bitsaplugin)
TEMPLATE    = lib

HEADERS     = bitsaplugin.h
SOURCES     = bitsaplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L.
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
#QMAKE_CXXFLAGS += -g
#QMAKE_CFLAGS += -g
INCLUDEPATH += /home/bqs/sbq/SA_RTSA/filemanager
#greaterThan(QT_MAJOR_VERSION, 4) {
#    QT += designer
#} else {
#    CONFIG += designer
#}

#DEFINES += QT_NO_DEBUG_OUTPUT
#DEFINES += QT_NO_WARNING_OUTPUT

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(bitsa.pri)

greaterThan(QT_MAJOR_VERSION, 4){
 QT += widgets
 TARGET_ARCH=$${QT_ARCH}
}else{
 TARGET_ARCH=$${QMAKE_HOST.arch}
}

contains(TARGET_ARCH, x86_64) {
LIBS += -L/home/bqs/sbq/SA_RTSA/filemanager/output -lsafilemanagerplugin
}else {
LIBS += -L/home/bqs/sbq/SA_RTSA/filemanager/arm_output -lsafilemanagerplugin
}
FORMS +=
