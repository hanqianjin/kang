#ifndef SCPIPORT_UART_H
#define SCPIPORT_UART_H

#include "scpiport.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#define  SETTING_RS232_COMNUMBER   "SYS/RS232_ComNumber"
#define  SETTING_RS232_BAUDRATE    "SYS/RS232_BaudRate"
#define  SETTING_RS232_DATABIT     "SYS/RS232_Databit"
#define  SETTING_RS232_STOPBIT     "SYS/RS232_Stopbit"
#define  SETTING_RS232_PARITY      "SYS/RS232_Parity"
#define  SETTING_RS232_FLOWCTRL    "SYS/RS232_Flowctrl"
#define  SETTING_RS232_USBSERIAL   "SYS/USBSerial"

class ScpiPort_uart : public ScpiPort_common
{
    Q_OBJECT
public:
    explicit ScpiPort_uart(QObject *parent = 0);
    void * getUserContext(){
        return (void *)&m_uart;
    }
    void closeConn();
    void lostConn();
signals:

public slots:
    void slotAcceptConnection();
    void slotReadUartConnected();
    void handleError(QSerialPort::SerialPortError e);
    void slotRestConn();

private:
    QSerialPort m_uart;
    QSettings   m_setting;
    quint16     m_port;
    QByteArray  m_cmdBuffer;
    //真为SCPI模式,假如为文件传输
    bool        m_modeScpi;
    QString     m_fileName;
    int         m_fileLen;
    int         m_byte_readed;
};






#endif // SCPIPORT_UART_H
