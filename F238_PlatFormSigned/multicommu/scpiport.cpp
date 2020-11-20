#include "scpiport.h"
#include <QMutex>
extern SYSTEM_STATUS g_systemStatus;
extern scpi_t scpi_context;
extern ScpiPort_common   *g_pPortCommon;


ScpiPort_common::ScpiPort_common(QObject *parent)
    : QObject(parent)
{
    g_pPortCommon = this;
    m_modeScpi = true;
    m_fileName = "";
    m_fileLen = 0;
    m_byte_readed = 0;
    connect(this,SIGNAL(sigLostConn()),
            this,SLOT(slotLostConn()));
}

void ScpiPort_common::slotLostConn()
{
    QMutex mutexData;
    mutexData.lock();
    this->lostConn();
    mutexData.unlock();
}

void ScpiPort_common::clear()
{
    g_systemStatus.mode = Mode_local;
    m_modeScpi = true;
    scpi_context.user_context = NULL;
    m_cmdBuffer.clear();
    g_pPortCommon = NULL;
}

//void ScpiPort_common::connectClose()
//{
//    g_systemStatus.mode = Mode_local;
//    scpi_context.user_context = NULL;
//    m_cmdBuffer.clear();
//    //用户断开了与SCPI连接,通知GUI进程进入本地模式
//    LocalCommunicate::instance()->changeMode(Mode_local);
//}


void ScpiPort_common::initTransFile(QString filename,int filelen)
{
    m_fileName = filename;
    //检查文件是否存在,不存在创建
    //然后写操作打开

    QFileInfo info(m_fileName);
    QDir dir;
    if (!info.exists())
    {
        if (!dir.mkpath(info.path()))
        {
            m_IoDevice->write("make folder failed.");
            return;
        }
    }

    QFile file(m_fileName);
    if (file.exists())
    {
        if (!file.open(QIODevice::WriteOnly|QIODevice::Append))
        {
            m_IoDevice->write("open file failed.");
            return;
        }
        file.remove();
        file.close();
    }

    m_fileLen = filelen;
    if (m_fileLen > MAX_FILE_SZIE)
    {
        m_IoDevice->write("file size > 1M");
        return;
    }
    m_modeScpi = false;
    m_byte_readed = 0;
    m_cmdBuffer.clear();
    m_IoDevice->write("ready");
    return;
}
void ScpiPort_common::transFile()
{
    if(m_modeScpi)return;

    m_cmdBuffer.append(m_IoDevice->read(m_fileLen - m_byte_readed));
    m_byte_readed = m_cmdBuffer.size();

    if (m_byte_readed == m_fileLen)
    {
        QFile file(m_fileName);
        if (!file.open(QIODevice::WriteOnly|QIODevice::Append))
        {
            m_IoDevice->write("open file failed.");
            return;
        }
        file.write(m_cmdBuffer);
        file.close();
        m_modeScpi = true;
        m_fileLen = 0;
        m_fileName = "";
        m_IoDevice->write("done");
    }
}
