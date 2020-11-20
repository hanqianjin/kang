#include "scpiport_usb.h"
#include "lib_usb.h"
#include "remoteinterface.h"
#include <QMap>
#include <QFile>

extern scpi_t scpi_context;
extern SYSTEM_STATUS g_systemStatus;
extern ScpiPort_common   *g_pPortCommon;


/**
* @class
* @brief
* @since {2019-08-20}
*/
extern scpi_command_t scpi_commands[];
extern scpi_command_t rtsa_scpi_commands[];
extern scpi_command_t ltefdd_scpi_commands[];
extern scpi_command_t ltetdd_scpi_commands[];
extern scpi_command_t fgnr_scpi_commands[];

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

  scpi_context.user_context = this->getUserContext();
  QString curData = m_usb.readAll();  
  //命令末尾必须为\n
  if (curData.right(1) != "\n")
    {
      return;
    }

  curData.remove(curData.length() - 1, 1); // 去掉最后一个'\n'
  m_cmdBuffer = curData.toUtf8();

  /**
* @class
* @brief add mode
* @since {2019-08-20}
*/
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

  if(m_cmdBuffer.length())
    {
      g_systemStatus.mode = Mode_remote_usb;
      slotReadUsbConnected();
    }
}

void ScpiPort_usb::slotWriteData(int socket)
{
if(oricmdstr.contains("?"))
  {
    SCPI_Input(&scpi_context, oricmdstr.toUtf8().data(), oricmdstr.size());
    //SCPI_Input(&scpi_context, NULL, 0);
    oricmdstr.clear();
  }
return;
}

/**
* @class
* @brief
* @since {2019-08-27}
*/
void ScpiPort_usb::slotAcceptConnection()
{
  usb_device_path = "/dev/g_tmc0";
  if(QFile::exists(usb_device_path))
    {
      m_usb.setFileName(usb_device_path);
    }
  else
    {
      qCritical() << "/dev/g_tmc0 nonexist.";
      m_valid = false;
      return;
    }

  if(!m_usb.open(QIODevice::ReadWrite))
    {
      qCritical() << "open /dev/g_tmc0 failed.";
      m_valid = false;
      return;
    }

  rnotifier = new QSocketNotifier(m_usb.handle(), QSocketNotifier::Read);
  if(!rnotifier)
    {
      qCritical() << "r connect /dev/g_tmc0 failed.";
      m_valid = false;
      return;
    }

  wnotifier = new QSocketNotifier(m_usb.handle(),QSocketNotifier::Write);
  if(!wnotifier)
    {
      qCritical() << "w connect /dev/g_tmc0 failed.";
      m_valid = false;
      return;
    }
  m_valid = true; 
  scpi_context.user_context = this->getUserContext();
  connect(rnotifier, SIGNAL(activated(int)), this, SLOT(slotReadData(int)));
  connect(wnotifier, SIGNAL(activated(int)), this, SLOT(slotWriteData(int)));
}

void ScpiPort_usb::write(QByteArray buf)
{
  qint32 ilen = m_usb.write(buf);
  m_usb.flush();
}

void ScpiPort_usb::slotReadUsbConnected()
{ 
  if (Mode_remote_usb == g_systemStatus.mode ||
      Mode_local == g_systemStatus.mode)
    {
      g_pPortCommon = this;
      if (m_cmdBuffer.size() && !m_cmdBuffer.isEmpty() && !m_cmdBuffer.isNull())
        {
          remoteinterface::getplatformremotehandle()->SetRemoteUi();          
          QStringList strCmdList = QString::fromUtf8(m_cmdBuffer.constData()).split('\n', QString::SkipEmptyParts); // 防止多个命令黏贴

          for (int i = 0; i < strCmdList.size() - 1; ++i)
            {
              if (!strCmdList.at(i).compare(strCmdList.at(i + 1))) // 如果缓冲区的命令是一样的，只执行一次
                {
                  strCmdList.removeAt(i + 1);
                }
            }

          if (Mode_local == g_systemStatus.mode)
            {
              g_systemStatus.port = Port_usb;              
            }


          foreach(QString cmd, strCmdList)
            {
              cmd.append("\r\n");
              oricmdstr = cmd;
              //when multi cmds contains mode switch conmand and when the cmd contains mode switch conmand
              //and the else conmands do not deal;              
              if(!cmd.contains("?") && cmd.contains("INST") && (cmd.contains("SELE") || cmd.contains("CLOS")) && cmd.contains("ANAM"))
                {
                  SCPI_Input(&scpi_context, cmd.toUtf8().data(), cmd.size());
                  SCPI_Input(&scpi_context, NULL, 0);
                  return;
                }
              else
                {
                  if(!cmd.contains("?"))
                    {
                      SCPI_Input(&scpi_context, cmd.toUtf8().data(), cmd.size());
                      SCPI_Input(&scpi_context, NULL, 0);
                    }
                }
            }
        }
    }
}

void ScpiPort_usb::closeConn()
{  
  if (Mode_remote_usb==g_systemStatus.mode)
    {        
      remoteinterface::getplatformremotehandle()->SetLocalUi(Qt::Key_Escape);
      this->clear();
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

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-06-29}
*/
void ScpiPort_usb::ReleaseMiniUsb()
{   
  if (Mode_remote_usb == g_systemStatus.mode)
    {
      remoteinterface::getplatformremotehandle()->SetLocalUi(Qt::Key_Escape);
    }
  m_valid = false;
  if(!rnotifier)
  {
      rnotifier->disconnect();
      rnotifier->deleteLater();
      delete rnotifier;
      rnotifier = NULL;
  }
  if(!wnotifier)
  {
      wnotifier->disconnect();
      wnotifier->deleteLater();
      delete wnotifier;
      wnotifier = NULL;
  }
  m_usb.close();
  this->clear();
}

