#include "qserialportex.h"
#include<qdebug.h>
#include<unistd.h>
#include "data_conversion.h"


QSerialPortEx::QSerialPortEx(QObject *parent) : QObject(parent)
{
    m_serialPort = new QSerialPort();
}

QSerialPortEx::~QSerialPortEx()
{
    if (m_serialPort->isOpen())
       {
           m_serialPort->close();
       }
       delete m_serialPort;
}

/**
* @brief   关闭串口
* @note
* @author Roc
* @since  2019.11.12
*/
void QSerialPortEx::closePort()
{
    if(m_serialPort->isOpen())//如果串口已经打开了 给他关闭了
    {
        qDebug()<< m_serialPortPara.strSerialPortname <<"is close"<<endl;
        m_serialPort->clear();
        m_serialPort->close();
    }
}

/**
* @brief   打开串口
* @note
* @author Roc
* @since  2019.11.12
*/
void QSerialPortEx::openPort(__SERIAL_PORT_PARA__ serialPortPara)
{
    if(m_serialPort->isOpen())//如果串口已经打开了 先给他关闭了
    {
        qDebug()<< m_serialPortPara.strSerialPortname <<"is Opened"<<endl;
        m_serialPort->clear();
        m_serialPort->close();
    }
    m_serialPortPara = serialPortPara;

    //设置串口名字
    m_serialPort->setPortName(m_serialPortPara.strSerialPortname);

    if(!m_serialPort->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
    {
        qDebug()<< m_serialPortPara.strSerialPortname <<"Open Fail"<<endl;
        return;
    }

    //打开成功
    m_serialPort->setDataTerminalReady(true);
    m_serialPort->setBaudRate(m_serialPortPara.nBaundRate,QSerialPort::AllDirections);//设置波特率和读写方向
    m_serialPort->setDataBits(m_serialPortPara.nDataBits);		//数据位为8位
    m_serialPort->setFlowControl(m_serialPortPara.nFlowControl);//无流控制
    m_serialPort->setParity(m_serialPortPara.nParity);	//无校验位
    m_serialPort->setStopBits(m_serialPortPara.nStopBits); //一位停止位

    qDebug()<< "SerialPort inno "  << "\n" <<
               "Name        :" << m_serialPortPara.strSerialPortname  << "\n" <<
               "BaundRate   : "<<m_serialPortPara.nBaundRate <<"\n"<<
               "DataBits    :" <<m_serialPortPara.nDataBits <<"\n"<<
               "FlowControl :" <<m_serialPortPara.nFlowControl<<"\n"<<
               "Parity      :" <<m_serialPortPara.nParity<< "\n" <<
               "StopBits    :" <<m_serialPortPara.nStopBits<< "\n" <<
               "SerialPort Open Success" << endl;

    QByteArray data;
    while(m_serialPort->waitForReadyRead(2000))
    {
        data = m_serialPort->readAll(); //读取串口数据
        if(data.isEmpty())
        {
            connectPort();
            return;
        }
        else
        {   //数据上传中
            qDebug()<<"USB Client Send Data "<<data.toHex() << endl;
            emit StopRecvData();
            return;
        }
    }
    connectPort();
    return;
}

void QSerialPortEx::connectPort()
{
    qDebug()<<"Connect Port Fun receiveInfo()" << endl;
    //连接信号槽 当下位机发送数据QSerialPortInfo 会发送个 readyRead 信号,我们定义个槽void receiveInfo()解析数据
    connect(m_serialPort,SIGNAL(readyRead()),this,SLOT(receiveInfo()));
}

void QSerialPortEx::clearSerialPort()
{
    qDebug()<<"Clear Data" << endl;
    QByteArray data;
    while(m_serialPort->waitForReadyRead(400))
    {
        usleep(100);
        data = m_serialPort->readAll(); //读取串口数据
        qDebug()<<data.toHex()<< endl;
        if(!data.isEmpty())
        {
            m_serialPort->clear();
        }
    }    
    m_serialPort->clear();
}

QSerialPort* QSerialPortEx::getSerialName()
{
    return m_serialPort;
}
bool QSerialPortEx::IsOpenPort()
{
    return m_serialPort->isOpen();
}

//接收单片机的数据
void QSerialPortEx::receiveInfo()
{
    QByteArray info = m_serialPort->readAll();
    qDebug()<<"Recv Data  :" << info.toHex() << endl;
    emit ReadComm(info);
}

//写两个函数 向单片机发送数据
void QSerialPortEx::sendInfo(char * info,int len)
{
    if(m_serialPort->isOpen())
    {
        QByteArray strDebug(info,len);
        qDebug()<<"Write to serial: "<< strDebug.toHex() <<endl;
        m_serialPort->write(info,len);//这句是真正的给单片机发数据 用到的是QIODevice::write 具体可以看文档
    }
}

void QSerialPortEx::sendInfo(QString &info)
{
    if(m_serialPort->isOpen())
    {
        QByteArray sendBuf;
        if (info.contains(" "))
        {
            info.replace(QString(" "),QString(""));//我这里是把空格去掉，根据你们定的协议来
        }
        qDebug()<<"Write to serial: "<< info;
        QStringToHexQByteArray(info, sendBuf); //把QString 转换 为 hex
        m_serialPort->write(sendBuf);////这句是真正的给单片机发数据 用到的是QIODevice::write 具体可以看文档
    }
}

