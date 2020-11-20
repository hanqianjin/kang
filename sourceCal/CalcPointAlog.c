#include <userint.h>
#include <ansi_c.h>
//==============================================================================
//
// Title:		CalcPointAlog.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/3/20 at 10:53:18 by bityang.
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "CalcPointAlog.h"

//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct seandst
{
	double startp;
	double endp;
	double stepp;
}SESP,*PSTEP;
//==============================================================================
// Static global variables
static const int BUFFERSIZE = 256;
//==============================================================================
// Static functions
static int GetItemsNum(char* str,const char* spestr);  
static int GetRowNum(FILE* fp);  
static int GetTrueItemsNum(PSTEP msesp,int rowNum,FILE* fp); 
static void ProduceParamList(PFREQLIST paraminfo,PSTEP msesp,int rowNum);  
//==============================================================================
// Global variables

//==============================================================================
// Global functions

int GetParamFromFile(const char* filedir,PFREQLIST paraminfo)
{
	FILE* fp = fopen(filedir,"r");
	if(fp == NULL)
	{   
		return -1;
	}
	
	//get row num
	int rowNum = GetRowNum(fp);

	char tempbuf[BUFFERSIZE];
	memset(tempbuf,0,BUFFERSIZE);

	//move away the titles
	if(NULL == fgets(tempbuf,BUFFERSIZE,fp))
	{  
		fclose(fp);
		return -1;
	}
	
	GetItemsNum(tempbuf," ");

	PSTEP msesp = (PSTEP)malloc(sizeof(SESP) * rowNum);
	if(NULL == msesp)
	{
		fclose(fp);
		return -1;
	}				 
	int buffersize = GetTrueItemsNum(msesp,rowNum,fp);
	ResizeArray((void*)paraminfo,buffersize);
	//save freq value
	ProduceParamList(paraminfo,msesp,rowNum);

	if(NULL != msesp)
		free(msesp);
	if(NULL != fp)
		fclose(fp);
	return 0;
}



static int  GetItemsNum(char* str,const char* spestr)
{
	int iTemp = 0;
	if(NULL == str)
		return iTemp;
	
	_mbstok ((unsigned char*)str,(const unsigned char*)spestr);
	iTemp++;
	
	const unsigned char space[] = {' '};
	while(NULL != _mbstok (NULL,space))
	{
		iTemp++;
	}
	
	return iTemp;
}

//get row num 
static int GetRowNum(FILE* fp)
{
	int iBack = 0;
	int rowNum = 0;
	if((iBack = fscanf(fp,"%d\n",&rowNum))<0)
	{   
		fclose(fp);
		fp = NULL;
		return iBack;
	}
	return rowNum;
}

//calc freq points num
static int GetTrueItemsNum(PSTEP msesp,int rowNum,FILE* fp)
{
	double temp_s =0.0,temp_e =0.0,temp_st =0.0;
	int buffersize=0,i = 0;
	for(i = 0; i<rowNum; i++)
	{
		fscanf(fp,"%lf %lf %lf",&temp_s,&temp_e,&temp_st);
		(msesp+i)->startp = temp_s;
		(msesp+i)->endp =  temp_e;
		(msesp+i)->stepp = temp_st;
		if(0.0 == (msesp+i)->stepp)
		{
			buffersize++;
		}
		else
		{
			buffersize += (int)((temp_e - temp_s) / temp_st + 0.5);
		}
	}
	buffersize++;
	return buffersize;
}

//get param list of start¡¢stop and step freq
//every row uninclude the stop freq
static void ProduceParamList(PFREQLIST paraminfo,PSTEP msesp,int rowNum)
{
	//FILE* fp9 = fopen("saclacconfig\\test.txt","w");
	int icircle = 0;
	int i = 0,j = 0,iTemp = 0;
	for(i = 0; i<rowNum; i++)
	{
		if((msesp+i)->endp == (msesp+i)->startp)
		{
			*(paraminfo->param+(icircle++)) = (msesp+i)->startp;
			//fprintf(fp9,"%.2lf\n",(msesp+i)->startp);
		}
		else
		{
			iTemp = (int)(((msesp+i)->endp - (msesp+i)->startp)/ (msesp+i)->stepp + 0.5);
			for(j = 0; j<iTemp; j++)
			{
				*(paraminfo->param+(icircle++)) = (msesp+i)->startp + ((msesp+i)->stepp)*j;
				//fprintf(fp9,"%.2lf\n",(msesp+i)->startp + ((msesp+i)->stepp)*j);
			}
		}
	}
	*(paraminfo->param + icircle) = (msesp+rowNum-1)->endp;
	//fprintf(fp9,"%.2lf\n",(msesp+rowNum-1)->endp);
	//fclose(fp9);
	return;
}

//resize the maloc buffer 
int ResizeArray(ArrayHandle handle,int arraysize)
{
	if(arraysize <0 || NULL == handle)
	{
		return -1;
	}

	PFREQLIST tempPtr = (PFREQLIST)handle;
	
	//new buffer smaller
	if(tempPtr->count > arraysize)
	{
		tempPtr->param = (double*)realloc(tempPtr->param,sizeof(double)*arraysize);
		if(NULL == tempPtr->param)
			return -1;
	}
	else
	{
		if(tempPtr->param != NULL)
		{
			free(tempPtr->param);
		}
		tempPtr->param = (double*)malloc(sizeof(double)*arraysize);
		if(NULL == tempPtr->param)
			return -1;
	}
	tempPtr->count = arraysize;
	return 0;
}


