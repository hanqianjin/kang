CONFIG      += plugin debug_and_release

TARGET      = $$qtLibraryTarget(rtsaremoteplugin)
TEMPLATE    = lib

HEADERS     =   rtsaremoteplugin.h
SOURCES     =   rtsaremoteplugin.cpp


RESOURCES   =   icons.qrc

greaterThan(QT_MAJOR_VERSION, 4){
 QT += widgets
 TARGET_ARCH=$${QT_ARCH}
}else{
 TARGET_ARCH=$${QMAKE_HOST.arch}
}

#linux-g++*{
#contains(TARGET_ARCH, x86_64) {
#LIBS += -LF:/File_Exchange/QT_Work/F238_VMarket/RemoteV/RTSA_Remote/RemoteGuiPlugin/BitViewPlugin/output/debug  -lbitviewplugin \
#        -L/home/songjinpeng/Desktop/ProgramFile/FileManaOutput -lsafilemanagerplugin
#}else {
#LIBS += -LF:/File_Exchange/QT_Work/F238_VMarket/RemoteV/RTSA_Remote/RemoteGuiPlugin/BitViewPlugin/output/debug -lbitviewplugin \
#        -L/mnt/hgfs/File_Exchange/QT_Work/F238_VMarket/FileManaArmOutput -lsafilemanagerplugin
#}
#INCLUDEPATH += F:/File_Exchange/QT_Work/F238_VMarket/RemoteV/RTSA_Remote/RemoteGuiPlugin/BitViewPlugin/BitView \
#               /mnt/hgfs/svn/FileManaSys

#}


#}

#Windows的方法
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../BitViewPlugin/output/release/ -lbitviewplugin \
                                              -L$$PWD/../../../../FileManaSysOut/release/ -lsafilemanagerplugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../BitViewPlugin/output/debug/ -lbitviewplugind \
                                                 -L$$PWD/../../../../FileManaSysOut/debug/ -lsafilemanagerplugind
else:unix: LIBS += -L$$PWD/../BitViewPlugin/output/ -lbitviewplugin \
                   -L$$PWD/../../../../../FileManaSysOut/ -lsafilemanagerplugin


INCLUDEPATH += $$PWD/../BitViewPlugin/BitView \
               $$PWD/../../../../FileManaSys

INCLUDEPATH += $$PWD/../BitViewPlugin/output/debug \
               $$PWD/../../../../FileManaSysOut/debug

DEPENDPATH += $$PWD/../BitViewPlugin/output/debug \
              $$PWD/../../../../FileManaSysOut/debug


greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(rtsaremote.pri)

DISTFILES +=  rtsaremote.pri

#//编译警告warning: unused parameter参数未使用
QMAKE_CXXFLAGS +=  -Wno-unused-parameter
