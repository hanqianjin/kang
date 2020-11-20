/*****************************************************************************
Copyright:    2018-2010,  Tech. Co., Ltd.
File name:    Touch.c
Description:  For touchscreen enable/disable
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
#include "Touch.h"

#include "error_functions.h"
#include "unity.h"
#ifdef  BIT_OLD_LCD
#define TOUCH_PATH "/sys/bus/i2c/drivers/icn85xx/icn_suspend"
#endif
#ifdef BIT_NEW_LCD
#define TOUCH_PATH "/sys/bus/i2c/drivers/ilitek_ts/ilitek_suspend"
#endif
static int g_open;

/*************************************************
Function: 		enableTouch
Description:    enable touchscreen 
Calls: 			
Called By: 		extern
Input: 			null
Output: 		devHandle    --handle of the device node
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 enableTouch(DiPSession devHandle)
{
	
	DiInt32 fd ;
	DiInt32 ret ;
	char * temp_buf = "0";

    fd = open(TOUCH_PATH, O_WRONLY) ;
    if (fd < 0) {
        errSys("openTouch");
    	return SA_TEMP_OPEN;
    }
	ret = write(fd, temp_buf, sizeof(temp_buf));
	if (ret <= 0) {
		errSys("write touch err\n") ;
		return SA_TEMP_READ;
	}
	close(fd);
	
	PRINTF("haha,I am in enableTouch\n");
	return DI_SUCCESS;	
}

/*************************************************
Function: 		readTouchState
Description:    read touchscreen state
Calls: 			read atol
Called By: 		extern
Input: 			null
Output: 		temp         --temperature
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 readTouchState(DiSession devHandle, DiPInt32 state)
{
	DiInt32 fd ;
	DiInt32 ret ;
	DiChar temp_buf[10] ;
	DiChar temp_buf1[10] = "suspend" ;
	int i;
	
    fd = open(TOUCH_PATH, O_RDONLY) ;
    if (fd < 0) {
        errSys("openTouch");
    	return SA_TEMP_OPEN;
    }
	memset(temp_buf, '\0', sizeof(temp_buf)) ;
	lseek(devHandle,0,SEEK_SET);
	ret = read(fd, temp_buf, sizeof(temp_buf));
	if (ret <= 0) {
		errSys("read temp err\n") ;
		return SA_TEMP_READ;
	}
	close(fd);

	if (!strcmp("suspend\n", temp_buf)) {
		*state = 1;
	}
	else if(!strcmp("resume\n", temp_buf)) {
		*state = 0;
	}
	
	return DI_SUCCESS ;
}

/*************************************************
Function: 		disableTouch
Description:    disable touchscreen
Calls: 			close
Called By: 		extern
Input: 			devHandle    --handler of the device node 
Output: 		null
Return: 	    DI_SUCCESS   --success
				less than 0  --err
Others: 		NULL
*************************************************/
DiInt32 disableTouch(DiSession devHandle)
{
	DiInt32 fd ;
	DiInt32 ret ;
	char * temp_buf = "1";

    fd = open(TOUCH_PATH, O_WRONLY) ;
    if (fd < 0) {
        errSys("openTouch");
    	return SA_TEMP_OPEN;
    }
	ret = write(fd, temp_buf, sizeof(temp_buf));
	if (ret <= 0) {
		errSys("write touch err\n") ;
		return SA_TEMP_READ;
	}
	ret = close(fd);
	
	PRINTF("haha,I am in disableTouch\n");
	return DI_SUCCESS;
}


