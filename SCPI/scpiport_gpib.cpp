#include "scpiport_gpib.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>

extern scpi_t scpi_context;
extern SYSTEM_STATUS g_systemStatus;
extern ScpiPort_common   *g_pPortCommon;

ScpiPort_gpib::ScpiPort_gpib(QObject *parent) :
    ScpiPort_common(parent)
{
    acceptGpibInit();
    slotAcceptConnection();
}
void ScpiPort_gpib::write(QByteArray buf)
{
    m_gpib.write(buf);
}

void ScpiPort_gpib::slotRestConn()
{
    m_gpib.close();
    closeConn();
    acceptGpibInit();
    slotAcceptConnection();
}

void ScpiPort_gpib::acceptGpibInit()
{
    QFile f(GPIB_SETTING_NODE);
    if(!f.exists())
    {
        qDebug()<<"file [/sys/bus/platform/device/f260_misc_tty.6/gpib_addr] nonexists.";
        return;
    }
    if(!f.open(QIODevice::ReadWrite))
    {
        qDebug()<<"open [/sys/bus/platform/device/f260_misc_tty.6/gpib_addr] failed.";
        return;
    }
    if(m_setting.value(SETTING_GPIB_ADRESS,"1").toString() == "1")
    {
        f.write("1");
    }
    else
    {
        f.write("2");
    }
}

void ScpiPort_gpib::slotReadData(int /*socket*/)
{
    if(!m_modeScpi)
    {
        transFile();
        return;
    }
    m_cmdBuffer = m_gpib.readAll();
    if(m_cmdBuffer.length())
    {
        slotReadgpibConnected();
    }
}


void ScpiPort_gpib::slotAcceptConnection()
{
    gpib_device_path = "/dev/ttyGF6";
    if(QFile::exists(gpib_device_path))
    {
        m_gpib.setFileName(gpib_device_path);
    }
    else
    {
        m_valid = false;
        return;
    }
    if(!m_gpib.open(QIODevice::ReadWrite))
    {
        m_valid = false;
        return;
    }

    notifier = new QSocketNotifier(m_gpib.handle(), QSocketNotifier::Read);
    if(!notifier)
    {
        m_valid = false;
        return;
    }
    m_valid = true;
    connect(notifier, SIGNAL(activated(int)), this, SLOT(slotReadData(int)));
    qDebug()<<"ScpiPort_gpib";
}

void ScpiPort_gpib::slotReadgpibConnected()
{
    if (Mode_remote_gpib == g_systemStatus.mode ||
        Mode_local == g_systemStatus.mode)
    {
        g_pPortCommon = this;
        if (m_cmdBuffer.size() && !m_cmdBuffer.isEmpty() && !m_cmdBuffer.isNull())
        {
            qDebug("recv:[%s]", m_cmdBuffer.constData());
            m_cmdBuffer.append("\r\n");

            if (Mode_local == g_systemStatus.mode)
                g_systemStatus.port = Port_gpib;

            SCPI_Input(&scpi_context, m_cmdBuffer.constData(), m_cmdBuffer.size());
            SCPI_Input(&scpi_context, NULL, 0);
        }
    }
}

void ScpiPort_gpib::closeConn()
{
    if (Mode_remote_gpib==g_systemStatus.mode)
    {
        this->clear();
        LocalCommunicate::instance()->changeMode(Mode_local);
    }
}

void ScpiPort_gpib::lostConn()
{
    if (Mode_remote_gpib==g_systemStatus.mode)
    {
        this->clear();
    }
}

