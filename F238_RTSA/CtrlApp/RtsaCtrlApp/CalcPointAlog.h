//==============================================================================
//
// Title:		CalcPointAlog.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/3/20 at 10:53:18 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __CalcPointAlog_H__
#define __CalcPointAlog_H__

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
// Include files

//#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types
#ifndef ArrayHandle
#define ArrayHandle void**
#endif   
	
typedef struct Param
{
	double* param;
	int count;
}FREQLIST,*PFREQLIST,CALCRESULTLIST,*PCALCRESULTLIST;
//==============================================================================
// External variables

//==============================================================================
// Global functions
int GetParamFromFile(const char* filedir,PFREQLIST paraminfo);
int ResizeArray(ArrayHandle handle,int arraysize);  

#ifdef __cplusplus
}
#endif

#endif  /* ndef __CalcPointAlog_H__ */
