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
