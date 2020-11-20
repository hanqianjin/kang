#ifndef TESTUSB_H
#define TESTUSB_H

#include <QObject>
#include <QThread>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <strings.h>
#include <string.h>
#include <signal.h>
#include "module/hotplug/hotplughandler.h"

enum{
     USB_TEST_STOP = 0,
     USB_TEST_START,
};
class testUSB : public QThread
{
     Q_OBJECT
public:
    testUSB();
    void setTestStatus(qint32 status);
    qint32 getTestStatus();

    int getUSBstatus();
protected:
    void run();
private slots:
    void on_DeviceStatusUpdated();
private:
    qint32 ConditionFlag;
    QString AnalysisSpeed();
signals:
    void testOnce(QString wSpeed,QString rSpeed);
    void StatusUpdated(qint32);
};

#endif // TESTUSB_H
