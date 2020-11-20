/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:
** Latest Version: V0.0.1
** Latest modified Date:  2019-02-28
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2019-02-28
** Descriptions:
**
*********************************************************************************************************/
#include "rtsa_scpi_freq.h"
#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;
scpi_result_t GetDoubleFreqVal(scpi_t *context, qreal *val);
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Center_Freq(scpi_t *context)
{
  if(g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;
  qreal ival = 0;
  scpi_result_t iback = GetDoubleFreqVal(context,&ival);
  if(iback)
    {
      remoteinterface::getrtsaremotehandle()->InterfaceObj->setCenterFreq(ival);
    }
  return iback;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Start_Freq(scpi_t * context)
{
  if(g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;
  qreal ival = 0;
  scpi_result_t iback = GetDoubleFreqVal(context,&ival);
  if(iback)
    {
      remoteinterface::getrtsaremotehandle()->InterfaceObj->setStartFreq(ival);
    }
  return iback;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Stop_Freq(scpi_t * context)
{
  if(g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;
  qreal ival = 0;
  scpi_result_t iback = GetDoubleFreqVal(context,&ival);
  if(iback)
    {
      remoteinterface::getrtsaremotehandle()->InterfaceObj->setStopFreq(ival);
    }
  return iback;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Step_Freq(scpi_t * context)
{
  if(g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;
  qreal ival = 0;
  scpi_result_t iback = GetDoubleFreqVal(context,&ival);
  if(iback)
    {
      remoteinterface::getrtsaremotehandle()->InterfaceObj->setCFStep(ival);
    }
  return iback;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Freq_Span(scpi_t * context)
{
  qreal ival = 0;
  if(g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;
  scpi_result_t iback = GetDoubleFreqVal(context,&ival);
  if(iback)
    {
      remoteinterface::getrtsaremotehandle()->InterfaceObj->setSpan(ival);
    }
  return iback;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Freq_FullSpan(scpi_t * context)
{
  quint64 ival = 0;
  Q_UNUSED(context)
  if(g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;
  remoteinterface::getrtsaremotehandle()->InterfaceObj->setFullSpan();
  return SCPI_RES_OK;
}

scpi_result_t RTSA_FREQUENCY_Offset_Freq(scpi_t * context)
{
    qreal ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetDoubleFreqVal(context,&ival);
    if(iback)
      {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setFreqOffset(ival);
      }
    return iback;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Channel_Standard(scpi_t * context)
{
    qint32 ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &ival, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setCHStandard(ival);

    return SCPI_RES_OK;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Channel_Standard_BandIndex(scpi_t * context)
{
    qint32 ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &ival, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setBandIndex(ival);

    return SCPI_RES_OK;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Channel_Number(scpi_t * context)
{
    qint32 ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &ival, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setChannelNumber(ival);

    return SCPI_RES_OK;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Channel_Step(scpi_t * context)
{
    qint32 ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &ival, true))
    {
        return SCPI_RES_ERR;
    }
//    remoteinterface::getrtsaremotehandle()->InterfaceObj->setChannelNumber(ival);

    return SCPI_RES_OK;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Channel_Type(scpi_t * context)
{
    qint32 ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &ival, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setCommuDirection(ival);

    return SCPI_RES_OK;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Center_FreqQ(scpi_t * context)
{
    qreal centerFreq;

    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    centerFreq = remoteinterface::getrtsaremotehandle()->InterfaceObj->getCenterFreq();
    if(!SCPI_ResultDouble(context, centerFreq))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Start_FreqQ(scpi_t * context)
{
    qreal startFreq;
    if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;

    startFreq = remoteinterface::getrtsaremotehandle()->InterfaceObj->getStartFreq();
    if(!SCPI_ResultDouble(context, startFreq))
    {
      return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Stop_FreqQ(scpi_t * context)
{
    qreal stopFreq;
    if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;

    stopFreq = remoteinterface::getrtsaremotehandle()->InterfaceObj->getStopFreq();
    if(!SCPI_ResultDouble(context, stopFreq))
    {
      return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Step_FreqQ(scpi_t * context)
{
    qreal stepFreq;
    if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;

    stepFreq = remoteinterface::getrtsaremotehandle()->InterfaceObj->getCFStep();
    if(!SCPI_ResultDouble(context, stepFreq))
    {
      return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Freq_SpanQ(scpi_t * context)
{
    qreal spanFreq;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    spanFreq = remoteinterface::getrtsaremotehandle()->InterfaceObj->getSpan();
    if(!SCPI_ResultDouble(context, spanFreq))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Freq_OffsetQ(scpi_t * context)
{
    qreal OffsetFreq;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    OffsetFreq = remoteinterface::getrtsaremotehandle()->InterfaceObj->getFreqOffset();
    if(!SCPI_ResultDouble(context, OffsetFreq))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Channel_StandardQ(scpi_t * context)
{
    qint32 standardIndex;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    standardIndex = remoteinterface::getrtsaremotehandle()->InterfaceObj->getCHStandard();
    if(!SCPI_ResultInt(context, standardIndex))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Channel_Standard_BandIndexQ(scpi_t * context)
{
    qint32 bandIndex;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    bandIndex = remoteinterface::getrtsaremotehandle()->InterfaceObj->getBandIndex();
    if(!SCPI_ResultInt(context, bandIndex))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Channel_NumberQ(scpi_t * context)
{
    qint32 channelNum;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    channelNum = remoteinterface::getrtsaremotehandle()->InterfaceObj->getChannelNumber();
    if(!SCPI_ResultInt(context, channelNum))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Channel_StepQ(scpi_t * context)
{
//    qint32 channelNum;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

//    channelNum = remoteinterface::getrtsaremotehandle()->InterfaceObj->getChannelNumber();
//    if(!SCPI_ResultInt(context, channelNum))
//      {
//        return SCPI_RES_ERR;
//      }
    return SCPI_RES_OK;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t RTSA_FREQUENCY_Channel_TypeQ(scpi_t * context)
{
    qint32 channelNum;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    channelNum = remoteinterface::getrtsaremotehandle()->InterfaceObj->getCommuDirection();
    if(!SCPI_ResultInt(context, channelNum))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
scpi_result_t GetDoubleFreqVal(scpi_t *context, qreal *val)
{
    qreal value = 0.0;
    const char* pstr;
    size_t ilen = 0;

    if (Mode_local == g_systemStatus.mode)
      {
        return SCPI_RES_ERR;
      }
    if (!SCPI_ParamDouble(context, &value, true))
      {
        return SCPI_RES_ERR;
      }
    //parse freq unit
    if(SCPI_ParamString(context, &pstr,&ilen,false))
      {
        QString mstr = QString(QLatin1String(pstr));
        qint32 iIndex = plf_compre_frequnit(mstr.mid(0,mstr.indexOf('\r')));
        if(iIndex)
        {
            value *= *(PLF_FREQ_UNIT_MULTIPLE + iIndex);
        }
      }
    *val = (qreal)value;
    return SCPI_RES_OK;
}
