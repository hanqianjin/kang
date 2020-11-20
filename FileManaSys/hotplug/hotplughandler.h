/*********************************************************************
 * Copyright(c) 2014, 一诺仪器（中国）有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：hotplughandler.h
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

#ifndef HOTPLUGHANDLER_H
#define HOTPLUGHANDLER_H

#include <QObject>
#include <QDebug>
//#include "globalDef.h"
#include "HotplugWatcher.h"

/*扩展存储媒介*/
typedef enum External_Media_Type_Enum{
    Media_Type_USB,         //USB
    Media_Type_SD,          //SD卡
    Media_Type_Unknow,      //不能识别
}External_Media_Type;

class HotplugManager : public QObject
{
    Q_OBJECT
public:
    static HotplugManager* instance()
    {static HotplugManager obj; return &obj;}
	
	void start(){ qDebug() << "HotplugManager is running."; }
    //指定设备是否存在
    bool isExist(External_Media_Type type);

	bool isExistDev(External_Media_Type type);
    //弹出指定设备
    bool eject(External_Media_Type type);
    //指定存储设备已使用空间比例
    qreal getPercent(External_Media_Type type);
    //指定存储设备总存储空间，单位:Ｍ
    qreal getTotalSize(External_Media_Type type);
    //指定存储设备未使用存储空间，单位:Ｍ
    qreal getFreeSize(External_Media_Type type);
    QString getDevice(External_Media_Type type);

    qint64 getMemoryFreeSize();

    int mount(External_Media_Type type,QString dev, QString format) ;
    int umount(External_Media_Type type) ;

    void refreshMedia(External_Media_Type type);

signals:
    //设备状态更新时触发
    void sigDeviceStatusUpdated();

    void sigTmcUsbPlugIn();
    void sigTmcUsbPlugOut();
private slots:
    void slotUsbDeviceAdd();
    void slotUsbFormatUnrecognize();
    void slotMmcFormatUnrecognize();
	void onMediaConnectedFail();
    void slotUsbStorageUpdate(QString action,QString dev);
    void slotMmcStorageUpdate(QString action,QString dev);
	void onMmcDeviceRemoved();
	void onUsbDeviceRemoved();
	void onSendSysCmdMsg(const QString &cmd);

private:
    explicit HotplugManager(QObject *parent = 0);

private:
	HotplugWatcher m_watcher;
    HotplugDevice m_usb;
    HotplugDevice m_mmc;
};

#endif // HOTPLUGHANDLER_H
