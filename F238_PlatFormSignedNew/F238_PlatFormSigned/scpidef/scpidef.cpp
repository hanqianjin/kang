#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <QMutex>
#include <QDebug>

#include "libscpi/inc/scpi/scpi.h"
#include "scpidef.h"
//#include ""//command define header
#include "sa_scpi_freq.h"
#include "sa_scpi_amp.h"
#include "sa_scpi_bw.h"
#include "sa_scpi_trace.h"
#include "sa_scpi_sweep.h"
#include "sa_scpi_limit.h"
#include "sa_scpi_meas.h"
#include "sa_scpi_marker.h"
#include "sa_scpi_setup.h"
#include "sa_scpi_trigger.h"
#include "rtsa_scpi_freq.h"
#include "rtsa_scpi_amp.h"
#include "rtsa_scpi_bw.h"
#include "rtsa_scpi_display.h"
#include "rtsa_scpi_trace.h"
#include "rtsa_scpi_sweep.h"
#include "rtsa_scpi_limit.h"
#include "rtsa_scpi_marker.h"
#include "rtsa_scpi_setup.h"
#include "rtsa_scpi_trigger.h"

#include "nr_scpi_amp.h"
#include "nr_scpi_bw.h"
#include "nr_scpi_freq.h"
#include "nr_scpi_limit.h"
#include "nr_scpi_marker.h"
#include "nr_scpi_meas.h"
#include "nr_scpi_sweep.h"
#include "nr_scpi_trace.h"

#include "fdd_scpi_amp.h"
#include "fdd_scpi_bw.h"
#include "fdd_scpi_freq.h"
#include "fdd_scpi_limit.h"
#include "fdd_scpi_marker.h"
#include "fdd_scpi_meas.h"
#include "fdd_scpi_sweep.h"
#include "fdd_scpi_trace.h"
#include "tdd_scpi_amp.h"
#include "tdd_scpi_bw.h"
#include "tdd_scpi_freq.h"
#include "tdd_scpi_limit.h"
#include "tdd_scpi_marker.h"
#include "tdd_scpi_meas.h"
#include "tdd_scpi_sweep.h"
#include "tdd_scpi_trace.h"

#include "dataconfig/ConfigData.h"


#include "remoteinterface.h"
#include "multicommu/localcommunicate.h"

#include "multicommu/threadmsg.h"
#define KEY_MSG_RECV 3434

#include "multicommu/scpiport_internet.h"
#include "multicommu/scpiport_uart.h"
#include "multicommu/scpiport_usb.h"

#include "scpidef/autoproductcommand.h"

ScpiPort_common     *g_pPortCommon;
ScpiPort_internet   *g_pPortInterNet;
ScpiPort_uart       *g_pPortUart;
ScpiPort_usb        *g_pPortUsb;
qint32 *g_planport;

int g_msgid_recv;

size_t SCPI_Write(scpi_t * context, const char * data, size_t len) {
  static qint32 it = 0;
  if (context->user_context != NULL) {
      if(Mode_remote_internet == g_systemStatus.mode ||
         Mode_local == g_systemStatus.mode)
        {
          QTcpSocket *pTcpSocket = reinterpret_cast<QTcpSocket *>(context->user_context);
          if (pTcpSocket->isValid())
            {
              qDebug()<<"send:"<<data;
              qDebug()<<"times:"<<it;
              it++;
#if NI_PROTO
              if(strcmp(data,"\r\n"))
              {
                  QByteArray tmpArray = charToByteArray(data);
                  QByteArray sendData = cmdDataSend(recMessgFlag,tmpArray);
                  return pTcpSocket->write(sendData);
              }
#else
              return pTcpSocket->write(data, len);
#endif
            }
          else
            return 0;
        }else if(Mode_remote_uart == g_systemStatus.mode ||
                 Mode_local == g_systemStatus.mode){
          QSerialPort *pUart = reinterpret_cast<QSerialPort *>(context->user_context);
          pUart->write(data,len);
        }else if(Mode_remote_usb == g_systemStatus.mode ||
                 Mode_local == g_systemStatus.mode){
          ScpiPort_usb *pUsb = reinterpret_cast<ScpiPort_usb *>(context->user_context);
          pUsb->write(data);
        }
    }
  return 0;
}

scpi_result_t SCPI_Flush(scpi_t * /*context*/) {
  return SCPI_RES_OK;
}

int SCPI_Error(scpi_t * context, int_fast16_t err) {
  (void) context;
  // BEEP
  fprintf(stderr, "**ERROR: %d, \"%s\"\r\n", (int32_t) err, SCPI_ErrorTranslate(err));
  return 0;
}

scpi_result_t SCPI_Control(scpi_t * /*context*/, scpi_ctrl_name_t ctrl, scpi_reg_val_t val) {
  if (SCPI_CTRL_SRQ == ctrl) {
      fprintf(stderr, "**SRQ: 0x%X (%d)\r\n", val, val);
    } else {
      fprintf(stderr, "**CTRL %02x: 0x%X (%d)\r\n", ctrl, val, val);
    }
  return SCPI_RES_OK;
}

scpi_result_t SCPI_Test(scpi_t * /*context*/) {
  fprintf(stderr, "**Test\r\n");
  return SCPI_RES_OK;
}

scpi_result_t SCPI_Reset(scpi_t * /*context*/) {
  fprintf(stderr, "**Reset\r\n");
  //Johnson 20200628 add
  remoteinterface::getplatformremotehandle()->PltFactorySet();
  return SCPI_RES_OK;
}

scpi_bool_t SCPI_SetSCPI_Port(qint32 *port)
{
  g_planport = port;
}


scpi_bool_t   SCPI_Communicate_Init()
{
//  g_msgid_recv = ::msgget((key_t)KEY_MSG_RECV, 0666 | IPC_CREAT);

//  ThreadMsg *thrdMsg = new ThreadMsg();
//  thrdMsg->start();

  //spci context init
  scpi_context.user_context = NULL;//socket
  scpi_context.buffer.length = 100000;//1024;
  scpi_context.buffer.data = (char *)malloc(200000);//(char *)malloc(2048);
  SCPI_Init(&scpi_context);


//  g_pPortUart = new ScpiPort_uart();
  g_pPortUsb = new ScpiPort_usb();
  g_pPortInterNet = new ScpiPort_internet(g_planport);
//  QObject::connect(thrdMsg,SIGNAL(sigRestartUart()),g_pPortUart,\
//                   SLOT(slotRestConn()),Qt::QueuedConnection);
//  QObject::connect(thrdMsg,SIGNAL(sigRestartUSB()),g_pPortUsb,\
//                   SLOT(slotRestConn()),Qt::QueuedConnection);
}

scpi_result_t COMM_ModeChange(scpi_t * context)
{
  scpi_bool_t param;

  qDebug("%s", __func__);
  if (!SCPI_ParamBool(context, &param, true))
    return SCPI_RES_ERR;

  if (param){
      switch (g_systemStatus.port){
        case Port_internet:
          g_systemStatus.mode = Mode_remote_internet;
          context->user_context = g_pPortInterNet->getUserContext();
          break;
        case Port_usb:
          g_systemStatus.mode = Mode_remote_usb;
          context->user_context = g_pPortUsb->getUserContext();
          break;
        case Port_gpib:
          g_systemStatus.mode = Mode_remote_gpib;
          context->user_context = g_pPortUsb->getUserContext();
          break;
        case Port_uart:
          g_systemStatus.mode = Mode_remote_uart;
          context->user_context = g_pPortUart->getUserContext();
          break;
        default:
          return SCPI_RES_ERR;
        }

    } else {
      g_systemStatus.mode = Mode_local;
      context->user_context = NULL;
      if (!LocalCommunicate::instance()->changeMode(Mode_local))
        return SCPI_RES_ERR;
    }

  return SCPI_RES_OK;
}

scpi_result_t COMM_TransFile_Send(scpi_t * context)
{
  const char *strCmd;
  QStringList strList;
  QString srcFile,destFile;

  size_t len_name;
  qint32 iBack = 0;
  if (!SCPI_ParamString(context, &strCmd, &len_name, 1))
  {
      return SCPI_RES_ERR;
  }
  strList = QString(strCmd).split(",");
  srcFile = strList.at(0);
  destFile = strList.at(1);
  destFile.remove("\r\n");
  switch(g_systemStatus.mode)
  {
  case Mode_remote_internet:
      iBack = g_pPortInterNet->transFileToRemote(srcFile,destFile);
      break;
  case Mode_remote_uart:
      iBack = g_pPortUart->transFileToRemote(srcFile,destFile);
      break;
  case Mode_remote_usb:
      iBack = g_pPortUsb->transFileToRemote(srcFile,destFile);
      break;
  default:
      break;
  }
  if(iBack)
      return SCPI_RES_OK;
  else
      return SCPI_RES_ERR;
}

scpi_result_t COMM_TransFile_Receive(scpi_t * context)
{
  size_t len_name;
  const char *file_name;
  int file_len = -1;
  QString strFile;
  if(!SCPI_ParamInt(context, &file_len,1))
  {
      return SCPI_RES_ERR;
  }
  if (!SCPI_ParamString(context, &file_name, &len_name, 1))
  {
      return SCPI_RES_ERR;
  }
  strFile = QString(file_name).remove("\r\n");
  switch(g_systemStatus.mode)
  {
  case Mode_remote_internet:
      g_pPortInterNet->initTransFile(strFile,file_len);
      break;
  case Mode_remote_uart:
      g_pPortUart->initTransFile(strFile,file_len);
      break;
  case Mode_remote_usb:
      g_pPortUsb->initTransFile(strFile,file_len);
      break;
  default:
      break;
  }
  return SCPI_RES_OK;
}
scpi_command_t scpi_commands[] = {
  SCPI_COMMANDS_MISC
  SA_SCPI_COMMANDS_FREQUENCY
  SA_SCPI_COMMANDS_AMPLITUDE
  SA_SCPI_COMMANDS_BANDWIDTH
  SA_SCPI_COMMANDS_TRACE
  SA_SCPI_COMMANDS_TRIGGER
  SA_SCPI_COMMANDS_SWEEP
  SA_SCPI_COMMANDS_LIMIT
  SA_SCPI_COMMANDS_MEASURE
  SA_SCPI_COMMANDS_MARKER
  SA_SCPI_COMMANDS_SETUP
  SCPI_CMD_LIST_END//end flag
};

/**
* @class rtsa
* @brief
*/
scpi_command_t rtsa_scpi_commands[] = {
  SCPI_COMMANDS_MISC
  RTSA_SCPI_COMMANDS_FREQUENCY
  RTSA_SCPI_COMMANDS_AMPLITUDE
  RTSA_SCPI_COMMANDS_SWEEP
  RTSA_SCPI_COMMANDS_BANDWIDTH
  RTSA_SCPI_COMMANDS_TRIGGER
  RTSA_SCPI_COMMANDS_TRACE
  RTSA_SCPI_COMMANDS_LIMIT
  RTSA_SCPI_COMMANDS_MARKER
  RTSA_SCPI_COMMANDS_DISPLAY
  RTSA_SCPI_COMMANDS_SETUP
  SCPI_CMD_LIST_END//end flag
};

scpi_command_t ltetdd_scpi_commands[] = {
  SCPI_COMMANDS_MISC
  TDD_SCPI_COMMANDS_FREQUENCY
  TDD_SCPI_COMMANDS_AMPLITUDE
  TDD_SCPI_COMMANDS_SWEEP
  TDD_SCPI_COMMANDS_BANDWIDTH
  TDD_SCPI_COMMANDS_TRACE
  TDD_SCPI_COMMANDS_LIMIT
  TDD_SCPI_COMMANDS_MARKER
  TDD_SCPI_COMMANDS_MEASURE
  SCPI_CMD_LIST_END//end flag
};

scpi_command_t ltefdd_scpi_commands[] = {
  SCPI_COMMANDS_MISC
  FDD_SCPI_COMMANDS_FREQUENCY
  FDD_SCPI_COMMANDS_AMPLITUDE
  FDD_SCPI_COMMANDS_SWEEP
  FDD_SCPI_COMMANDS_BANDWIDTH
  FDD_SCPI_COMMANDS_TRACE
  FDD_SCPI_COMMANDS_LIMIT
  FDD_SCPI_COMMANDS_MARKER
  FDD_SCPI_COMMANDS_MEASURE
  SCPI_CMD_LIST_END//end flag
};

scpi_command_t fgnr_scpi_commands[] = {
  SCPI_COMMANDS_MISC
  NR_SCPI_COMMANDS_FREQUENCY
  NR_SCPI_COMMANDS_AMPLITUDE
  NR_SCPI_COMMANDS_SWEEP
  NR_SCPI_COMMANDS_BANDWIDTH
  NR_SCPI_COMMANDS_TRACE
  NR_SCPI_COMMANDS_LIMIT
  NR_SCPI_COMMANDS_MARKER
  NR_SCPI_COMMANDS_MEASURE
  SCPI_CMD_LIST_END//end flag
};

static scpi_interface_t scpi_interface = {
  /* error */ SCPI_Error,
  /* write */ SCPI_Write,
  /* control */ SCPI_Control,
  /* flush */ SCPI_Flush,
  /* reset */ SCPI_Reset,
  /* test */ SCPI_Test,
};

#define SCPI_INPUT_BUFFER_LENGTH 256
static char scpi_input_buffer[SCPI_INPUT_BUFFER_LENGTH];

static scpi_reg_val_t scpi_regs[SCPI_REG_COUNT];


scpi_t scpi_context = {
  /* cmdlist */ scpi_commands,
  /* buffer */ { /* length */ SCPI_INPUT_BUFFER_LENGTH, /* position */ 0,  /* data */ scpi_input_buffer, },
  /* paramlist */ { /* cmd */ NULL, /* parameters */ NULL, /* length */ 0, },
  /* interface */ &scpi_interface,
  /* output_count */ 0,
  /* input_count */ 0,
  /* cmd_error */ FALSE,
  /* error_queue */ NULL,
  /* registers */ scpi_regs,
  /* units */ scpi_units_def,
  /* special_numbers */ scpi_special_numbers_def,
  /* user_context */ NULL,
  /* idn */ {"INNO","Signal Analyzer","19051100","0.3"},
};


SYSTEM_STATUS g_systemStatus = {
  /*Mode: Remote/Local*/Mode_local,
  /*Communicate Port*/Port_null,
};

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-03-01}
*/
scpi_result_t SWITCH_Anamode(scpi_t *context)
{
  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_OK;
  qint32 imode = -1;
  qint32 imeas = -1;

  //mode
  if (!SCPI_ParamInt(context, &imode, true))
    {
      return SCPI_RES_ERR;
    }
  //measure iteam,may omit
  if(!SCPI_ParamInt(context, &imeas, false))
    {
      imeas = -1;
    }
  remoteinterface::getplatformremotehandle()->SwitchAnaMode(imode,imeas);
  return SCPI_RES_OK;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-03-01}
*/
scpi_result_t CLOSE_Anamode(scpi_t *context)
{
  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_OK;
  qint32 imode = -1;
  //mode
  if (!SCPI_ParamInt(context, &imode, true))
    {
      return SCPI_RES_ERR;
    }
  remoteinterface::getplatformremotehandle()->CloseAnaModeR(imode);
  return SCPI_RES_OK;
}

/**
 * @brief for remote ctrl to close plt and up calc peocess
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-04-29}
*/
scpi_result_t SCPI_CalcRun(scpi_t *context)
{
  remoteinterface::getplatformremotehandle()->StartDevCalc();
  return SCPI_RES_OK;
}

/**
 * @brief to set vloume and change ui and save recover state
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-05-21}SetSysLcdBri
*/
scpi_result_t VOLU_Ctrl(scpi_t *context)
{
  qint32 ivol = -1;
  //volume
  if (!SCPI_ParamInt(context, &ivol, false))
    {
      return SCPI_RES_ERR;
    }
  remoteinterface::getplatformremotehandle()->SetSysVolume(ivol);
  return SCPI_RES_OK;
}

scpi_result_t VOLU_Switch_Ctrl(scpi_t *context)
{
  qint32 iswitch = -1;
  //volume
  if (!SCPI_ParamInt(context, &iswitch, false))
    {
      return SCPI_RES_ERR;
    }
  remoteinterface::getplatformremotehandle()->SetSysVolSwitch(iswitch);
  return SCPI_RES_OK;
}

scpi_result_t BRIGness_Ctrl(scpi_t *context)
{
  qint32 ibri = -1;
  //volume
  if (!SCPI_ParamInt(context, &ibri, false))
    {
      return SCPI_RES_ERR;
    }
  remoteinterface::getplatformremotehandle()->SetSysLcdBri(ibri);
  return SCPI_RES_OK;
}

scpi_result_t DATEtype_Ctrl(scpi_t *context)
{
  qint32 ival = -1;
  //volume
  if (!SCPI_ParamInt(context, &ival, false))
    {
      return SCPI_RES_ERR;
    }
  remoteinterface::getplatformremotehandle()->SetSysDateType(ival);
  return SCPI_RES_OK;
}

scpi_result_t DISPlay_Ctrl(scpi_t *context)
{
  qint32 ival = -1;
  //volume
  if (!SCPI_ParamInt(context, &ival, false))
    {
      return SCPI_RES_ERR;
    }
  remoteinterface::getplatformremotehandle()->SetSysDisMod(ival);
  return SCPI_RES_OK;
}

scpi_result_t SLEEp_Ctrl(scpi_t *context)
{
  qint32 ival = -1;
  //volume
  if (!SCPI_ParamInt(context, &ival, false))
    {
      return SCPI_RES_ERR;
    }
  remoteinterface::getplatformremotehandle()->SetSysSleepT(ival);
  return SCPI_RES_OK;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-05-23}
*/
scpi_result_t GPSwitch_Ctrl(scpi_t *context)
{
  qint32 ival = -1;
  //volume
  if (!SCPI_ParamInt(context, &ival, false))
    {
      return SCPI_RES_ERR;
    }
  remoteinterface::getplatformremotehandle()->SetGpsEnable(ival);
  return SCPI_RES_OK;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-06-28}
*/
scpi_result_t SCPI_SetIp(scpi_t *context)
{
  const char* pstr;
  size_t ilen;
  if(!SCPI_ParamString(context, &pstr,&ilen,false))
    {
      return SCPI_RES_ERR;
    }

  QString mstr = QString(QLatin1String(pstr));
  mstr = mstr.mid(0,mstr.indexOf('\r'));
  remoteinterface::getplatformremotehandle()->SetSysIpAddr(mstr);
  return SCPI_RES_OK;
}

scpi_result_t SCPI_SetMask(scpi_t *context)
{
  const char* pstr;
  size_t ilen;
  if(!SCPI_ParamString(context, &pstr,&ilen,false))
    {
      return SCPI_RES_ERR;
    }
  QString mstr = QString(QLatin1String(pstr));
  mstr = mstr.mid(0,mstr.indexOf('\r'));
  remoteinterface::getplatformremotehandle()->SetSysMaskAddr(mstr);
  return SCPI_RES_OK;
}

scpi_result_t SCPI_SetGate(scpi_t *context)
{
  const char* pstr;
  size_t ilen;
  if(!SCPI_ParamString(context, &pstr,&ilen,false))
    {
      return SCPI_RES_ERR;
    }
  QString mstr = QString(QLatin1String(pstr));
  mstr = mstr.mid(0,mstr.indexOf('\r'));
  remoteinterface::getplatformremotehandle()->SetSysGateAddr(mstr);
  return SCPI_RES_OK;
}

scpi_result_t SCPI_SetPort(scpi_t *context)
{
  qint32 ival = -1;
  //volume
  if (!SCPI_ParamInt(context, &ival, false))
    {
      return SCPI_RES_ERR;
    }
  remoteinterface::getplatformremotehandle()->SetSysNetPort(ival);
  return SCPI_RES_OK;
}

scpi_result_t SCPI_SetWifiswitch(scpi_t *context)
{
    qint32 ival = -1;
    if (!SCPI_ParamInt(context, &ival, false))
    {
        return SCPI_RES_ERR;
    }
    //wifi switch
    //remoteinterface::getplatformremotehandle();
    return SCPI_RES_OK;
}

scpi_result_t SCPI_SetWifimib(scpi_t *context)
{
    qint32 ival = -1;
    if (!SCPI_ParamInt(context, &ival, false))
    {
        return SCPI_RES_ERR;
    }
    //wifi
    //remoteinterface::getplatformremotehandle();
    return SCPI_RES_OK;
}

scpi_result_t SCPI_Blueswitch(scpi_t *context)
{
    qint32 ival = -1;
    if (!SCPI_ParamInt(context, &ival, false))
    {
        return SCPI_RES_ERR;
    }
    //bluetooth switch
    //remoteinterface::getplatformremotehandle();
    return SCPI_RES_OK;
}

scpi_result_t SCPI_ClearExcenotic(scpi_t *context)
{
  remoteinterface::getplatformremotehandle()->SetExceNoticClear();
  return SCPI_RES_OK;
}

/**
 * @brief RF_TemptureQ
 * @param context
 * @return
 * @author Johnson
 */
scpi_result_t RF_TemptureQ(scpi_t * context)
{
    qreal rfTmp;

    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    rfTmp = remoteinterface::getplatformremotehandle()->getRfTemp();
    if(!SCPI_ResultDouble(context, rfTmp))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

/**
 * @brief BOARD_TemptureQ
 * @param context
 * @return
 * @author Johnson
 */
scpi_result_t BOARD_TemptureQ(scpi_t * context)
{
    qreal boardTmp;

    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    boardTmp = remoteinterface::getplatformremotehandle()->getBoardTemp();
    if(!SCPI_ResultDouble(context, boardTmp))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

/**
 * @brief FPGA_TemptureQ
 * @param context
 * @return
 * @author Johnson
 */
scpi_result_t FPGA_TemptureQ(scpi_t * context)
{
    qreal fpgaTmp;

    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    fpgaTmp = remoteinterface::getplatformremotehandle()->getFpgaTemp();
    if(!SCPI_ResultDouble(context, fpgaTmp))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

/**
 * @brief BATTERY_TemptureQ
 * @param context
 * @return
 * @author Johnson
 */
scpi_result_t BATTERY_TemptureQ(scpi_t * context)
{
    qreal batteryTmp;

    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    batteryTmp = remoteinterface::getplatformremotehandle()->getBatteryTemp();
    if(!SCPI_ResultDouble(context, batteryTmp))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

/**
 * @brief PlatForm_Config
 * @param context
 * @return
 * @author Johnson
 */
scpi_result_t PlatForm_Config(scpi_t *context)
{
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    QTcpSocket *pTcpSocket = reinterpret_cast<QTcpSocket *>(context->user_context);

    const char* pstr;
    size_t ilen;
    if(!SCPI_ParamString(context, &pstr,&ilen,false))
      {
        return SCPI_RES_ERR;
      }

    QString mstr = QString(QLatin1String(pstr));
    mstr = mstr.mid(0,mstr.indexOf('\r'));

    model::PlatformConfigData pltCf;
    pltCf.fromJson(mstr.toStdString());


    PLTSTATEPARAM rcvData;
    memcpy(&rcvData,&(pltCf.m_data),sizeof(pltCf.m_data));
    remoteinterface::getplatformremotehandle()->refreshPltConfig(rcvData);


    if (pTcpSocket->isValid())
      {
        char data[10];
        memset(data,0,10);
        sprintf(data,"%d",rcvData.orimode);
        pTcpSocket->write(data, sizeof(data));
      }

    return SCPI_RES_OK;
}

/**
 * @brief PlatForm_ConfigQ
 * @param context
 * @return
 * @author Johnson
 */
scpi_result_t PlatForm_ConfigQ(scpi_t *context)
{
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    model::PlatformConfigData tmpPltConfig;

    PLTSTATEPARAM desParam;
    remoteinterface::getplatformremotehandle()->GetPltParam(&desParam);
    memcpy(&(tmpPltConfig.m_data),&desParam,sizeof(PLTSTATEPARAM));

    std::string jsonData;
    tmpPltConfig.toJson(jsonData);

    const char* data = jsonData.c_str();
    qint32 len = strlen(data);

    if(!SCPI_ResultStringSize(context,data,len))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

/**
 * @brief RunMode_Config
 * @param context
 * @return
 * @author Johnson
 */
scpi_result_t RunMode_Config(scpi_t *context)
{
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    const char* pstr;
    size_t ilen;
    if(!SCPI_ParamString(context, &pstr,&ilen,false))
      {
        return SCPI_RES_ERR;
      }

    QString mstr = QString(QLatin1String(pstr));
    mstr = mstr.mid(0,mstr.indexOf('\r'));

    PLTSTATEPARAM desParam;
    remoteinterface::getplatformremotehandle()->GetPltParam(&desParam);

    switch(desParam.orimode)
    {
    case SA_MODE:
    {
        model::SAConfigData SACf;
        SACf.fromJson(mstr.toStdString());

        _SA_ALL_CONF_ tmpStruct;
        memcpy(&tmpStruct,&(SACf.m_data),sizeof(SACf.m_data));
        remoteinterface::getsaremotehandle()->pcontrolInterface->refreshSAConfig(tmpStruct);
    }
        break;
    case RTSA_MODE:
        break;
    case INTERF_MODE:
        break;
    case PM_MODE:
        break;
    case LTE_FDD_MODE:
        break;
    case LTE_TDD_MODE:
        break;
    case FIVE_G_NR:
        break;
    default: break;
    }
    return SCPI_RES_OK;
}

/**
 * @brief RunMode_ConfigQ
 * @param context
 * @return
 * @author Johnson
 */
scpi_result_t RunMode_ConfigQ(scpi_t *context)
{
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;


    PLTSTATEPARAM desParam;
    remoteinterface::getplatformremotehandle()->GetPltParam(&desParam);

    switch(desParam.orimode)
    {
    case SA_MODE:
    {
        model::SAConfigData tmpSAConfig;
        _SA_ALL_CONF_ desSAParam;
        remoteinterface::getsaremotehandle()->pcontrolInterface->getSAParam(desSAParam);
        memcpy(&(tmpSAConfig.m_data),&desSAParam,sizeof(_SA_ALL_CONF_));

        std::string jsonData;
        tmpSAConfig.toJson(jsonData);

        const char* data = jsonData.c_str();
        qint32 len = strlen(data);

        if(!SCPI_ResultStringSize(context,data,len))
        {
            return SCPI_RES_ERR;
        }

    }
        break;
    case RTSA_MODE:
        break;
    case INTERF_MODE:
        break;
    case PM_MODE:
        break;
    case LTE_FDD_MODE:
        break;
    case LTE_TDD_MODE:
        break;
    case FIVE_G_NR:
        break;
    default: break;
    }
    return SCPI_RES_OK;
}

/**
 * @brief Notify_Msg
 * @return
 * @author Johnson
 */
scpi_result_t Notify_Msg()
{
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    model::NotifyConfigData tmpNotifyConfig;

    MODCHG_NOTIC_MSG desParam;
    memcpy(&(tmpNotifyConfig.m_data),&desParam,sizeof(MODCHG_NOTIC_MSG));

    std::string jsonData;
    tmpNotifyConfig.toJson(jsonData);

    const char* data = jsonData.c_str();
    qint32 len = strlen(data);

    return SCPI_RES_OK;
}

/**
 * @brief Deviece_Calibrate
 * @param context
 * @return
 * @author Johnson
 */
scpi_result_t Deviece_Calibrate(scpi_t *context)
{
  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_OK;
  qint32 password = -1;

  //password
  if (!SCPI_ParamInt(context, &password, true))
    {
      return SCPI_RES_ERR;
    }
  if(password != 110201)
  {
      return SCPI_RES_ERR;
  }
  remoteinterface::getplatformremotehandle()->StartDevCalc();
  return SCPI_RES_OK;
}

