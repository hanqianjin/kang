/****************************************Copyright (c)****************************************************
**
**                                     INNO Instrument(China) Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                bitvnchandle.cpp
** Latest Version:           V1.0.0
** Created by:               Tony
** Created date:             2019/07/08
** Descriptions:             Set or get handle
**
*********************************************************************************************************/

#include "bitvnchandle.h"

//#include "scpidef/sa_scpidef.h"
//#include "bitplatform.h"
//#include "bitvnc_internet.h"

sa_scpidef *BitVncHandle::pHandleSa = 0;
BitPlatForm *BitVncHandle::pBitApp = 0;
bitvnc_internet *BitVncHandle::pCommuInter = 0;

BitVncHandle::BitVncHandle()
{

}

void BitVncHandle::SetScpiHandle(sa_scpidef *Handle)
{
    pHandleSa = Handle;
    return;
}

sa_scpidef *BitVncHandle::GetScpiHandle()
{
    return pHandleSa;
}

void BitVncHandle::SetVncAppHandle(BitPlatForm *Handle)
{
    pBitApp = Handle;
    return;
}

BitPlatForm *BitVncHandle::GetVncAppHandle()
{
    return pBitApp;
}

void BitVncHandle::SetVncInternetHandle(bitvnc_internet *Handle)
{
    pCommuInter = Handle;
    return;
}

bitvnc_internet *BitVncHandle::GetVncInternetHandle()
{
    return pCommuInter;
}

