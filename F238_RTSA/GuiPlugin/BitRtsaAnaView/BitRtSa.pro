CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(bitrtsaplugin)
TEMPLATE    = lib

HEADERS     = bitrtsaplugin.h
SOURCES     = bitrtsaplugin.cpp
RESOURCES   = icons.qrc
QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
QMAKE_CXXFLAGS += -Wno-sign-compare
QMAKE_CXXFLAGS += -Wno-comment
greaterThan(QT_MAJOR_VERSION, 4){
 QT += widgets
 TARGET_ARCH=$${QT_ARCH}
}else{
 TARGET_ARCH=$${QMAKE_HOST.arch}
}
contains(TARGET_ARCH, x86_64) {
LIBS += -L/home/bqs/sbq/SA_RTSA/RTSA_sf/GuiPlugin/BitViewPlugin/output -lbitviewplugin \
        -L/home/bqs/sbq/SA_RTSA/filemanager/output -lsafilemanagerplugin
}else {
LIBS += -L/home/bqs/sbq/SA_RTSA/RTSA_sf/GuiPlugin/BitViewPlugin/arm_output -lbitviewplugin \
        -L/home/bqs/sbq/SA_RTSA/filemanager/arm_output -lsafilemanagerplugin
}
INCLUDEPATH += /home/bqs/sbq/SA_RTSA/RTSA_sf/GuiPlugin/BitViewPlugin/BitView \
               /home/bqs/sbq/SA_RTSA/filemanager

#greaterThan(QT_MAJOR_VERSION, 4) {
#    QT += designer
#} else {
#    CONFIG += designer
#}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(bitrtsa.pri)
