//==============================================================================
//
// Title:		MidMsg.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/1/11 at 8:39:55 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __MidMsg_H__
#define __MidMsg_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files	 
#include <unistd.h>		
#include "SaDataStruct.h"
#include "BitVisaType.h"
#include "ApiDriverDef.h"
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions
void* MidMsgFunc(void *functionData); 
//Albert 1026 add
DiInt32 InitSysApiDev();
//Albert 0307 add
DiInt32 CloseApiDev();
// Albert 03/15 add
DiInt32 RegisterUDisk();
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __MidMsg_H__ */
