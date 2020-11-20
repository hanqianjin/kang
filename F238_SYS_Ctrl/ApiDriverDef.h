/**
*   Title:		ApiDriverDef.h
*   Purpose:    Unity def for Api Driver
*   
*   Created on: 2018/10/26.
*   Copyright:	. All Rights Reserved.
*/
#ifndef _API_DRIVER_DEF_H
#define _API_DRIVER_DEF_H
#include "BitVisaType.h"
#include "SaDataStruct.h"
//! Albert 1026 define Driver Handle
//  0 means cur dev can not use


//!Albert enum must correspond Driver_func array
enum
{
    DEV_SUNDRY = 0,
    DEV_GPS,    
    DEV_TEMP_MAIN,
    DEV_TEMP_RF,
    DEV_BATTERY,
    DEV_FM,
//    DEV_UDISK, 
    DEV_FPGA_TEMP,       
};

typedef struct Driver_func
{
	char *dev_name;
	DiSession dev_handle;

}Driver_func;
#endif
