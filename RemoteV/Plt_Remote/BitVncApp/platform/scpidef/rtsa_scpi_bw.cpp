#include "rtsa_scpi_bw.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

extern scpi_result_t GetDoubleFreqVal(scpi_t *context,quint64 *val);
//scpi_result_t GetDoubleFreqVal(scpi_t *context, qreal *val)
//{
//    qreal value = 0.0;
//    const char* pstr;
//    size_t ilen = 0;

//    if (Mode_local == g_systemStatus.mode)
//      {
//        return SCPI_RES_ERR;
//      }
//    if (!SCPI_ParamDouble(context, &value, true))
//      {
//        return SCPI_RES_ERR;
//      }
//    //parse freq unit
//    if(SCPI_ParamString(context, &pstr,&ilen,false))
//      {
//        QString mstr = QString(QLatin1String(pstr));
//        qint32 iIndex = plf_compre_frequnit(mstr.mid(0,mstr.indexOf('\r')));
//        if(iIndex)
//        {
//            value *= *(PLF_FREQ_UNIT_MULTIPLE + iIndex);
//        }
//      }
//    *val = (qreal)value;
//    return SCPI_RES_OK;
//}

scpi_result_t RTSA_BANDWIDTH_AutoRbw(scpi_t *context)
{
    qint32 isAuto;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &isAuto, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setBWAuto(isAuto);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_BANDWIDTH_Rbw(scpi_t *context)
{
    qint32 ival = 0;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &ival, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setBWIndex(ival);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_BANDWIDTH_FFTWindow(scpi_t *context)
{
    qint32 ival = 0;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &ival, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setFFTWindow(ival);
    return SCPI_RES_OK;
}



scpi_result_t RTSA_BANDWIDTH_AutoRbwQ(scpi_t *context)
{
    qint32 isAuto;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    isAuto = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsBWAuto();
    if(!SCPI_ResultInt(context, isAuto))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_BANDWIDTH_RbwQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getBWIndex();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_BANDWIDTH_FFTWindowQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getFFTWindow();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

