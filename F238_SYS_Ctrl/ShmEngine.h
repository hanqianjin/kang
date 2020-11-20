//==============================================================================
//
// Title:		ShmEngine.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/1/11 at 11:17:56 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __ShmEngine_H__
#define __ShmEngine_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files
#include <stdio.h>
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
DiInt32 IniShmCtrl(void* param);
DiInt32 CloseShmCtrl(void* param);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __ShmEngine_H__ */
