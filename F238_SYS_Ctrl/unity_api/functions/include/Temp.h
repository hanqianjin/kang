/*****************************************************************************
Copyright:    2018-2010,  Tech. Co., Ltd.
File name:    Temp.c
Description:  Just for temperature reading
Author:       brook.lv
Version:      v1.01
Date:         2018.6.12
History:    

*****************************************************************************/

#ifndef __TEMP_H__
#define __TEMP_H__

#ifdef __cplusplus
    extern "C" {
#endif
#include "BitVisaType.h"

DiInt32 openTemp(DiPSession devHandle) ;
DiInt32 readTemp(DiSession devHandle, DiPReal64 temp) ;
DiInt32 closeTemp(DiSession devHandle) ;

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __TEMP_H__ */
