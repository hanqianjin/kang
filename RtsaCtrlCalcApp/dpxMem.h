
/*****************************************************************************
Copyright:    2018-2010,  Tech. Co., Ltd.
File name:    DiIoCtrl.c
Description:  Read and write the DRAM in PL
Author:       brook.lv
Version:      v1.01
Date:         2018.6.12
NOTE:         When write, address MUST be 4 Bytes aligned, 
History:    

*****************************************************************************/

#ifndef __DiDPX_H__
#define __DiDPX_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include <stdlib.h>
#include <stdio.h>
#include "BitVisaType.h"    

//==============================================================================
// Constants
#define TESTUNIT 0
#define ESP (1.0e-3)  
//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================

#define MMAP_SIZE 0x400000

DiInt32 openDPXMem(DiPSession devHandle); 
void* getDPXAddr(DiSession devHandle); 
DiInt32 registerDPXHandler(DiSession devHandle, void(*func)(void *));
DiInt32 unregisterDPXHandler(DiSession devHandle);
DiInt32 closeDPXMem(DiSession devHandle);


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __DiIoCtrl_H__ */

