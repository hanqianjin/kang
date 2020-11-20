#ifndef SCPIPORT_GPIB_H
#define SCPIPORT_GPIB_H

#include <QSocketNotifier>
#include "scpiport.h"
#include <QSettings>
#include <QThread>

#define GPIB_SETTING_NODE "/sys/bus/platform/device/f260_misc_tty6/gpib_addr"
#define  SETTING_GPIB_ADRESS "SYS/GPIB_Address"

class ScpiPort_gpib : public ScpiPort_common
{
    Q_OBJECT
public:
    explicit ScpiPort_gpib(QObject *parent = 0);

    void * getUserContext(){
        return (void *)this;
    }
    void closeConn();
    void lostConn();
    void write(QByteArray buf);
    void acceptGpibInit();
public slots:
    void slotAcceptConnection();
    void slotReadgpibConnected();
    void slotReadData(int socket);//读取设备文件数据
    void slotRestConn();
public:
    const char *gpib_device_path;
private:
    QFile       m_gpib;
    quint16     m_port;
    bool        m_valid;
    QSocketNotifier *notifier;
    QSettings   m_setting;
};









#endif // SCPIPORT_GPIB_H
