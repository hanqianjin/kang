/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:
** Latest Version: V0.0.1
** Latest modified Date:  2019-02-11
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2019-02-11
** Descriptions:for remote control to get handle
**
*********************************************************************************************************/
#include "remoteinterface.h"

BitSA* remoteinterface::premotesa = NULL;
BitRtSa* remoteinterface::premotertsa = NULL;
quint32* remoteinterface::nowanamode = NULL;
BitPlatForm* remoteinterface::premoteplatform = NULL;
BitLteFdd* remoteinterface::premotefdd = NULL;
BitLteTdd* remoteinterface::premotetdd = NULL;
BitNr* remoteinterface::premotefgnr = NULL;
remoteinterface::remoteinterface()
{

}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note will increase by lte and so on
 * @author steve
 * @since {2019-02-11}
*/
void remoteinterface::SetRemoteSaHandle(BitSA *phandle)
{
  premotesa = phandle;
  return;
}

void remoteinterface::SetRemoteRtsaHandle(BitRtSa *phandle)
{
  premotertsa = phandle;
  return;
}

/**
 * @brief get ana mode from platform
 * @param[in]
 * @param[in]
 * @return
 * @note when remote ctrl through this handle to decide which interface to use
 * @author steve
 * @since {2019-02-28}
*/
void remoteinterface::SetAnaModeHandle(quint32 *panamode)
{
  nowanamode = panamode;
  return;
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
void remoteinterface::SetPlatFormHandle(BitPlatForm *phandle)
{
  premoteplatform = phandle;
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-07-02}
*/
void remoteinterface::SetRemoteFddHandle(BitLteFdd *phandle)
{
  premotefdd = phandle;
  return;
}

void remoteinterface::SetRemoteTddHandle(BitLteTdd *phandle)
{
  premotetdd = phandle;
  return;
}

void remoteinterface::SetRemoteFgnrHandle(BitNr *phandle)
{
  premotefgnr = phandle;
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note will increase by lte...
 * @author steve
 * @since {2019-02-11}
*/
BitSA *remoteinterface::getsaremotehandle()
{
  return premotesa;
}

BitRtSa *remoteinterface::getrtsaremotehandle()
{
  return premotertsa;
}

quint32 remoteinterface::getanamodehandle()
{
  return *nowanamode;
}

BitPlatForm *remoteinterface::getplatformremotehandle()
{
  return premoteplatform;
}

BitLteFdd *remoteinterface::getfddremotehandle()
{
  return premotefdd;
}

BitLteTdd *remoteinterface::gettddremotehandle()
{
  return premotetdd;
}

BitNr *remoteinterface::getfgnrremotehandle()
{
  return premotefgnr;
}
