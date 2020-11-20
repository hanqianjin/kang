CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(bitsaplugin)
TEMPLATE    = lib

HEADERS     = bitsaplugin.h
SOURCES     = bitsaplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L.
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
debug{
    QMAKE_CXXFLAGS += -g
    QMAKE_CFLAGS += -g
}
#greaterThan(QT_MAJOR_VERSION, 4) {
#    QT += designer
#} else {
#    CONFIG += designer
#}
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
#for linux
unix{
  INCLUDEPATH += /mnt/hgfs/work/FileManaSys
  LIBS += -L/mnt/hgfs/work/FileManaSys/output -lsafilemanagerplugin
}
#for windows
win32{
    INCLUDEPATH += E:\F238_VMarket\FileManaSys \

    CONFIG(debug, debug|release){
        #debug
            LIBS += -LE:\F238_VMarket\FileManaSys\outputWin\debug -lsafilemanagerplugind \

    }
    else
    {
        #release
            LIBS += -LE:\F238_VMarket\FileManaSys\outputWin\release -lsafilemanagerplugin \

    }
}
FORMS +=
