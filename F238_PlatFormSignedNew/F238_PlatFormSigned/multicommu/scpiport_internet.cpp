#include "scpiport_internet.h"
#include "localcommunicate.h"
#include "remoteinterface.h"
#include "scpidef/autoproductcommand.h"

extern scpi_t scpi_context;
extern SYSTEM_STATUS g_systemStatus;
extern ScpiPort_common   *g_pPortCommon;

//!<02-28 steve
extern scpi_command_t scpi_commands[];
extern scpi_command_t rtsa_scpi_commands[];
extern scpi_command_t ltefdd_scpi_commands[];
extern scpi_command_t ltetdd_scpi_commands[];
extern scpi_command_t fgnr_scpi_commands[];

ScpiPort_internet::ScpiPort_internet(qint32 *port, QObject *parent):
  m_tcpSocketConnected(NULL),
  ScpiPort_common(parent)
{
  qDebug() << __func__ << "@" << "5026";
  //m_port = m_setting.value(SETTING_TCPSERVER_PORT, 0).toUInt();
  m_port = port;  //DEBUG
  m_tcpServer.listen(QHostAddress::Any, *m_port);
  connect(&m_tcpServer, &QTcpServer::newConnection, this, &ScpiPort_internet::slotAcceptConnection);
}

ScpiPort_internet::ScpiPort_internet(QObject *parent) :
  m_tcpSocketConnected(NULL),
  ScpiPort_common(parent)
{

}

void ScpiPort_internet::slotAcceptConnection()
{
  qDebug("%s", __func__);
  if (NULL == m_tcpSocketConnected)
    {
      m_tcpSocketConnected = m_tcpServer.nextPendingConnection();
      m_IoDevice = m_tcpSocketConnected;
      set_tcp_keepAlive(m_tcpSocketConnected->socketDescriptor(),1,1,10);
      if (m_tcpSocketConnected)
        {
          g_systemStatus.mode = Mode_remote_internet;
          scpi_context.user_context = this->getUserContext();
          connect(m_tcpSocketConnected, &QTcpSocket::readyRead, this, &ScpiPort_internet::slotReadTCPConnected);
          connect(m_tcpSocketConnected, &QTcpSocket::disconnected, this, &ScpiPort_internet::slotCloseTCPConnection);
          //this means not support multi connect
          m_tcpServer.close();
          remoteinterface::getplatformremotehandle()->SetRemoteUi();         
        }
    }
}

void ScpiPort_internet::slotReadTCPConnected()
{
  //when user set local but connect still exist the send cmd need to remote again without connect again
  remoteinterface::getplatformremotehandle()->SetRemoteUi();
  g_systemStatus.mode = Mode_remote_internet;
  scpi_context.user_context = this->getUserContext();
  if (!m_modeScpi)
    {
      return transFile();
    }

  if(0 == remoteinterface::getanamodehandle())
    {
      scpi_context.cmdlist = scpi_commands;
    }
  else if(1 == remoteinterface::getanamodehandle())
    {
      scpi_context.cmdlist = rtsa_scpi_commands;
    }
  else if(4 == remoteinterface::getanamodehandle())
    {
      scpi_context.cmdlist = ltefdd_scpi_commands;
    }
  else if(5 == remoteinterface::getanamodehandle())
    {
      scpi_context.cmdlist = ltetdd_scpi_commands;
    }
  else if(6 == remoteinterface::getanamodehandle())
    {
      scpi_context.cmdlist = fgnr_scpi_commands;
    }
  static QString comData;
  QString curData;

#if NI_PROTO
  QByteArray BA = m_tcpSocketConnected->readAll();
  curData = cmdDataProcess(BA);
#else
  curData = m_tcpSocketConnected->readAll();
#endif
  comData += curData;
  //命令末尾必须为\n
  if (comData.right(1) != "\n")
    {
      comData.clear();
      return;
    }
  comData.remove(comData.length() - 1, 1); // 去掉最后一个'\n'
  m_cmdBuffer = comData.toUtf8();  
  comData.clear();
  if (Mode_remote_internet == g_systemStatus.mode || Mode_local == g_systemStatus.mode)
    {
      g_pPortCommon = this;
      if (m_cmdBuffer.size() && !m_cmdBuffer.isEmpty() && !m_cmdBuffer.isNull())
        {
          QStringList strCmdList = QString::fromUtf8(m_cmdBuffer.constData()).split('\n', QString::SkipEmptyParts); // 防止多个命令黏贴                   
          for (int i = 0; i < strCmdList.size() - 1; ++i)
            {
              //QMessageBox::about(0,"net",strCmdList.at(i));
              if (!strCmdList.at(i).compare(strCmdList.at(i + 1))) // 如果缓冲区的命令是一样的，只执行一次
                {
                  strCmdList.removeAt(i + 1);
                }
            }
          if (Mode_local == g_systemStatus.mode)
            {
              g_systemStatus.port = Port_internet;
            }

          foreach(QString cmd, strCmdList)
            {             
              cmd.append("\r\n");

              //when multi cmds contains mode switch conmand and when the cmd contains mode switch conmand
              //and the else conmands do not deal;
              if(cmd.contains("INST") && (cmd.contains("SELE") || cmd.contains("CLOS")) && cmd.contains("ANAM"))
                {                  
                  SCPI_Input(&scpi_context, cmd.toUtf8().data(), cmd.size());
                  SCPI_Input(&scpi_context, NULL, 0);
                  return;
                }
              else
                {
                  SCPI_Input(&scpi_context, cmd.toUtf8().data(), cmd.size());
                  SCPI_Input(&scpi_context, NULL, 0);
                }
            }
        }
    }
}

void ScpiPort_internet::slotCloseTCPConnection()
{  
  this->closeConn();
}

void ScpiPort_internet::closeConn()
{
  qDebug("%s", __func__);

  if (Mode_remote_internet == g_systemStatus.mode)
    {
      this->clear();
    }
  if (m_tcpSocketConnected->isValid())
    {
      m_tcpSocketConnected->disconnectFromHost();
    }
  m_tcpSocketConnected->deleteLater();  

  m_tcpSocketConnected = NULL;
  m_tcpServer.listen(QHostAddress::Any, *m_port);
  remoteinterface::getplatformremotehandle()->SetLocalUi(Qt::Key_Escape);

}

void ScpiPort_internet::lostConn()
{
  qDebug("%s", __func__);
  if (Mode_remote_internet == g_systemStatus.mode)
    {
      this->clear();
      if (m_tcpSocketConnected->isValid())
        {
          m_tcpSocketConnected->disconnectFromHost();
        }
      m_tcpSocketConnected->deleteLater();
      m_tcpSocketConnected = NULL;
      m_tcpServer.listen(QHostAddress::Any, *m_port);
    }
}

void ScpiPort_internet::closeBitConn()
{
  if (Mode_remote_internet == g_systemStatus.mode)
    {
      this->clear();      
    }
  if(m_tcpSocketConnected)
    {
      if (m_tcpSocketConnected->isValid())
        {
          m_tcpSocketConnected->disconnectFromHost();
        }
      m_tcpSocketConnected->deleteLater();
    }
}

void ScpiPort_internet::buildBitConn()
{  
  if(m_tcpServer.isListening())
    {
      m_tcpServer.close();
      m_tcpServer.listen(QHostAddress::Any, *m_port);
    }
  //remoteinterface::getplatformremotehandle()->SetLocalUi();
}

//fd:网络连接描述符
//start:首次心跳侦测包发送之间的空闲时间
//interval:两次心跳侦测包之间的间隔时间
//count:探测次数，即将几次探测失败判定为TCP断开
int ScpiPort_internet::set_tcp_keepAlive(int fd, int start, int interval, int count)
{
#ifdef Q_OS_LINUX
  int keepAlive = 1;
  if (fd < 0 || start < 0 || interval < 0 || count < 0) return -1;  //入口参数检查

  //启用心跳机制，如果您想关闭，将keepAlive置零即可
  if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (void*)&keepAlive, sizeof(keepAlive)) == -1)
    {
      qDebug("setsockopt");
      return -1;
    }
  //启用心跳机制开始到首次心跳侦测包发送 的空闲时间
  if (setsockopt(fd, SOL_TCP, TCP_KEEPIDLE, (void *)&start, sizeof(start)) == -1)
    {
      qDebug("setsockopt");
      return -1;
    }
  //两次心跳侦测包之间的间隔时间
  if (setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, (void *)&interval, sizeof(interval)) == -1)
    {
      qDebug("setsockopt");
      return -1;
    }
  //探测次数，即将几次探测失败判定为TCP断开
  if (setsockopt(fd, SOL_TCP, TCP_KEEPCNT, (void *)&count, sizeof(count)) == -1)
    {
      qDebug("setsockopt");
      return -1;
    }
#endif
  return 0;
}
