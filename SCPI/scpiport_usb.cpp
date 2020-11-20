#include "scpiport_usb.h"
#include "lib_usb.h"

#include <QMap>
#include <QFile>

extern scpi_t scpi_context;
extern SYSTEM_STATUS g_systemStatus;
extern ScpiPort_common   *g_pPortCommon;

ScpiPort_usb::ScpiPort_usb(QObject *parent) :
    ScpiPort_common(parent)
{
    acceptUSBInit();
    slotAcceptConnection();
}

bool ScpiPort_usb::getUsbValid()
{
    return m_valid;
}

void ScpiPort_usb::slotReadData(int /*socket*/)
{
    if(!m_modeScpi)
    {
        transFile();
        return;
    }
    m_cmdBuffer = m_usb.readAll();
    if(m_cmdBuffer.length())
    {
        slotReadUsbConnected();
    }
}

void ScpiPort_usb::slotAcceptConnection()
{
    usb_device_path = "/dev/ttyGF5";
    if(QFile::exists(usb_device_path))
    {
        m_usb.setFileName(usb_device_path);
    }
    else
    {
        qDebug() << "/dev/ttyGF5 nonexist.";
        m_valid = false;
        return;
    }
    if(!m_usb.open(QIODevice::ReadWrite))
    {
        qDebug() << "open /dev/ttyGF5 failed.";
        m_valid = false;
        return;
    }
    notifier = new QSocketNotifier(m_usb.handle(), QSocketNotifier::Read);
    if(!notifier)
    {
        qDebug() << "connect /dev/ttyGF5 failed.";
        m_valid = false;
        return;
    }
    m_valid = true;
    connect(notifier, SIGNAL(activated(int)), this, SLOT(slotReadData(int)));
    qDebug()<<"ScpiPort_usb";
}
void ScpiPort_usb::write(QByteArray buf)
{
    m_usb.write(buf);
}
void ScpiPort_usb::slotReadUsbConnected()
{
    if (Mode_remote_usb == g_systemStatus.mode ||
        Mode_local == g_systemStatus.mode)
    {
        g_pPortCommon = this;
        if (m_cmdBuffer.size() && !m_cmdBuffer.isEmpty() && !m_cmdBuffer.isNull())
        {
            qDebug("recv:[%s]", m_cmdBuffer.constData());
//            m_cmdBuffer.append("\r\n");

            if (Mode_local == g_systemStatus.mode)
                g_systemStatus.port = Port_usb;

            SCPI_Input(&scpi_context, m_cmdBuffer.constData(), m_cmdBuffer.size());
            SCPI_Input(&scpi_context, NULL, 0);
        }
    }
}

void ScpiPort_usb::closeConn()
{
    if (Mode_remote_usb==g_systemStatus.mode)
    {
        this->clear();
        LocalCommunicate::instance()->changeMode(Mode_local);
    }
}

void ScpiPort_usb::lostConn()
{
    if (Mode_remote_usb==g_systemStatus.mode)
    {
        this->clear();
    }
}

void ScpiPort_usb::slotRestConn()
{
    m_usb.close();
    closeConn();
    acceptUSBInit();
    slotAcceptConnection();
}

void ScpiPort_usb::acceptUSBInit()
{
    m_modeScpi = true;
    m_valid = false;
}
