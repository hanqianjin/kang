#-------------------------------------------------
#
# Project created by QtCreator 2018-12-11T16:26:53
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += serialport


greaterThan(QT_MAJOR_VERSION, 4){
 QT += widgets
 TARGET_ARCH=$${QT_ARCH}
}else{
 TARGET_ARCH=$${QMAKE_HOST.arch}
}

TARGET = BitPlatFormApp
TEMPLATE = app

#QMAKE_CXXFLAGS += -g
#QMAKE_CFLAGS += -g

QMAKE_CXXFLAGS += -std=c++0x

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS\          
           QT_NO_DEBUG_OUTPUT
           #QT_MESSAGELOGCONTEXT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


##Johnson 20200317
contains(TARGET_ARCH, x86_64) {
LIBS +=  -L/home/bqs/sbq/SA_RTSA/SA_sf/BitSaAnaView/output -lbitsaplugin \
         -L/home/bqs/sbq/SA_RTSA/RTSA_sf/GuiPlugin/BitRtsaAnaView/output -lbitrtsaplugin \
         -L/home/bqs/sbq/SA_RTSA/RTSA_sf/GuiPlugin/BitViewPlugin/output -lbitviewplugin \
         -L/home/bqs/sbq/SA_RTSA/filemanager/output -lsafilemanagerplugin \
         -L/home/bqs/sbq/SA_RTSA/XA_sf/BitCustomSo_Pro/output -lbitcustomplugin \
         -L/home/bqs/sbq/SA_RTSA/XA_sf/BitLteFDDSo_Pro/output -lbitltefddplugin \
         -L/home/bqs/sbq/SA_RTSA/XA_sf/BitLteTDDSo_Pro/output -lbitltetddplugin \
         -L/home/bqs/sbq/SA_RTSA/XA_sf/BitNRSo_Pro/output -lbitnrplugin \
}else {
LIBS +=  -L/home/bqs/sbq/SA_RTSA/SA_sf/BitSaAnaView/arm_output -lbitsaplugin \
         -L/home/bqs/sbq/SA_RTSA/RTSA_sf/GuiPlugin/BitRtsaAnaView/arm_output -lbitrtsaplugin \
         -L/home/bqs/sbq/SA_RTSA/RTSA_sf/GuiPlugin/BitViewPlugin/arm_output -lbitviewplugin \
         -L/home/bqs/sbq/SA_RTSA/filemanager/arm_output -lsafilemanagerplugin \
         -L/home/bqs/sbq/SA_RTSA/XA_sf/BitCustomSo_Pro/arm_output -lbitcustomplugin \
         -L/home/bqs/sbq/SA_RTSA/XA_sf/BitLteFDDSo_Pro/arm_output -lbitltefddplugin \
         -L/home/bqs/sbq/SA_RTSA/XA_sf/BitLteTDDSo_Pro/arm_output -lbitltetddplugin \
         -L/home/bqs/sbq/SA_RTSA/XA_sf/BitNRSo_Pro/arm_output -lbitnrplugin \
}
contains(TARGET_ARCH, x86_64) {
INCLUDEPATH +=   /home/bqs/sbq/SA_RTSA/SA_sf/BitSaAnaView \
                /home/bqs/sbq/SA_RTSA/RTSA_sf/GuiPlugin/BitRtsaAnaView \
                /home/bqs/sbq/SA_RTSA/RTSA_sf/GuiPlugin/BitViewPlugin/BitView \
                /home/bqs/sbq/SA_RTSA/filemanager \
                /home/bqs/sbq/SA_RTSA/XA_sf/BitCustomSo_Pro \
                /home/bqs/sbq/SA_RTSA/XA_sf/BitLteFDDSo_Pro \
                /home/bqs/sbq/SA_RTSA/XA_sf/BitLteTDDSo_Pro \
                /home/bqs/sbq/SA_RTSA/XA_sf/BitNRSo_Pro \
}else {
INCLUDEPATH +=   /home/bqs/sbq/SA_RTSA/SA_sf/BitSaAnaView \
                /home/bqs/sbq/SA_RTSA/RTSA_sf/GuiPlugin/BitRtsaAnaView \
                /home/bqs/sbq/SA_RTSA/RTSA_sf/GuiPlugin/BitViewPlugin/BitView \
                /home/bqs/sbq/SA_RTSA/filemanager \
                /home/bqs/sbq/SA_RTSA/XA_sf/BitCustomSo_Pro \
                /home/bqs/sbq/SA_RTSA/XA_sf/BitLteFDDSo_Pro \
                /home/bqs/sbq/SA_RTSA/XA_sf/BitLteTDDSo_Pro \
                /home/bqs/sbq/SA_RTSA/XA_sf/BitNRSo_Pro \
}

SOURCES += \
        main.cpp \
        bitplatform.cpp \    
        shmengine.cpp \
        loadctrlrunparam.cpp \
        plusmode.cpp \
        setwid.cpp \
        comset.cpp \
        networkset.cpp \
        dsdtset.cpp \
        sysinfo.cpp \
        licemana.cpp \
        libscpi/src/debug.c \
        libscpi/src/error.c \
        libscpi/src/fifo.c \
        libscpi/src/ieee488.c \
        libscpi/src/minimal.c \
        libscpi/src/parser.c \
        libscpi/src/units.c \
        libscpi/src/utils.c \
        scpidef/sa_scpi_freq.cpp \
        scpidef/sa_scpi_amp.cpp \
        scpidef/sa_scpi_bw.cpp \
        scpidef/sa_scpi_sweep.cpp \
        scpidef/sa_scpi_trace.cpp \
        scpidef/sa_scpi_marker.cpp \
        multicommu/localcommunicate.cpp \
        multicommu/scpiport.cpp \
        multicommu/scpiport_internet.cpp \
        multicommu/scpiport_uart.cpp \
        multicommu/scpiport_usb.cpp \
        multicommu/threadmsg.cpp \
    remoteinterface.cpp \
    macrobus.cpp \
    switmod.cpp \
    scpidef/rtsa_scpi_freq.cpp \
    scpidef/sa_scpi_limit.cpp \
    scpidef/sa_scpi_trigger.cpp \
    scpidef/sa_scpi_meas.cpp \   
    scpidef/rtsa_scpi_amp.cpp \
    pltnotice.cpp \
    filemana.cpp \
    debugdia.cpp \
    scpidef/sa_scpi_setup.cpp \
    scpidef/rtsa_scpi_sweep.cpp \
    scpidef/rtsa_scpi_bw.cpp \
    scpidef/rtsa_scpi_trace.cpp \
    scpidef/rtsa_scpi_marker.cpp \
    scpidef/rtsa_scpi_limit.cpp \
    scpidef/rtsa_scpi_display.cpp \
    scpidef/rtsa_scpi_setup.cpp \
    bitapplication.cpp \
    clicklabel.cpp \
    pltdisthread.cpp \
    focuslinedit.cpp \
    plugin/smkeyboard.cpp \
    plugin/iplineedit.cpp \
    plugin/pltkeyboard.cpp \
    module/wificonnect.cpp \
    module/LinkList.c \
    module/wireless.c \
    plugin/timesetup.cpp \
    plugin/pltcalendar.cpp \
    excenoti.cpp \
    pltcirlist.cpp \
    noticmsg.cpp \
    msgNoticeCode.cpp \
    scpidef/rtsa_scpi_trigger.cpp \
    scpidef/scpidef.cpp \
    bitboard.cpp \
    module/testusb.cpp \
    module/hotplug/HotplugWatcher.cpp \
    module/hotplug/hotplughandler.cpp \
    scpidef/nr_scpi_amp.cpp \
    scpidef/nr_scpi_bw.cpp \
    scpidef/nr_scpi_freq.cpp \
    scpidef/nr_scpi_limit.cpp \
    scpidef/nr_scpi_marker.cpp \
    scpidef/nr_scpi_sweep.cpp \
    scpidef/nr_scpi_trace.cpp \
    scpidef/nr_scpi_meas.cpp \
    scpidef/fdd_scpi_amp.cpp \
    scpidef/fdd_scpi_bw.cpp \
    scpidef/fdd_scpi_freq.cpp \
    scpidef/fdd_scpi_limit.cpp \
    scpidef/fdd_scpi_marker.cpp \
    scpidef/fdd_scpi_meas.cpp \
    scpidef/fdd_scpi_sweep.cpp \
    scpidef/fdd_scpi_trace.cpp \
    scpidef/tdd_scpi_amp.cpp \
    scpidef/tdd_scpi_bw.cpp \
    scpidef/tdd_scpi_freq.cpp \
    scpidef/tdd_scpi_limit.cpp \
    scpidef/tdd_scpi_marker.cpp \
    scpidef/tdd_scpi_meas.cpp \
    scpidef/tdd_scpi_sweep.cpp \
    scpidef/tdd_scpi_trace.cpp \
    scpidef/autoproductcommand.cpp


HEADERS += \
        bitplatform.h \
        softbus.h \
        macrobus.h \
        loadctrlrunparam.h \
        shmengine.h \        
        plusmode.h \
        setwid.h \
        comset.h \
        networkset.h \
        dsdtset.h \
        sysinfo.h \
        licemana.h \
        libscpi/inc/scpi/config.h \
        libscpi/inc/scpi/constants.h \
        libscpi/inc/scpi/debug.h \
        libscpi/inc/scpi/error.h \
        libscpi/inc/scpi/fifo.h \
        libscpi/inc/scpi/ieee488.h \
        libscpi/inc/scpi/minimal.h \
        libscpi/inc/scpi/parser.h \
        libscpi/inc/scpi/scpi.h \
        libscpi/inc/scpi/types.h \
        libscpi/inc/scpi/units.h \
        libscpi/inc/scpi/utils_private.h \
        scpidef/scpidef.h \        
        scpidef/sa_scpi_freq.h \
        scpidef/sa_scpi_amp.h \
        scpidef/sa_scpi_bw.h \
        scpidef/sa_scpi_sweep.h \
        scpidef/sa_scpi_trace.h \
        scpidef/sa_scpi_marker.h \
        multicommu/lib_usb.h \
        multicommu/localcommunicate.h \
        multicommu/scpiport.h \
        multicommu/scpiport_internet.h \
        multicommu/scpiport_uart.h \
        multicommu/scpiport_usb.h \
        multicommu/threadmsg.h \
        multicommu/type.h \
    remoteinterface.h \
    switmod.h \
    scpidef/rtsa_scpi_freq.h \
    scpidef/sa_scpi_limit.h \
    scpidef/sa_scpi_trigger.h \
    scpidef/sa_scpi_meas.h \  
    scpidef/rtsa_scpi_amp.h \
    pltnotice.h \
    filemana.h \
    debugdia.h \
    scpidef/sa_scpi_setup.h \
    scpidef/rtsa_scpi_sweep.h \
    scpidef/rtsa_scpi_bw.h \
    scpidef/rtsa_scpi_trace.h \
    scpidef/rtsa_scpi_marker.h \
    scpidef/rtsa_scpi_limit.h \
    scpidef/rtsa_scpi_display.h \
    scpidef/rtsa_scpi_setup.h \
    bitapplication.h \
    clicklabel.h \
    pltdisthread.h \
    focuslinedit.h \
    plugin/smkeyboard.h \
    plugin/iplineedit.h \
    plugin/pltkeyboard.h \
    module/LinkList.h \
    module/wificonnect.h \
    module/wireless.h \
    plugin/timesetup.h \
    plugin/pltcalendar.h \
    excenoti.h \
    pltdictionary/pltsadiction.h \
    pltdictionary/pltrtsadiction.h \
    pltdictionary/pltiadiction.h \
    pltdictionary/pltpmdiction.h \
    pltdictionary/pltfdddiction.h \
    pltdictionary/plttdddiction.h \
    pltdictionary/pltfgnrdiction.h \
    pltdictionary/pltsysctrldiction.h \
    pltdictionary/plthomediction.h \
    pltcirlist.h \
    pltdictionary/pltdiction.h \
    noticmsg.h \
    msgNoticeCode.h \
    scpidef/rtsa_scpi_trigger.h \
    bitboard.h \
    module/testusb.h \
    module/hotplug/HotplugWatcher.h \
    module/hotplug/hotplughandler.h \
    scpidef/nr_scpi_amp.h \
    scpidef/nr_scpi_bw.h \
    scpidef/nr_scpi_freq.h \
    scpidef/nr_scpi_limit.h \
    scpidef/nr_scpi_marker.h \
    scpidef/nr_scpi_sweep.h \
    scpidef/nr_scpi_trace.h \
    scpidef/nr_scpi_meas.h \
    scpidef/fdd_scpi_amp.h \
    scpidef/fdd_scpi_bw.h \
    scpidef/fdd_scpi_freq.h \
    scpidef/fdd_scpi_limit.h \
    scpidef/fdd_scpi_marker.h \
    scpidef/fdd_scpi_meas.h \
    scpidef/fdd_scpi_sweep.h \
    scpidef/fdd_scpi_trace.h \
    scpidef/lte_scpi_def.h \
    scpidef/tdd_scpi_amp.h \
    scpidef/tdd_scpi_bw.h \
    scpidef/tdd_scpi_freq.h \
    scpidef/tdd_scpi_limit.h \
    scpidef/tdd_scpi_marker.h \
    scpidef/tdd_scpi_meas.h \
    scpidef/tdd_scpi_sweep.h \
    scpidef/tdd_scpi_trace.h \
    scpidef/autoproductcommand.h \
    dataconfig/ajson/ajson.hpp \
    dataconfig/ajson/ajson_msd.hpp \
    dataconfig/BaseData.h \
    dataconfig/ConfigData.h \
    dataconfig/Platform_def.h \
    dataconfig/SA_def.h


FORMS += \
        bitplatform.ui \
        plusmode.ui \
        setwid.ui \
        comset.ui \
        networkset.ui \
        dsdtset.ui \
        sysinfo.ui \
        licemana.ui \
    switmod.ui \
    pltnotice.ui \
    filemana.ui \
    debugdia.ui \
    plugin/smkeyboard.ui \
    module/wificonnect.ui \
    plugin/pltkeyboard.ui \
    plugin/timesetup.ui \
    plugin/pltcalendar.ui \
    noticmsg.ui \
    bitboard.ui

RESOURCES += \
    bitresources.qrc

DISTFILES += \
    dataconfig/ajson/README.md \
    dataconfig/ajson/LICENSE
