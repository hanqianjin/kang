#include "testusb.h"
#include <QFile>
#define ENTER_USBDIR "cd /tmp/USB"
#define WRITE_TEST   "(dd if=/dev/zero of=./largefile bs=8k count=1000)2>usbTest"
#define CLEAR_CACHES "sh -c \"sync && echo 3 > /proc/sys/vm/drop_caches\""
#define READ_TEST    "(dd if=./largefile of=/dev/null bs=8k)2>usbTest"

testUSB::testUSB():
    ConditionFlag(USB_TEST_STOP)
{
    connect(HotplugManager::instance(), SIGNAL(sigDeviceStatusUpdated()), this, SLOT(on_DeviceStatusUpdated()));
}

void testUSB::setTestStatus(qint32 status)
{
    ConditionFlag = status;
    this->start();
}

qint32 testUSB::getTestStatus()
{
    return ConditionFlag;
}

int testUSB::getUSBstatus()
{
    if (HotplugManager::instance()->isExistDev(Media_Type_USB))
    {
        return 1;
    }else
    {
        return 0;
    }
}

void testUSB::run()
{
    QString wSpeed,rSpeed;
    while(ConditionFlag)
    {
        if (!HotplugManager::instance()->isExistDev(Media_Type_USB))
        {
            ConditionFlag = 0;
            emit StatusUpdated(0);
            break;
        }
        system(ENTER_USBDIR);
        system(WRITE_TEST);
        wSpeed = AnalysisSpeed();
        system(CLEAR_CACHES);
        system(READ_TEST);
        rSpeed = AnalysisSpeed();
        emit testOnce(wSpeed,rSpeed);
        sleep(1);
    }
}

void testUSB::on_DeviceStatusUpdated()
{
    if (HotplugManager::instance()->isExistDev(Media_Type_USB))  //USB存在
    {
        emit StatusUpdated(1);
    }
    else
    {
        emit StatusUpdated(0);
    }
}

QString testUSB::AnalysisSpeed()
{
    QString strSpeed,buf;
    qint32 index;
    QFile mfile("usbTest");
    if(!mfile.open(QIODevice::ReadOnly))
    {
        strSpeed ="";
        return strSpeed;
    }
    buf = mfile.readAll();
    mfile.close();
    if(buf.contains("s,"))
    {
        index = buf.indexOf("s,")+2;
        strSpeed = buf.right(buf.size() - (index+1));
        strSpeed = strSpeed.split('\n').first();
    }
    return strSpeed;
}
