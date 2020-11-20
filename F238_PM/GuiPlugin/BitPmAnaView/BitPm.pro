CONFIG      += plugin debug_and_release

TARGET      = $$qtLibraryTarget(bitpmplugin)
TEMPLATE    = lib
HEADERS     = \  
    bitpmplugin.h
SOURCES     = \  
    bitpmplugin.cpp

QT += serialport

RESOURCES   =   $$PWD/icons.qrc

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4){
 QT += widgets
 TARGET_ARCH=$${QT_ARCH}
}else{
 TARGET_ARCH=$${QMAKE_HOST.arch}
}

#-------------------------------------------------
# Windows
#-------------------------------------------------
win32 {
    #添加_CRT_SECURE_NO_WARNINGS定义，避免VC编译器关于fopen等应使用fopen_s的安全警告
    win32:DEFINES+=_CRT_SECURE_NO_WARNINGS
    #屏蔽C4819警告，需要注意的是，在.pro文件中定义的均为全局配置。
    QMAKE_CXXFLAGS+=/wd"4819" \
                    /wd"4244"

    #-------------------------------------------------
    # Windows Host x86
    #-------------------------------------------------
    contains(QMAKE_TARGET.arch,x86){
#              INCLUDEPATH += C:/example_3rdlib/x86/include
#              LIBS +=-LC:/example_3rdlib/x86/lib/
        win32:CONFIG(release, debug|release){
            LIBS += -L/home/songjinpeng/Desktop/ProgramFile/GaugeViewOutput -lbitgaugedialviewplugin \
                    -L/home/songjinpeng/Desktop/ProgramFile/FileManaOutput -lsafilemanagerplugin\
        }
        else:win32:CONFIG(debug, debug|release){
#                           LIBS +=-lexample_3rdlibd
        }
    }
    #-------------------------------------------------
    # Windows Host x64
    #-------------------------------------------------
    contains(QMAKE_TARGET.arch,x86_64){
#              INCLUDEPATH +=C:/example_3rdlib/x64/include
#              LIBS +=-LC:/example_3rdlib/x64/lib/
        win32:CONFIG(release, debug|release){
#                           LIBS +=-lexample_3rdlib
        }
        else:win32:CONFIG(debug, debug|release){
#                           LIBS +=-lexample_3rdlibd
        }
    }
}
#-------------------------------------------------
# Linux Host
#-------------------------------------------------
unix {
    #-------------------------------------------------
    # Linux Host x64
    #-------------------------------------------------
    contains(TARGET_ARCH, x86_64) {
        CONFIG(debug, debug|release){
            LIBS += -L/home/songjinpeng/Desktop/ProgramFile/GaugeViewOutput -lbitgaugedialviewplugin \
                    -L/home/songjinpeng/Desktop/ProgramFile/x64FileManaOutput -lsafilemanagerplugin
        }
        CONFIG(release, debug|release){
            LIBS += -L/home/songjinpeng/Desktop/ProgramFile/GaugeViewOutput -lbitgaugedialviewplugin \
                    -L/home/songjinpeng/Desktop/ProgramFile/x64FileManaOutput -lsafilemanagerplugin
        }
    }else {
    #-------------------------------------------------
    # Linux Host x86
    #-------------------------------------------------
        CONFIG(debug, debug|release){
            LIBS += -L/home/songjinpeng/Desktop/AtmFile/GaugeViewOutput -lbitgaugedialviewplugin \
                    -L/home/songjinpeng/Desktop/AtmFile/FileManaOutput -lsafilemanagerplugin
        }
        CONFIG(release, debug|release){
            LIBS += -L/home/songjinpeng/Desktop/AtmFile/GaugeViewOutput -lbitgaugedialviewplugin \
                    -L/home/songjinpeng/Desktop/AtmFile/FileManaOutput -lsafilemanagerplugin
        }
    }
}

INCLUDEPATH += $$PWD/../BitGaugeDialViewPlugin/BitGaugeDialView \
               $$PWD/../../../FileManaSys

#INCLUDEPATH += $$PWD/../BitViewPlugin/output/debug \
#               $$PWD/../../../FileManaSysOut/debug

#DEPENDPATH += $$PWD/../BitViewPlugin/output/debug \
#              $$PWD/../../../FileManaSysOut/debug


target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(bitpm.pri)

DISTFILES +=  

#//编译警告warning: unused parameter参数未使用
QMAKE_CXXFLAGS +=  -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable


CONFIG += console
