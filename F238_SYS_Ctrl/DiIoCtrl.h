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

#ifndef __DiIoCtrl_H__
#define __DiIoCtrl_H__

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

//by steve 0925
#define BIT_DEBUG 0//1 means simulate
//Johnson 190813
#define FREQ_COUNT 1//1 means open,0 means close
//Johson 191011
#define BIT_F239 
//Johnson 191101
//#define BIT_F238_SMART
//#define BIT_F238
//Johnson 191025
#define DEBUG_OUTPUT 1//1 means debug message output,0 means debug message close 

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================

DiInt32 BitOpen(DiRsrc rsrcName,DiPSession devHandle); 

DiInt32 BitWrite32(DiSession devHandle,DiUInt32 addr,DiUInt32 value);
DiInt32 BitRead32(DiSession devHandle,DiUInt32 addr,DiPUInt32 value); 
DiInt32 BitMoveOut8(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt8 buf8);
DiInt32 BitMoveOut16(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt16 buf16); 
DiInt32 BitMoveOut32(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt32 buf32);
DiInt32 BitMoveOut64(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt64 buf64);

DiInt32 BitWrite32Ex(DiSession devHandle,DiUInt32 space,DiBusAddress offset,DiUInt32 value);
DiInt32 BitRead32Ex(DiSession devHandle,DiUInt32 space,DiBusAddress offset,DiPUInt32 value);
DiInt32 BitMoveOut8Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt8 buf8);
DiInt32 BitMoveOut16Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt16 buf16); 
DiInt32 BitMoveOut32Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt32 buf32);
DiInt32 BitMoveOut64Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt64 buf64);

DiInt32 BitClose(DiSession devHandle);


//Albert add flaot data write
DiInt32 BitReadFloat32(DiSession devHandle,DiUInt32 addr,DiPReal32 value); 
DiInt32 BitWriteFloat32(DiSession devHandle,DiUInt32 addr,DiReal32 value);
DiInt32 BitMoveOutFloat32(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPReal32 buf32);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __DiIoCtrl_H__ */
