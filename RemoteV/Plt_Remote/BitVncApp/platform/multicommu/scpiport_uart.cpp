#include "scpiport_uart.h"
extern scpi_t scpi_context;
extern SYSTEM_STATUS g_systemStatus;
extern ScpiPort_common   *g_pPortCommon;

ScpiPort_uart::ScpiPort_uart(QObject *parent) :
    ScpiPort_common(parent)
{
    m_modeScpi = true;
    this->slotAcceptConnection();
}


void ScpiPort_uart::slotAcceptConnection()
{
    qDebug("********%s********",__func__);
    QSettings setting;
    qDebug() << "ScpiPort_uart" << "@" <<setting.value(SETTING_RS232_COMNUMBER,"COM1").toString();
    qDebug() << "ScpiPort_uart" << "@" <<setting.value(SETTING_RS232_BAUDRATE,38400).toInt();
    QString com = setting.value(SETTING_RS232_COMNUMBER,"COM1").toString();
    int icom = com.right(1).toInt() - 1;
    if(icom>=0 && icom<= 7)
    {
        m_uart.setPortName("/dev/ttyUSB"+QString::number(icom));
        if(m_uart.open(QIODevice::ReadWrite))
        {
            qDebug()<<"open uart.";
        }
    }
    if(m_uart.isOpen())
    {
        m_uart.setBaudRate(setting.value(SETTING_RS232_BAUDRATE,38400).toInt());
        m_uart.setDataBits((QSerialPort::DataBits)setting.value(SETTING_RS232_DATABIT,QSerialPort::Data8).toInt());
        m_uart.setParity((QSerialPort::Parity)setting.value(SETTING_RS232_PARITY,QSerialPort::NoParity).toInt());
        m_uart.setStopBits((QSerialPort::StopBits)setting.value(SETTING_RS232_STOPBIT,QSerialPort::OneStop).toInt());
        m_uart.setFlowControl((QSerialPort::FlowControl)setting.value(SETTING_RS232_FLOWCTRL,QSerialPort::NoFlowControl).toInt());
        g_systemStatus.mode = Mode_remote_uart;
        scpi_context.user_context = this->getUserContext();
        connect(&m_uart, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
        connect(&m_uart, SIGNAL(readyRead()), this, SLOT(slotReadUartConnected()));
    }
    else
    {
        qDebug()<<"open uart failed.";
    }
}
void ScpiPort_uart::handleError(QSerialPort::SerialPortError /*e*/)
{
    this->closeConn();
}

void ScpiPort_uart::slotReadUartConnected()
{
    qDebug(":::%s", __func__);
    if(!m_modeScpi)return transFile();

    static QString comData;
    QString curData = m_uart.readAll();
    comData += curData;

    if(!comData.contains("\n"))return;

    m_cmdBuffer = comData.toLatin1();
    comData.clear();

    if (Mode_remote_uart == g_systemStatus.mode ||
        Mode_local == g_systemStatus.mode)
    {
        g_pPortCommon = this;
        if (m_cmdBuffer.size() && !m_cmdBuffer.isEmpty() && !m_cmdBuffer.isNull())
        {
            qDebug("recv:[%s]", m_cmdBuffer.constData());
            m_cmdBuffer.append("\r\n");

            if (Mode_local == g_systemStatus.mode)
                g_systemStatus.port = Port_uart;

            SCPI_Input(&scpi_context, m_cmdBuffer.constData(), m_cmdBuffer.size());
            SCPI_Input(&scpi_context, NULL, 0);
        }
    }
}

void ScpiPort_uart::closeConn()
{
    if (Mode_remote_uart==g_systemStatus.mode)
    {
        this->clear();        
    }
}

void ScpiPort_uart::lostConn()
{
    if (Mode_remote_uart==g_systemStatus.mode)
    {
        this->clear();
    }
}

void ScpiPort_uart::slotRestConn()
{
    qDebug("********%s********",__func__);
    m_modeScpi = true;
    disconnect(&m_uart, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    disconnect(&m_uart, SIGNAL(readyRead()), this, SLOT(slotReadUartConnected()));
    m_uart.close();
    slotAcceptConnection();
}

