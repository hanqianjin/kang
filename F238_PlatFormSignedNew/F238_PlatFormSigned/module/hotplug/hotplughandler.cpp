/*********************************************************************
 * Copyright(c) 2014, 一诺仪器（中国）有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：hotplughandler.cpp
 * 概   要：
 *
 * 当前版本：V1.0.0
 * 作   者：王直豪
 * 完成日期：2017-8-15
 *
 * 修改版本：
 * 修改说明：
 * 修改作者：
 *
 ********************************************************************/
#include <QFile>
#include <QDir>
#include <QFileInfo>
//#include <QTest>
#if __linux__
#include <sys/stat.h>
#include <sys/statfs.h>
#endif

#include "hotplughandler.h"
//#include "globalDef.h"
//#include "../../common/MessageBox.h"
//#include "../../service/SysMsgHelper.h"

bool HotplugManager::isExist(External_Media_Type type)
{
    if (type == Media_Type_USB) {
        return m_usb.isExist();
    } else if (type == Media_Type_SD){
        return m_mmc.isExist();
    } else {
        return false;
    }
}

bool HotplugManager::isExistDev(External_Media_Type type)
{
	if (type == Media_Type_USB) {
		return m_usb.isExistDev();
	}
	else if (type == Media_Type_SD) {
		return m_mmc.isExistDev();
	}
	else {
		return false;
	}
}

bool HotplugManager::eject(External_Media_Type type)
{
    if (type == Media_Type_USB) {
        if (m_usb.ejectDevice()) {
            //WarningBox::instance()->showMessage(OUT_MEDIA_REMOVED, QT_TRANSLATE_NOOP("WarningBox","Tips"), true);

            emit sigDeviceStatusUpdated();
            return true;
        }
        return false;
    } else if (type == Media_Type_SD){
        if (m_mmc.ejectDevice()) {
            //WarningBox::instance()->showMessage(OUT_MEDIA_REMOVED, QT_TRANSLATE_NOOP("WarningBox","Tips"), true);

            emit sigDeviceStatusUpdated();
            return true;
        }
        return false;
    } else {
        return false;
    }
}

qreal HotplugManager::getPercent(External_Media_Type type)
{
    refreshMedia(type);
    if (type == Media_Type_USB) {
        return m_usb.getPercent();
    } else if (type == Media_Type_SD) {
        return m_mmc.getPercent();
    } else {
        return 0;
    }
}

qreal HotplugManager::getTotalSize(External_Media_Type type)
{
    if (type == Media_Type_USB) {
        return m_usb.getTotalSize();
    } else if (type == Media_Type_SD) {
        return m_mmc.getTotalSize();
    } else {
        return 0;
    }
}

qreal HotplugManager::getFreeSize(External_Media_Type type)
{
    refreshMedia(type);
    if (type == Media_Type_USB) {
        return m_usb.getFreeSize();
    } else if (type == Media_Type_SD) {
        return m_mmc.getFreeSize();
    } else {
        return 0;
    }
}

int HotplugManager::mount(External_Media_Type type, QString dev, QString format) 
{
    if (type == Media_Type_USB) {
        return m_usb.mount(dev,format);
    } else if (type == Media_Type_SD) {
        return m_mmc.mount(dev,format);
    } else {
        return false;
    }
}

int HotplugManager::umount(External_Media_Type type) 
{
    if (type == Media_Type_USB) {
        return m_usb.umount();
    } else if (type == Media_Type_SD) {
        return m_mmc.umount();
    } else {
        return false;
    }
}

QString HotplugManager::getDevice(External_Media_Type type)
{
    if (type == Media_Type_USB) {
        return m_usb.getDevice();
    } else if (type == Media_Type_SD) {
        return m_mmc.getDevice();
    } else {
        return "";
    }
}

qint64 HotplugManager::getMemoryFreeSize()
{
#ifdef __linux__
	QString memPath = "/";
	struct statfs sfs;
	qint64 free;
	if (::statfs(memPath.toStdString().data(), &sfs) == 0)
	{
		free = (qint64)sfs.f_bavail*(qint64)sfs.f_bsize / 1024 / 1024;
	}
	return free;
#endif // __arm
	return 0;
}

void HotplugManager::slotUsbDeviceAdd()
{
    //WarningBox::instance()->showMessage(MEDIA_USB_CONNECTED, QT_TRANSLATE_NOOP("WarningBox","Tips"), true);
}

void HotplugManager::slotUsbFormatUnrecognize()
{
   // WarningBox::instance()->showMessage(USB_RECOGNIZED_FAIL, QT_TRANSLATE_NOOP("WarningBox","Warning"), true);
}

void HotplugManager::slotMmcFormatUnrecognize()
{
   // WarningBox::instance()->showMessage(WRONG_FORMAT_MEDIA, QT_TRANSLATE_NOOP("WarningBox","Warning"), true);
}

void HotplugManager::onMediaConnectedFail()
{
    //WarningBox::instance()->showMessage(OUT_MEDIA_CONNECTED_FAIL, QT_TRANSLATE_NOOP("WarningBox", "Warning"), true);
}

void HotplugManager::slotUsbStorageUpdate(QString action,QString dev)
{
    if (action == "add") {
        if (m_usb.isExist()) {
            return;
        }

        if (m_usb.addDevice(dev)) {
            //WarningBox::instance()->showMessage(OUT_MEDIA_CONNECTED, QT_TRANSLATE_NOOP("WarningBox","Tips"), true);
            emit sigDeviceStatusUpdated();
        } else {
           // WarningBox::instance()->showMessage(OUT_MEDIA_CONNECTED_FAIL, QT_TRANSLATE_NOOP("WarningBox","Warning"), true);
        }
    } else if (action == "remove") {
        if (m_usb.removeDevice(dev)) {
            //WarningBox::instance()->showMessage(OUT_MEDIA_REMOVED_IMPROPERLY, QT_TRANSLATE_NOOP("WarningBox","Warning"), true);
            emit sigDeviceStatusUpdated();
        }
    }
}

void HotplugManager::slotMmcStorageUpdate(QString action,QString dev)
{
    if (action == "add" ) {
        if (m_mmc.isExist()) {
            return;
        }

        if (m_mmc.addDevice(dev)) {
            //WarningBox::instance()->showMessage(OUT_MEDIA_CONNECTED, QT_TRANSLATE_NOOP("WarningBox","Tips"), true);
            emit sigDeviceStatusUpdated();
        } else {
            //WarningBox::instance()->showMessage(OUT_MEDIA_CONNECTED_FAIL, QT_TRANSLATE_NOOP("WarningBox","Warning"), true);
        }
    } else if (action == "remove") {
        if (m_mmc.removeDevice(dev)) {
            //WarningBox::instance()->showMessage(OUT_MEDIA_REMOVED_IMPROPERLY, QT_TRANSLATE_NOOP("WarningBox","Warning"), true);
            emit sigDeviceStatusUpdated();
        }
    }
}

void HotplugManager::refreshMedia(External_Media_Type type)
{
    if (type == Media_Type_USB) {
        m_usb.reset();
    }
    if (type == Media_Type_SD) {
        m_mmc.reset();
    }
}

void HotplugManager::onMmcDeviceRemoved()
{
	qDebug() << "remove sd!";
}

void HotplugManager::onUsbDeviceRemoved()
{
	qDebug() << "remove usb!";
}

void HotplugManager::onSendSysCmdMsg(const QString &cmd)
{
    //MsgHelp msgHelp;
    //msgHelp.PostProcessMsg(FTP_SERVER_MODULE, SYS_MSG_CMD, 0, cmd.toLatin1());
    //QCoreApplication::processEvents();
    //QTest::qWait(300);
}

HotplugManager::HotplugManager(QObject *parent)
    : QObject(parent)
    , m_usb(Media_Type(Type_USB), this)
    , m_mmc(Media_Type(Type_SD), this)
    , m_watcher(this)
{
    connect(&m_usb,SIGNAL(sigFormatUnrecognized()),
            this, SLOT(slotUsbFormatUnrecognize()));
    connect(&m_mmc,SIGNAL(sigFormatUnrecognized()),
            this, SLOT(slotMmcFormatUnrecognize()));
    connect(&m_watcher,SIGNAL(sigUsbDeviceAdded()),
            this, SLOT(slotUsbDeviceAdd()));
    connect(&m_watcher,SIGNAL(sigUsbStorageUpdated(QString,QString)),
            this, SLOT(slotUsbStorageUpdate(QString,QString)));
    connect(&m_watcher,SIGNAL(sigMmcStorageUpdated(QString,QString)),
            this, SLOT(slotMmcStorageUpdate(QString,QString)));
    connect(&m_watcher,SIGNAL(sigtmcUsbDeviceRemoved()),this,SIGNAL(sigTmcUsbPlugOut()));
	connect(&m_usb, &HotplugDevice::mediaConnectedFail,this, &HotplugManager::onMediaConnectedFail);
	connect(&m_mmc, &HotplugDevice::mediaConnectedFail,this, &HotplugManager::onMediaConnectedFail);
	

	connect(&m_watcher, &HotplugWatcher::sigMmcDeviceRemoved,this, &HotplugManager::onMmcDeviceRemoved);
	connect(&m_watcher, &HotplugWatcher::sigUsbDeviceRemoved, this, &HotplugManager::onUsbDeviceRemoved);

	connect(&m_usb, &HotplugDevice::sendSysCmdMsg,this, &HotplugManager::onSendSysCmdMsg);
	connect(&m_mmc, &HotplugDevice::sendSysCmdMsg, this, &HotplugManager::onSendSysCmdMsg);

}
