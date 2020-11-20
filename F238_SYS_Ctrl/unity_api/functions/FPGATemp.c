/*****************************************************************************
Copyright:    2018-2010,  Tech. Co., Ltd.
File name:    FpgaTemp.c
Description:  Just for fpga temperature reading
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

#include "error_functions.h"
#include "unity.h"
#define FPGA_TEMP_PATH "/sys/devices/soc0/amba/f8007100.adc/iio\:device0/in_temp0_raw"

/*************************************************
Function: 		openFpgaTemp
Description:    open temperature device node
Calls: 			open
Called By: 		extern
Input: 			null
Output: 		devHandle    --handle of the device node
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 openFpgaTemp(DiPSession devHandle)
{
	DiInt32 fd ;

	fd = open(FPGA_TEMP_PATH, O_RDONLY) ;
	if (fd < 0) {
		errSys("openTemp");
		return SA_TEMP_OPEN;
	}
	
	*devHandle = fd ;
	PRINTF("haha,I am in openTemp\n");
	return DI_SUCCESS;	
}

/*************************************************
Function: 		readFpgaTemp
Description:    read temperature 
Calls: 			read atol
Called By: 		extern
Input: 			null
Output: 		temp         --temperature
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 readFpgaTemp(DiSession devHandle, DiPReal64 temp)
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
	*temp = atol(temp_buf) * 503.975 / 4096 - 273.15 ;
	
	return DI_SUCCESS ;
}

/*************************************************
Function: 		closeFpgaTemp
Description:    close temperature device node
Calls: 			close
Called By: 		extern
Input: 			devHandle    --handler of the device node 
Output: 		null
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 closeFpgaTemp(DiSession devHandle)
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

static dev_fun_opt* fpga_temp_fun;

void init_fpga_temp(void)
{
	fpga_temp_fun = (dev_fun_opt* )malloc(sizeof(struct dev_fun_opt));
    memset(fpga_temp_fun, 0, sizeof(struct dev_fun_opt));
	
	fpga_temp_fun->bus_name   = "VIRTUAL";
	fpga_temp_fun->dev_num    = 7;
	fpga_temp_fun->dev_type   = "DEVICE";
	fpga_temp_fun->open = openFpgaTemp;
	fpga_temp_fun->close= closeFpgaTemp;	

	register_dev_fun(fpga_temp_fun);
}

void exit_fpga_temp(void)
{
	free(fpga_temp_fun);
	unregister_dev_fun(fpga_temp_fun);
}


