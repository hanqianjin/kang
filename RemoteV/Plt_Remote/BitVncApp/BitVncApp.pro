#-------------------------------------------------
#
# Project created by QtCreator 2019-06-26T15:55:32
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BitVncApp
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


SOURCES += \
        main.cpp \
        bitvncapp.cpp \
    bitvnchandle.cpp \
    bitvncinterface.cpp \
    communication/bitvnc_internet.cpp \
    vnc_threadrefresh.cpp \
    app/vnc_remotelogin.cpp \
    communication/bitvnc_datahandling.cpp \


HEADERS += \
        bitvncapp.h \
    bitvnchandle.h \
    bitvncinterface.h \
    communication/bitvnc_internet.h \
    vnc_threadrefresh.h \
    app/vnc_remotelogin.h \
    communication/bitvnc_datahandling.h

FORMS += \
        bitvncapp.ui \
    app/vnc_remotelogin.ui
win32{
    INCLUDEPATH +=   \#/mnt/hgfs/work/F238_VNC/BitVncApp/app2/F238_PlatFormSigned \
                     E:\F238_VMarket\F238_VNC\BitVncApp\app2\BitSaAnaView \
                     E:\F238_VMarket\RemoteV\RTSA_Remote\RemoteGuiPlugin\BitViewPlugin\BitView \
                     E:\F238_VMarket\RemoteV\RTSA_Remote\RemoteGuiPlugin\RtsaRemoteView \
                     E:\F238_VMarket\FileManaSys \

    CONFIG(debug, debug|release){
        #debug
        LIBS +=  \#-L/mnt/hgfs/work/lib -lBitPlatFormApp \
                -LE:\F238_VMarket\RemoteV\SA_Remote\BitSaAnaView\outputWin\debug -lbitsaplugind \
                -LE:\F238_VMarket\FileManaSys\outputWin\debug -lsafilemanagerplugind \
                #-L/mnt/hgfs/work/F238_RTSA/GuiPlugin/BitRtsaAnaView/output -lbitrtsaplugin \
                #-L/mnt/hgfs/work/F238_RTSA/GuiPlugin/BitViewPlugin/output -lbitviewplugin \
                #-L/mnt/hgfs/work/FileManaSys/output -lsafilemanagerplugin \

    }
    else
    {
        #release
        LIBS +=  \#-L/mnt/hgfs/work/lib -lBitPlatFormApp \
                -LE:\F238_VMarket\RemoteV\SA_Remote\BitSaAnaView\outputWin\release -lbitsaplugin \
                -LE:\F238_VMarket\FileManaSys\outputWin\release -lsafilemanagerplugin \
                #-L/mnt/hgfs/work/F238_RTSA/GuiPlugin/BitRtsaAnaView/output -lbitrtsaplugin \
                #-L/mnt/hgfs/work/F238_RTSA/GuiPlugin/BitViewPlugin/output -lbitviewplugin \
                #-L/mnt/hgfs/work/FileManaSys/output -lsafilemanagerplugin \

    }
}

unix{
LIBS +=  \#-L/mnt/hgfs/work/lib -lBitPlatFormApp \
         -L/mnt/hgfs/work/RemoteV/SA_Remote/BitSaAnaView/outputLinux -lbitsaplugin \
         -L/mnt/hgfs/work/FileManaSys/output -lsafilemanagerplugin \
         #-L/mnt/hgfs/work/F238_RTSA/GuiPlugin/BitRtsaAnaView/output -lbitrtsaplugin \
         #-L/mnt/hgfs/work/F238_RTSA/GuiPlugin/BitViewPlugin/output -lbitviewplugin \
         #-L/mnt/hgfs/work/FileManaSys/output -lsafilemanagerplugin \



}

INCLUDEPATH +=   \#/mnt/hgfs/work/F238_VNC/BitVncApp/app2/F238_PlatFormSigned \
                 /mnt/hgfs/work/RemoteV/SA_Remote/BitSaAnaView \
                 /mnt/hgfs/work/FileManaSys \
                 /mnt/hgfs/work/RemoteV/RTSA_Remote/RemoteGuiPlugin/BitViewPlugin/BitView \
                 /mnt/hgfs/work/RemoteV/RTSA_Remote/RemoteGuiPlugin/RtsaRemoteView \
                # /mnt/hgfs/work/FileManaSys  \

RESOURCES += \
    icon.qrc

INCLUDEPATH += \
    $$PWD/app \
    $$PWD/communication \

#INCLUDEPATH +=   /mnt/hgfs/work/F238_SA/GuiPlugin/BitSaAnaView \
#                /mnt/hgfs/work/F238_RTSA/GuiPlugin/BitRtsaAnaView \
#                /mnt/hgfs/work/F238_RTSA/GuiPlugin/BitViewPlugin/BitView \
#                /mnt/hgfs/work/FileManaSys  \
#                /home/bob/Documents/LTE_Lib_V0.3.3/BitCustomSo_Pro \
#                /home/bob/Documents/LTE_Lib_V0.3.3/BitLteFDDSo_Pro \
#                /home/bob/Documents/LTE_Lib_V0.3.3/BitLteTDDSo_Pro \

#  platform
INCLUDEPATH += \
        platform/
SOURCES += \
        platform/bitplatform.cpp \
        platform/loadctrlrunparam.cpp \
        platform/plusmode.cpp \
        platform/setwid.cpp \
        platform/comset.cpp \
        platform/networkset.cpp \
        platform/dsdtset.cpp \
        platform/sysinfo.cpp \
        platform/licemana.cpp \
        platform/scpidef/scpidef.cpp \
        platform/libscpi/src/debug.c \
        platform/libscpi/src/error.c \
        platform/libscpi/src/fifo.c \
        platform/libscpi/src/ieee488.c \
        platform/libscpi/src/minimal.c \
        platform/libscpi/src/parser.c \
        platform/libscpi/src/units.c \
        platform/libscpi/src/utils.c \
        platform/scpidef/sa_scpi_freq.cpp \
        platform/scpidef/sa_scpi_amp.cpp \
        platform/scpidef/sa_scpi_bw.cpp \
        platform/scpidef/sa_scpi_sweep.cpp \
        platform/scpidef/sa_scpi_trace.cpp \
        platform/scpidef/sa_scpi_marker.cpp \
        platform/multicommu/localcommunicate.cpp \
        platform/multicommu/scpiport.cpp \
        platform/multicommu/scpiport_internet.cpp \
        platform/multicommu/scpiport_uart.cpp \
        platform/multicommu/scpiport_usb.cpp \
        platform/multicommu/threadmsg.cpp \
    platform/remoteinterface.cpp \
    platform/macrobus.cpp \
    platform/switmod.cpp \
    platform/scpidef/rtsa_scpi_freq.cpp \
    platform/scpidef/sa_scpi_limit.cpp \
    platform/scpidef/sa_scpi_trigger.cpp \
    platform/scpidef/sa_scpi_meas.cpp \
    platform/scpidef/rtsa_scpi_amp.cpp \
    platform/pltnotice.cpp \
    platform/filemana.cpp \
    platform/debugdia.cpp \
    platform/scpidef/sa_scpi_setup.cpp \
    platform/scpidef/rtsa_scpi_sweep.cpp \
    platform/scpidef/rtsa_scpi_bw.cpp \
    platform/scpidef/rtsa_scpi_trace.cpp \
    platform/scpidef/rtsa_scpi_marker.cpp \
    platform/scpidef/rtsa_scpi_limit.cpp \
    platform/scpidef/rtsa_scpi_display.cpp \
    platform/scpidef/rtsa_scpi_setup.cpp \
    platform/clicklabel.cpp \
    platform/pltdisthread.cpp \
    platform/focuslinedit.cpp \
    platform/plugin/smkeyboard.cpp \
    platform/plugin/iplineedit.cpp \
    platform/plugin/pltkeyboard.cpp \
    platform/module/wificonnect.cpp \
    platform/module/LinkList.c \
    platform/module/wireless.c \
    platform/plugin/timesetup.cpp \
    platform/plugin/pltcalendar.cpp

HEADERS += \
        platform/bitplatform.h \
        platform/softbus.h \
        platform/macrobus.h \
        platform/loadctrlrunparam.h \
        platform/plusmode.h \
        platform/setwid.h \
        platform/comset.h \
        platform/networkset.h \
        platform/dsdtset.h \
        platform/sysinfo.h \
        platform/licemana.h \
        platform/libscpi/inc/scpi/config.h \
        platform/libscpi/inc/scpi/constants.h \
        platform/libscpi/inc/scpi/debug.h \
        platform/libscpi/inc/scpi/error.h \
        platform/libscpi/inc/scpi/fifo.h \
        platform/libscpi/inc/scpi/ieee488.h \
        platform/libscpi/inc/scpi/minimal.h \
        platform/libscpi/inc/scpi/parser.h \
        platform/libscpi/inc/scpi/scpi.h \
        platform/libscpi/inc/scpi/types.h \
        platform/libscpi/inc/scpi/units.h \
        platform/libscpi/inc/scpi/utils_private.h \
        platform/scpidef/scpidef.h \
        platform/scpidef/sa_scpi_freq.h \
        platform/scpidef/sa_scpi_amp.h \
        platform/scpidef/sa_scpi_bw.h \
        platform/scpidef/sa_scpi_sweep.h \
        platform/scpidef/sa_scpi_trace.h \
        platform/scpidef/sa_scpi_marker.h \
        platform/multicommu/lib_usb.h \
        platform/multicommu/localcommunicate.h \
        platform/multicommu/scpiport.h \
        platform/multicommu/scpiport_internet.h \
        platform/multicommu/scpiport_uart.h \
        platform/multicommu/scpiport_usb.h \
        platform/multicommu/threadmsg.h \
        platform/multicommu/type.h \
    platform/remoteinterface.h \
    platform/switmod.h \
    platform/scpidef/rtsa_scpi_freq.h \
    platform/scpidef/sa_scpi_limit.h \
    platform/scpidef/sa_scpi_trigger.h \
    platform/scpidef/sa_scpi_meas.h \
    platform/scpidef/rtsa_scpi_amp.h \
    platform/pltnotice.h \
    platform/filemana.h \
    platform/debugdia.h \
    platform/scpidef/sa_scpi_setup.h \
    platform/scpidef/rtsa_scpi_sweep.h \
    platform/scpidef/rtsa_scpi_bw.h \
    platform/scpidef/rtsa_scpi_trace.h \
    platform/scpidef/rtsa_scpi_marker.h \
    platform/scpidef/rtsa_scpi_limit.h \
    platform/scpidef/rtsa_scpi_display.h \
    platform/scpidef/rtsa_scpi_setup.h \
    platform/clicklabel.h \
    platform/pltdisthread.h \
    platform/focuslinedit.h \
    platform/plugin/smkeyboard.h \
    platform/plugin/iplineedit.h \
    platform/plugin/pltkeyboard.h \
    platform/module/LinkList.h \
    platform/module/wificonnect.h \
    platform/module/wireless.h \
    platform/plugin/timesetup.h \
    platform/plugin/pltcalendar.h

FORMS += \
        platform/bitplatform.ui \
        platform/plusmode.ui \
        platform/setwid.ui \
        platform/comset.ui \
        platform/networkset.ui \
        platform/dsdtset.ui \
        platform/sysinfo.ui \
        platform/licemana.ui \
    platform/switmod.ui \
    platform/pltnotice.ui \
    platform/filemana.ui \
    platform/debugdia.ui \
    platform/dialog.ui \
    platform/plugin/smkeyboard.ui \
    platform/module/wificonnect.ui \
    platform/plugin/pltkeyboard.ui \
    platform/plugin/timesetup.ui \
    platform/plugin/pltcalendar.ui

RESOURCES += \
    platform/bitresources.qrc

