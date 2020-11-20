//==============================================================================
//
// Title:		DiIoCtrl.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/1/11 at 11:17:56 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

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
#define TESTUNIT 1
#define ESP (1.0e-3)  
//==============================================================================
// Types

//#define BIT_F238
#define BIT_F239
//		#define BIT_F238_SMART
//==============================================================================
// External variables

//==============================================================================
// Global functions 
/*
purpose: get the ctrl handle of the device by rsrcName
func:BitOpen
param:<in>rsrcName:the description string of the device which used to open it
      <out>devHandle:the pointer of the dev handle 
return:>=0 is ok
 */
DiInt32 BitOpen(DiRsrc rsrcName,DiPSession devHandle); 

DiInt32 BitWrite32(DiSession devHandle,DiUInt32 addr,DiUInt32 value);
DiInt32 BitRead32(DiSession devHandle,DiUInt32 addr,DiPUInt32 value); 
DiInt32 BitMoveOut8(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt8 buf8);
DiInt32 BitMoveOut16(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt16 buf16); 
DiInt32 BitMoveOut32(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt32 buf32);

DiInt32 BitWrite32Ex(DiSession devHandle,DiUInt32 space,DiBusAddress offset,DiUInt32 value);
DiInt32 BitRead32Ex(DiSession devHandle,DiUInt32 space,DiBusAddress offset,DiPUInt32 value);
DiInt32 BitMoveOut8Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt8 buf8);
DiInt32 BitMoveOut16Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt16 buf16); 
DiInt32 BitMoveOut32Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt32 buf32);

DiInt32 BitClose(DiSession devHandle); 
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __DiIoCtrl_H__ */
