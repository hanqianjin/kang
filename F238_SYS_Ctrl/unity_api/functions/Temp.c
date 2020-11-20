/*****************************************************************************
Copyright:    2018-2010,  Tech. Co., Ltd.
File name:    temp.c
Description:  Just for temperature reading
Author:       brook.lv
Version:      v1.01
Date:         2018.6.12
History:    

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "Temp.h"

#include "error_functions.h"
#include "unity.h"
#define TEMP_PATH "/sys/class/hwmon/hwmon0/temp1_input"
#define TEMP_RF_PATH "/sys/class/hwmon/hwmon1/temp1_input"

/*************************************************
Function: 		openTemp
Description:    open temperature device node
Calls: 			open
Called By: 		extern
Input: 			null
Output: 		devHandle    --handle of the device node
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 openTemp(DiPSession devHandle)
{
	DiInt32 fd ;

	fd = open(TEMP_PATH, O_RDONLY) ;
	if (fd < 0) {
		errSys("openTemp");
		return SA_TEMP_OPEN;
	}
	
	*devHandle = fd ;
	PRINTF("haha,I am in openTemp\n");
	return DI_SUCCESS;	
}

/*************************************************
Function: 		openTemp_rf
Description:    open temperature device node
Calls: 			open
Called By: 		extern
Input: 			null
Output: 		devHandle    --handle of the device node
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 openTemp_rf(DiPSession devHandle)
{
	DiInt32 fd ;

	fd = open(TEMP_RF_PATH, O_RDONLY) ;
	if (fd < 0) {
		errSys("openTemp");
		return SA_TEMP_OPEN;
	}

	*devHandle = fd ;
	PRINTF("haha,I am in openTemp\n");
	return DI_SUCCESS;	
}
/*************************************************
Function: 		readTemp
Description:    read temperature 
Calls: 			read atol
Called By: 		extern
Input: 			null
Output: 		temp         --temperature
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 readTemp(DiSession devHandle, DiPReal64 temp)
{
	DiInt32 ret ;
	DiChar temp_buf[10] ;

	if (devHandle <= 2) {
		errSys("read temp --handle err\n") ;
		return SA_TEMP_READ;
	}

	memset(temp_buf, 0, sizeof(temp_buf)) ;
	lseek(devHandle,0,SEEK_SET);
	ret = read(devHandle, temp_buf, sizeof(temp_buf));
	if (ret <= 0) {
		errSys("read temp err\n") ;
		return SA_TEMP_READ;
	} 
	*temp = (atol(temp_buf))/1000.0 ;
	
	return DI_SUCCESS ;
}

/*************************************************
Function: 		closeTemp
Description:    close temperature device node
Calls: 			close
Called By: 		extern
Input: 			devHandle    --handler of the device node 
Output: 		null
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 closeTemp(DiSession devHandle)
{
	DiInt32 ret ;
	
	if (devHandle <= 2) {
		errSys("close temp --handle err\n") ;
		return SA_TEMP_CLOSE;
	}
	ret = close(devHandle) ;
	if (ret < 0) {
		errSys("close temp err\n") ;
		return SA_TEMP_CLOSE ;
	}

	PRINTF("haha,I am in closeTemp\n");
	return DI_SUCCESS;
}

static dev_fun_opt* temp_fun;

void init_temp(void)
{
	temp_fun = (dev_fun_opt* )malloc(sizeof(struct dev_fun_opt));
    memset(temp_fun, 0, sizeof(struct dev_fun_opt));
	
	temp_fun->bus_name   = "I2C";
	temp_fun->dev_num    = 0;
	temp_fun->dev_type   = "DEVICE";
	temp_fun->open = openTemp;
	temp_fun->close= closeTemp;	

	register_dev_fun(temp_fun);
}

void exit_temp(void)
{
	free(temp_fun);
	unregister_dev_fun(temp_fun);
}


static dev_fun_opt* temp_rf_fun;

void init_temp_rf(void)
{
	temp_rf_fun = (dev_fun_opt* )malloc(sizeof(struct dev_fun_opt));
    memset(temp_rf_fun, 0, sizeof(struct dev_fun_opt));

	temp_rf_fun->bus_name   = "I2C";
	temp_rf_fun->dev_num    = 1;
	temp_rf_fun->dev_type   = "DEVICE";
	temp_rf_fun->open = openTemp_rf;
	temp_rf_fun->close= closeTemp;	

	register_dev_fun(temp_rf_fun);
}

void exit_temp_rf(void)
{
	free(temp_rf_fun);
	unregister_dev_fun(temp_rf_fun);
}
