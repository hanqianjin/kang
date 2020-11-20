
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
//#include "BitVisaType.h"
#include <qglobal.h>

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

qint32 openDPXMem(quint32* devHandle);
void* getDPXAddr(quint32 devHandle);
qint32 registerDPXHandler(quint32 devHandle, void(*func)(void *));
qint32 unregisterDPXHandler(quint32 devHandle);
qint32 closeDPXMem(quint32 devHandle);


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __DiIoCtrl_H__ */

