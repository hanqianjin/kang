#ifndef SCPIPORT_USB_H
#define SCPIPORT_USB_H

#include <QSocketNotifier>
#include "scpiport.h"
#include <QThread>



class ScpiPort_usb : public ScpiPort_common
{
    Q_OBJECT
public:
    explicit ScpiPort_usb(QObject *parent = 0);

    void * getUserContext(){
        return (void *)this;
    }
    void write(QByteArray buf);
    bool getUsbValid();
    void closeConn();
    void lostConn();
    void acceptUSBInit();
public slots:
    void slotAcceptConnection();
    void slotReadUsbConnected();
    void slotReadData(int socket);//读取设备文件数据
    void slotRestConn();


private:
    const char *usb_device_path;
    QFile       m_usb;
    quint16     m_port;
    QByteArray  m_cmdBuffer;
    bool        m_valid;
    QSocketNotifier *notifier;
};



#endif // SCPIPORT_USB_H
