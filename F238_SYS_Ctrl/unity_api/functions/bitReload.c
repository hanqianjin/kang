/*****************************************************************************
Copyright:    2018-2010,  Tech. Co., Ltd.
File name:    temp.c
Description:  Just for reload bitfile
Author:       brook.lv
Version:      v1.01
Date:         2019.2.11
History:    

*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#define  __DEBUG
#include "error_functions.h"
#include "SysDev.h"
#include "bitReload.h"
#include "unity.h"
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



static int setFileValue(char *fileName, int value)
{
	int fd;
	
	if (fileName == NULL)
		return -1;
	else {
		fd = open(fileName, O_WRONLY);
		if (fd < 0) {
			errUser("open %s\n", fileName);
			return -1;
		}
	}
	if (value== 1) {
		write(fd, "1", strlen("1"));
	}
	else if(value == 2) {
		write(fd, "2", strlen("2"));
	}
	else {
		write(fd, "0", strlen("0"));
	}

	close(fd);

	return DI_SUCCESS;
}

/*************************************************
Function:       ReloadBitfile
Description:    reload bitfile after system has been spring up
Calls:          gpsDevSuspend system gpsDevResume
Called By:      extern
Input:          bitfile      --bitfile name
                ri           --other parm needed
Output:         null
Return:         DI_SUCCESS   --success
                less than 0  --err
                Others:         NULL
*************************************************/
DiInt32 ReloadBitfile(DiString bitfile, ReloadInfo* ri)
{
    char bitload_cmd[50] = "./bitstream.sh ";
    int ret;
    FILE* fp = NULL;
	char buf[256];

    if (bitfile != NULL) {
       // strcat(bitload_cmd, bitfile);
       sprintf(bitload_cmd, "sh ./bitstream.sh %s\n", bitfile);
    }
/*    ret = gpsDevSuspend(ri->gps_handle);
    if (ret < 0) {
        return ret;
    }*/

    BackLightEpollSuspend(0);

    PRINTF("%s\n", bitload_cmd);
	setFileValue("/sys/devices/soc0/43000000.ps7-lcdc/pl_bg/bg_flag", 2);
	setFileValue("/sys/devices/soc0/amba_pl/amba_pl:mcu-interrupt/mcu_interrupt/mcu_interrupt_flag", 0);
#ifdef BIT_OLD_LCD
setFileValue("/sys/bus/i2c/drivers/icn85xx/icn_suspend", 1);
#endif
#ifdef BIT_NEW_LCD
	setFileValue("/sys/bus/i2c/drivers/ilitek_ts/ilitek_suspend",1);
#endif
	setFileValue("/sys/devices/soc0/amba/amba:matrix-keyboard/matrix_gpio", 0);
	setFileValue("/sys/devices/soc0/amba_pl/80021000.serial/usart_pl/usart_flag", 1);
	setFileValue("/sys/devices/soc0/amba_pl/80028000.serial/usart_pl/usart_flag", 1);

    ret = system(bitload_cmd);
    //printf("bitfile system ret:%d\n", ret);
    if (ret == -1) {
        printf("system bitreload\n");
		return -1;
    }
    else if (WIFEXITED(ret) && WEXITSTATUS(ret)==127) {
        printf("could not invoke shell\n");
		return -1;
    }
	/*
      fp = popen(bitload_cmd, "r");
      if(NULL == fp){
        errUser("popen err cmd:%s", bitload_cmd);
      }
      if (ri->load_time > 10) {
        usleep(ri->load_time * 1000);
      }
      else{
        usleep(4000000);
      }
      while(fgets(buf, 1024, fp) != NULL)
      {   
          fprintf(stdout, "%s", buf); 
          PRINTF("%s", buf); 
      } 
      pclose(fp);*/
 /*   
    ret = gpsDevResume(ri->gps_handle);
   
    if (ret < 0) {
        return ret;
    }*/
	setFileValue("/sys/devices/soc0/43000000.ps7-lcdc/pl_bg/bg_flag", 1);
	setFileValue("/sys/devices/soc0/amba_pl/amba_pl:mcu-interrupt/mcu_interrupt/mcu_interrupt_flag", 1);
#ifdef BIT_OLD_LCD	
	setFileValue("/sys/bus/i2c/drivers/icn85xx/icn_suspend", 0);
#endif
#ifdef BIT_NEW_LCD
	setFileValue("/sys/bus/i2c/drivers/ilitek_ts/ilitek_suspend",0);
#endif
	setFileValue("/sys/devices/soc0/amba/amba:matrix-keyboard/matrix_gpio", 1);
	setFileValue("/sys/devices/soc0/amba_pl/80021000.serial/usart_pl/usart_flag", 0);
	setFileValue("/sys/devices/soc0/amba_pl/80028000.serial/usart_pl/usart_flag", 0);
    BackLightEpollResume(0);


    return DI_SUCCESS;
}

