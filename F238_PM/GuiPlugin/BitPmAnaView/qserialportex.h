#ifndef QSERIALPORTEX_H
#define QSERIALPORTEX_H

#include <QObject>
#include <QComboBox>
#include <QSerialPort>
#include <QSerialPortInfo>

typedef struct
{
    QString strSerialPortname;  //串口名称
    QSerialPort::BaudRate nBaundRate;//设置波特率
    QSerialPort::DataBits nDataBits;//数据位
    QSerialPort::FlowControl nFlowControl;//流控制
    QSerialPort::Parity nParity;//校验位
    QSerialPort::StopBits nStopBits; //停止位

}__SERIAL_PORT_PARA__;

class QSerialPortEx : public QObject
{
    Q_OBJECT
public:
    explicit QSerialPortEx(QObject *parent = NULL);
    ~QSerialPortEx();
signals:
    void ReadComm(QByteArray commRecvData);
    void StopRecvData();
private slots:
    void receiveInfo();
public:

    bool IsOpenPort();
    void openPort(__SERIAL_PORT_PARA__ serialPortPara);
    void closePort();

    void sendInfo(char * info,int len);
    void sendInfo(QString &info);

    void connectPort();
    void clearSerialPort();

    QSerialPort* getSerialName();

private:
    __SERIAL_PORT_PARA__ m_serialPortPara;
    QSerialPort *m_serialPort;
};

#endif // QSERIALPORTEX_H
