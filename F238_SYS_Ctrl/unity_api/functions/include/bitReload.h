/*****************************************************************************
Copyright:    2018-2010,  Tech. Co., Ltd.
File name:    bitReload.h
Description:  Just for reload bitfile
Author:       brook.lv
Version:      v1.01
Date:         2019.2.11
History:    

*****************************************************************************/

#ifndef __BITRELOAD_H__
#define __BITRELOAD_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "BitVisaType.h"

typedef struct _tReloadInfo
{
    DiInt32 gps_handle;
    DiInt32 load_time;//the sh run time in ms
}ReloadInfo;

DiInt32 ReloadBitfile(DiString bitfile, ReloadInfo* ri);

#ifdef __cplusplus
}   
#endif

#endif  /* ndef __BITRELOAD_H__*/


