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

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions
void* MidMsgFunc(void *functionData); 
DiInt32 InitTriggerParam();

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __MidMsg_H__ */
