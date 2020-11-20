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


#include "remoteinterface.h"
#include "multicommu/localcommunicate.h"

#include "multicommu/threadmsg.h"
#define KEY_MSG_RECV 3434

#include "multicommu/scpiport_internet.h"
#include "multicommu/scpiport_uart.h"
#include "multicommu/scpiport_usb.h"

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
              return pTcpSocket->write(data, len);
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
  scpi_context.buffer.length = 1024;
  scpi_context.buffer.data = (char *)malloc(2048);
  SCPI_Init(&scpi_context);


  //g_pPortUart = new ScpiPort_uart();
  //g_pPortUsb = new ScpiPort_usb();
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

scpi_result_t COMM_TransFile(scpi_t * context)
{
  size_t len_name;
  const char *file_name;
  int file_len;
  if (!SCPI_ParamInt(context, &file_len,1))
    {
      return SCPI_RES_ERR;
    }
  if (!SCPI_ParamString(context, &file_name, &len_name, 1))
    {
      return SCPI_RES_ERR;
    }
  switch(g_systemStatus.mode)
    {
    case Mode_remote_internet:
      g_pPortInterNet->initTransFile(QString(file_name),file_len);
      break;
    case Mode_remote_uart:
      g_pPortUart->initTransFile(QString(file_name),file_len);
      break;
    case Mode_remote_usb:
      g_pPortUsb->initTransFile(QString(file_name),file_len);
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

  SCPI_CMD_LIST_END//end flag
};

scpi_command_t ltetdd_scpi_commands[] = {
  SCPI_COMMANDS_MISC

  SCPI_CMD_LIST_END//end flag
};

scpi_command_t ltefdd_scpi_commands[] = {
  SCPI_COMMANDS_MISC

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
