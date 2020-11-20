//==============================================================================
//
// Title:		SaAnalysis.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/1/20 at 11:34:57 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __SWEEP_INTERUPT_H__
#define __SWEEP_INTERUPT_H__

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
// Include files
#include <sys/ipc.h>
#include <sys/sem.h>
#include "DiIoCtrl.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions
int OpenPlInterrupt();
void PlInterruptValue(int * keyValue);
void ClosePlInterrupt();
#ifdef __cplusplus
}
#endif

#endif  /* ndef __SaAnalysis_H__ */
