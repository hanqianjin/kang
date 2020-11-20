/*****************************************************************************
Copyright:    2018-2010,  Tech. Co., Ltd.
File name:    FPGATemp.c
Description:  Just for temperature reading
Author:       brook.lv
Version:      v1.01
Date:         2018.6.12
History:    

*****************************************************************************/

#ifndef __FPGA_TEMP_H__
#define __FPGA_TEMP_H__

#ifdef __cplusplus
    extern "C" {
#endif
#include "BitVisaType.h"

DiInt32 openFpgaTemp(DiPSession devHandle) ;
DiInt32 readFpgaTemp(DiSession devHandle, DiPReal64 temp) ;
DiInt32 closeFpgaTemp(DiSession devHandle) ;

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __FPGA_TEMP_H__ */
