/*****************************************************************************
Copyright: 2018-2028, yinuo Tech. Co.Ltd.
File name: 
Description: 
Author: gaven
Version: V1.01
Date: 2018 06 11
History: 
*****************************************************************************/


#include "SysDev.h"


#include <fcntl.h>     
#include <termios.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <stdint.h>  
#include <string.h>  
#include <sys/types.h>  
#include <linux/input.h>
#include <sys/mman.h>  
#include <unistd.h>   
#include <signal.h> 
#include <pthread.h>  

#define  __DEBUG
#include "error_functions.h"
#include "unity.h"
#include "lplay.h"
//#define MCU_INTERFACE   





#define PL_MISC_DBUG    

#define GPS_DEVICE_NAME           "/dev/ttyUL0"
#define MCU_DEVICE_NAME           "/dev/ttyUL1"
#define PL_DEVICE_NAME	          "/dev/pl_misc"

#define PL_DEVICE_LCD_SWITCH      "/sys/devices/soc0/43000000.ps7-lcdc/lcd_switch_pl/lcd_switch_pl"

#define PL_DEVICE_LCD_PWR         "/sys/devices/soc0/43000000.ps7-lcdc/lcd_pwr_en/lcd_pwr_en"
#define PL_DEVICE_GPS_EN          "/sys/class/tty/ttyUL0/device/gps_en/gps_en_flag"
#define PL_DEVICE_GPS_RST         "/sys/class/tty/ttyUL0/device/gps_rst/gps_rst_flag"

#define MICRO_USB_DEVICE_NAME	  "/dev/g_tmc0"

#define REC_LEN   800
#define DELAY_US  60000




 
static DiInt32 g_backLight_epoll_handle = 0;

 
static DiUInt8 g_plMiscCount = 0;
static DiInt32 g_plMiscFd = 0;
static pthread_mutex_t g_plMutex; 

static DiUInt8 g_gpsFlag = 0;
static DiInt32 g_gpsFd = 0;
static pthread_mutex_t g_gpsMutex; 
static pthread_t g_gps_thread;
static nmeaINFO g_gps_info;



static pthread_mutex_t g_gps_thread_mutex;
static pthread_cond_t g_gps_cond;
static DiInt32 g_gps_thread_flag = 0;




static DiUInt8 g_mcuFlag = 0;
static DiInt32 g_mcuFd = 0;
static pthread_mutex_t g_mcuMutex;


static DiUInt8 g_microUsbFlag = 0;
static DiInt32 g_microUsbFd = 0;
static pthread_mutex_t g_microUsbMutex;

static DiInt8 g_backLight_flag = 0;


// 2018 11 21
static struct input_event g_key_event = {0};
static pthread_t g_key_thread;
static pthread_t g_time_thread;

static DiInt32 g_count = 0;
static DiInt32 g_misc_fd = 0;
static DiInt8 g_key_flag = 0;
static DiInt8 g_key_voice = 0;
static DiSession keyHandle;

static fd_set g_rfds;

/*************************************************
Function: usart write
Description:mcu usart write date
Calls: read
Called By: extern
Table Accessed:
Table Updated: 
Input:  null
Output:
Return: success 0 fail -1
Others: null
*************************************************/
static DiInt32 mcuDevWriteDate(DiSession devHandle,DiPChar buff,DiInt32 length)
{
   DiInt32 ret = -1;

   if(g_mcuFlag == 0)
   {
        errUser("MCU_DBUG mcuDevWriteDate is not open\n");
        return SA_MCU_WRITE;
   }
   #ifdef PL_MISC_DBUG
   PRINTF("send:");
   int i;
   for(i=0;i<length;i++)
   {
      PRINTF(" 0x%x",buff[i]);
   }
   PRINTF("\n");
	    
   #endif
   ret = write(devHandle,buff,length);
   tcflush(devHandle,TCIFLUSH);
   if(ret<0)
   {
   	 errUser("MCU_DBUG mcuDevWriteDate date is error\n");
	 return SA_MCU_WRITE;
   }
   return DI_SUCCESS;
	
}

/*************************************************
Function: usart read
Description:mcu usart read date
Calls: read
Called By: extern
Table Accessed:
Table Updated: 
Input:  null
Output:
Return: success 0 fail -1
Others: null
*************************************************/
static DiInt32 mcuDevReadDate(DiSession devHandle,DiPChar buff,DiInt32 length)
{
   DiInt32 ret = -1;
  
   if(g_mcuFlag == 0)
   {
        errUser("MCU_DBUG mcuDevReadDate is not open\n");
        return SA_MCU_READ;
   }
   ret = read(devHandle,buff,length);
   if(ret<0)
   {
   	 errUser("MCU_DBUG mcuDevReadDate  is error\n");
	 return SA_MCU_READ;
   }

#ifdef PL_MISC_DBUG
  
#endif 	

   return DI_SUCCESS;
	
}

/*************************************************
Function: fanOpenDelay 
Description: Control MCU fan turn on delay
Calls: mcuDevWriteDate pthread_mutex_unlock
Called By:
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
static DiInt32 fanOpenDelay(DiSession devHandle)
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x0C,0x01};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
   	  errUser("%s: mcuDevWriteDate write is error\n", __func__);
      pthread_mutex_unlock(&g_mcuMutex);
   	  return SA_FAN_OPEN;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("%s: mcuDevReadDate read is error\n", __func__);
   	  return SA_FAN_OPEN;
   }

   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
	   #ifdef PL_MISC_DBUG
	   int i;
	   PRINTF("fanOpenDelay rec:\n");
	   for(i=0;i<sizeof(rec_buf);i++)
	   {
		  PRINTF(" 0x%x",rec_buf[i]);

	   }
	   PRINTF("\n");
		#endif
      if(rec_buf[4]==0x01)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      errUser("PL_MISC_DBUG fanOpenDelay is error\n");
      return SA_FAN_OPEN;
   }
   return DI_SUCCESS;
}
/*************************************************
Function: fanCloseDelay
Description: Control MCU fan turn off delay
Calls: mcuDevWriteDate pthread_mutex_unlock
Called By:
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
static DiInt32 fanCloseDelay(DiSession devHandle)
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x0C,0x00};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
   	  errUser("%s: mcuDevWriteDate is error\n", __func__);
          pthread_mutex_unlock(&g_mcuMutex);
   	  return SA_FAN_OPEN;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("%s: mcuDevReadDate is error\n", __func__);
   	  return SA_FAN_OPEN;
   }

   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
	   #ifdef PL_MISC_DBUG
	   int i;
	   PRINTF("fanCloseDelay rec:\n");
	   for(i=0;i<sizeof(rec_buf);i++)
	   {
		  PRINTF(" 0x%x",rec_buf[i]);

	   }
	   PRINTF("\n");
		#endif
      if(rec_buf[4]==0x00)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      errUser("PL_MISC_DBUG fanCloseDelay is error\n");
      return SA_FAN_OPEN;
   }
   return DI_SUCCESS;
}

/*************************************************
Function: The plmisc device drives is open
Description:Used to open the driver device node
Calls: pthread_mutex_init  pthread_mutex_lock   pthread_mutex_unlock  fcntl  open
Called By: extern
Table Accessed:
Table Updated: 
Input:  null
Output:
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 plMiscOpen(DiPSession devHandle)//
{
    DiInt32 ret = -1;
    if(g_plMiscCount == 0)
    {
        ret = pthread_mutex_init(&g_plMutex, NULL);
        if(ret < 0)
        {
           errUser("PL_MISC_DBUG pthread_mutex_init\n");
           return -1;
        }
    }
    if(pthread_mutex_lock(&g_plMutex) != 0)
    {
        errUser("PL_MISC_DBUG pthread_mutex error\n");
        return -1;
    }
    #ifdef PL_MISC_DBUG
    PRINTF("PL_MISC_DBUG pthread_mutex init is successful\n");
    #endif
    if(g_plMiscCount == 0)
    {
        if((g_plMiscFd = open(PL_DEVICE_NAME, O_RDWR | O_SYNC)) < 0)
                return -1;
        
    }
    *devHandle = g_plMiscFd;//ָ

    g_plMiscCount++;
    #ifdef PL_MISC_DBUG
	  PRINTF("PL_MISC_DBUG plMiscOpen is successful g_plMiscCount=%d\n",g_plMiscCount);
    #endif
    pthread_mutex_unlock(&g_plMutex);
    return 0;	
}
/*************************************************
Function: the plmisc device drives is close 
Description:Used to close the driver device node
Calls:  pthread_mutex_lock   pthread_mutex_unlock  pthread_mutex_destroy
Called By: extern 
Table Accessed: 
Table Updated: 
Input: null
Output: null
Return: success 0  fail -1
Others: null
*************************************************/
DiInt32 plMiscClose(DiSession devHandle)//
{

	if(g_plMiscCount)
	{

		if(pthread_mutex_lock(&g_plMutex) != 0)
		{
			errUser("PL_MISC_DBUG  pthread_mutex error\n");
			return -1;
		}

	    if(g_plMiscCount == 1)
	    {
			#ifdef PL_MISC_DBUG
			  PRINTF("PL_MISC_DBUG plMiscClose is successful devHandle=%d g_plMiscCount=%d\n",devHandle,g_plMiscCount);
		    #endif
	        close(devHandle);
			g_plMiscCount = 0; 
	        pthread_mutex_destroy(&g_plMutex);
	        return 0;
	    }
		else{
			#ifdef PL_MISC_DBUG
		      PRINTF("PL_MISC_DBUG devHandle=%d  g_plMiscCount=%d\n",devHandle,g_plMiscCount);
            #endif
			g_plMiscCount--;
		}
		pthread_mutex_unlock(&g_plMutex);
		return 0;
	}
	else
	{
	    errUser("PL_MISC_DBUG  plMiscClose is error g_plMiscCount = %d\n",g_plMiscCount);
	    return -1;
	}
	return  0;
}


/*************************************************
Function: the red light device node open
Description: open red light  
Calls: plMiscOpen  ioctl
Called By: extern
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 ledRedOpen(DiSession devHandle)//
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x07,0x01};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG LedRedOpen write is error\n");
          pthread_mutex_unlock(&g_mcuMutex);
   	  return SA_RED_LED_OPEN;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG LedRedOpen read is error\n");
   	  return SA_RED_LED_OPEN;
   }

   #ifdef PL_MISC_DBUG
   int i;
   PRINTF("rec:\n");
   for(i=0;i<sizeof(rec_buf);i++)
   {
      PRINTF(" %x",rec_buf[i]);

   }
   PRINTF("\n");
   #endif

   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
      if(rec_buf[4]==0x01)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      errUser("PL_MISC_DBUG LedRedOpen open is error\n");
      return SA_RED_LED_OPEN;
   }
   return DI_SUCCESS;
}
/*************************************************
Function: the red light device node close
Description: close red light  
Calls: plMiscOpen  ioctl
Called By: extern
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 ledRedClose(DiSession devHandle)//
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x07,0x00};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG LedRedClose write is error\n");
          pthread_mutex_unlock(&g_mcuMutex);
   	  return SA_RED_LED_CLOSE;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG LedRedClose read is error\n");
   	  return SA_RED_LED_CLOSE;
   }
   #ifdef PL_MISC_DBUG
   int i;
   PRINTF("rec:\n");
   for(i=0;i<sizeof(rec_buf);i++)
   {
      PRINTF(" %x",rec_buf[i]);

   }
   PRINTF("\n");
    #endif
   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
      if(rec_buf[4]==0x00)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      return SA_RED_LED_CLOSE;
   }

   return DI_SUCCESS;
}


/*************************************************
Function: the green light device node open 
Description: open green light 
Calls: plMiscOpen  ioctl
Called By: extern 
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0  fail -1
Others: null
*************************************************/
DiInt32 ledGreenOpen(DiSession devHandle)//
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x06,0x01};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG LedGreenOpen write is error\n");
          pthread_mutex_unlock(&g_mcuMutex);
   	  return SA_GREEN_LED_OPEN;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG LedGreenOpen read is error\n");
          
   	  return SA_GREEN_LED_OPEN;
   }
   #ifdef PL_MISC_DBUG
   int i;
   PRINTF("rec:\n");
   for(i=0;i<sizeof(rec_buf);i++)
   {
      PRINTF(" %x",rec_buf[i]);

   }
   PRINTF("\n");
    #endif
   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
      if(rec_buf[4]==0x01)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      errUser("PL_MISC_DBUG LedGreenOpen open is error\n");
      return SA_GREEN_LED_OPEN;
   }
   return DI_SUCCESS;
}
/*************************************************
Function: the green light device node close
Description: close green light 
Calls: plMiscOpen  ioctl
Called By: extern
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0 fail-1
Others: null
*************************************************/
DiInt32 ledGreenClose(DiSession devHandle)//
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x06,0x00};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG LedGreenClose write is error\n");
          pthread_mutex_unlock(&g_mcuMutex);
   	  return SA_GREEN_LED_CLOSE;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG LedGreenClose read is error\n");
   	  return SA_GREEN_LED_CLOSE;
   }
   #ifdef PL_MISC_DBUG
   int i;
   PRINTF("rec:\n");
   for(i=0;i<sizeof(rec_buf);i++)
   {
      PRINTF(" %x",rec_buf[i]);

   }
   PRINTF("\n");
    #endif
   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
      if(rec_buf[4]==0x00)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      return SA_GREEN_LED_CLOSE;
   }


   return DI_SUCCESS;
}
/*************************************************
Function: the Blue light device node open 
Description: open Blue light 
Calls: plMiscOpen  ioctl
Called By: extern 
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0  fail -1
Others: null
*************************************************/
DiInt32 ledBlueOpen(DiSession devHandle)//
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x05,0x01};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
		errUser("PL_MISC_DBUG LedBlueOpen write is error\n");
		pthread_mutex_unlock(&g_mcuMutex);
		return SA_BLUE_LED_OPEN;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG LedBlueOpen read is error\n");

   	  return SA_BLUE_LED_OPEN;
   }
   #ifdef PL_MISC_DBUG
   int i;
   PRINTF("rec:\n");
   for(i=0;i<sizeof(rec_buf);i++)
   {
      PRINTF(" %x",rec_buf[i]);

   }
   PRINTF("\n");
    #endif
   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
      if(rec_buf[4]==0x01)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      errUser("PL_MISC_DBUG LedBlueOpen read is error\n");
      return SA_BLUE_LED_OPEN;
   }
   return DI_SUCCESS;
}
/*************************************************
Function: the Blue light device node close
Description: close blue light 
Calls: plMiscOpen  ioctl
Called By: extern
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0 fail-1
Others: null
*************************************************/
DiInt32 ledBlueClose(DiSession devHandle)//
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x05,0x00};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
		errUser("PL_MISC_DBUG LedBlueClose write is error\n");
		pthread_mutex_unlock(&g_mcuMutex);
		return SA_BLUE_LED_CLOSE;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG LedBlueClose read is error\n");
   	  return SA_BLUE_LED_CLOSE;
   }
   #ifdef PL_MISC_DBUG
   int i;
   PRINTF("rec:\n");
   for(i=0;i<sizeof(rec_buf);i++)
   {
      PRINTF(" %x",rec_buf[i]);

   }
   PRINTF("\n");
    #endif
   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
      if(rec_buf[4]==0x00)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      return SA_BLUE_LED_CLOSE;
   }


   return DI_SUCCESS;
}

/*************************************************
Function: the wifi_bt_en open 
Description: enable wifi_bt_en gpio
Calls: plMiscOpen  ioctl
Called By: extern 
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0  fail -1
Others: null
*************************************************/
DiInt32 wifiBtOpen(DiSession devHandle)//
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x0E,0x01};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
		errUser("PL_MISC_DBUG wifiBtOpen write is error\n");
		pthread_mutex_unlock(&g_mcuMutex);
		return SA_BLUE_LED_OPEN;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG wifiBtOpen read is error\n");

   	  return SA_BLUE_LED_OPEN;
   }
   #ifdef PL_MISC_DBUG
   int i;
   PRINTF("rec:\n");
   for(i=0;i<sizeof(rec_buf);i++)
   {
      PRINTF(" %x",rec_buf[i]);

   }
   PRINTF("\n");
    #endif
   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
      if(rec_buf[4]==0x01)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      errUser("PL_MISC_DBUG wifiBtOpen read is error\n");
      return SA_BLUE_LED_OPEN;
   }
   return DI_SUCCESS;
}
/*************************************************
Function: the wifi_bt_en close 
Description: disable wifi_bt_en gpio 
Calls: plMiscOpen  ioctl
Called By: extern
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0 fail-1
Others: null
*************************************************/
DiInt32 wifiBtClose(DiSession devHandle)//
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x0E,0x00};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
		errUser("PL_MISC_DBUG wifiBtClose write is error\n");
		pthread_mutex_unlock(&g_mcuMutex);
		return SA_BLUE_LED_CLOSE;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG wifiBtClose read is error\n");
   	  return SA_BLUE_LED_CLOSE;
   }
   #ifdef PL_MISC_DBUG
   int i;
   PRINTF("rec:\n");
   for(i=0;i<sizeof(rec_buf);i++)
   {
      PRINTF(" %x",rec_buf[i]);

   }
   PRINTF("\n");
    #endif
   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
      if(rec_buf[4]==0x00)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      return SA_BLUE_LED_CLOSE;
   }


   return DI_SUCCESS;
}

/*************************************************
Function: the Back light device node open
Description: open back light
Calls: plMiscOpen  ioctl
Called By:  extern
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 keyBacklightOpen(DiSession devHandle)//
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x0A,0x01};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }

   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG keyBacklightOpen write is error\n");
          pthread_mutex_unlock(&g_mcuMutex);
   	  return SA_KEYLIGHT_OPEN;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG keyBacklightOpen read is error\n");
   	  return SA_KEYLIGHT_OPEN;
   }
   #ifdef PL_MISC_DBUG
   PRINTF("rec:");
   int i;
   for(i=0;i<sizeof(rec_buf);i++)
   {
      PRINTF(" %x",rec_buf[i]);

   }
   PRINTF("\n");
    #endif
   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
      if(rec_buf[4]==0x01)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      errUser("PL_MISC_DBUG keyBacklightOpen open is error\n");
      return SA_KEYLIGHT_OPEN;
   }
   
   return DI_SUCCESS;
}
/*************************************************
Function: the back light device node close
Description: close back light
Calls: plMiscOpen  ioctl
Called By: extern
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0 fail-1
Others: null
*************************************************/
DiInt32 keyBacklightClose(DiSession devHandle)//
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x0A,0x00};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
		errUser("PL_MISC_DBUG keyBacklightClose write is error\n");
		pthread_mutex_unlock(&g_mcuMutex);
		return SA_KEYLIGHT_CLOSE;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG keyBacklightClose read is error\n");
   	  return SA_KEYLIGHT_CLOSE;
   }
   
   #ifdef PL_MISC_DBUG
   int i;
   PRINTF("rec:\n");
   for(i=0;i<sizeof(rec_buf);i++)
   {
      PRINTF(" %x",rec_buf[i]);

   }
   PRINTF("\n");
    #endif
   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
      if(rec_buf[4]==0x00)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      return SA_KEYLIGHT_CLOSE;
   }

   return DI_SUCCESS;
}
/*************************************************
Function: lcd power device open 
Description: open lcd power device
Calls: mcuDevWriteDate pthread_mutex_unlock
Called By: extern
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 lcdPwrOpen(DiSession devHandle)
{
#ifdef MCU_INTERFACE  //
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x04,0x01};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
		errUser("PL_MISC_DBUG lcdPwrOpen write is error\n");
		pthread_mutex_unlock(&g_mcuMutex);
		return SA_LCD_PWR_OPEN;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG lcdPwrOpen read is error\n");
   	  return SA_LCD_PWR_OPEN;
   }
   #ifdef PL_MISC_DBUG
   int i;
   PRINTF("rec:\n");
   for(i=0;i<sizeof(rec_buf);i++)
   {
      PRINTF(" %x",rec_buf[i]);

   }
   PRINTF("\n");
    #endif
   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
      if(rec_buf[4]==0x01)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      errUser("PL_MISC_DBUG lcdPwrOpen is error\n");
      return SA_LCD_PWR_OPEN;
   }
   return DI_SUCCESS;
#else     //
	DiInt32 fd = 0 ;
	DiInt32 ret = -1;
	char * temp_buf = "1";

    fd = open(PL_DEVICE_LCD_PWR, O_WRONLY) ;
    if (fd < 0) {
        errUser("lcdPwrOpen  is error\n");
    	return SA_LCD_PWR_OPEN;
    }
	ret = write(fd, temp_buf, strlen(temp_buf));
	if (ret < 0) {
		errUser("lcdPwrOpen  is error\n");
		return SA_LCD_PWR_OPEN;
	}
	ret = close(fd);
    if(ret < 0)
    {
    	errUser("lcdPwrOpen  is error\n");
		return SA_LCD_PWR_OPEN;
    }
	return DI_SUCCESS;
#endif



}

DiInt32 lcdSwitchOpen(DiSession devHandle)
{
	DiInt32 fd = 0 ;
	DiInt32 ret = -1;
	char * temp_buf = "1";

    fd = open(PL_DEVICE_LCD_SWITCH, O_WRONLY) ;
    if (fd < 0) {
        errUser("lcdSwitchOpen open is error\n");
    	return SA_LCD_SWITCH_OPEN;
    }
	ret = write(fd, temp_buf, strlen(temp_buf));
	if (ret < 0) {
		errUser("lcdSwitchOpen write is error\n");
		return SA_LCD_SWITCH_OPEN;
	}
	ret = close(fd);
    if(ret < 0)
    {
		errUser("lcdSwitchOpen close is error\n");
		return SA_LCD_SWITCH_OPEN;
    }
	return DI_SUCCESS;
}

DiInt32 lcdSwitchClose(DiSession devHandle)
{
	DiInt32 fd = 0 ;
	DiInt32 ret = -1;
	char * temp_buf = "0";

    fd = open(PL_DEVICE_LCD_SWITCH, O_WRONLY);
    if (fd < 0) {
        errUser("lcdSwitchClose open  is error\n");
    	return SA_LCD_SWITCH_CLOSE;
    }
	ret = write(fd, temp_buf, strlen(temp_buf));
	if (ret < 0) {
		errUser("lcdSwitchClose write is error\n");
		return SA_LCD_SWITCH_CLOSE;
	}
	ret = close(fd);
    if(ret < 0)
    {
		errUser("lcdSwitchClose close is error\n");
		return SA_LCD_SWITCH_CLOSE;
    }
	return DI_SUCCESS;
}

/*************************************************
Function: lcd power device close 
Description: close lcd power device
Calls: mcuDevWriteDate pthread_mutex_unlock
Called By: extern
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 lcdPwrClose(DiSession devHandle)
{
#ifdef MCU_INTERFACE  //
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x04,0x00};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
		errUser("PL_MISC_DBUG lcdPwrClose write is error\n");
		pthread_mutex_unlock(&g_mcuMutex);
		return SA_LCD_PWR_CLOSE;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG lcdPwrClose read is error\n");
   	  return SA_LCD_PWR_CLOSE;
   }
   #ifdef PL_MISC_DBUG
   int i;
   PRINTF("rec:\n");
   for(i=0;i<sizeof(rec_buf);i++)
   {
      PRINTF(" %x",rec_buf[i]);

   }
   PRINTF("\n");
    #endif
   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
      if(rec_buf[4]==0x00)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      return SA_LCD_PWR_CLOSE;
   }
   return DI_SUCCESS;
#else     //
	DiInt32 fd = 0 ;
	DiInt32 ret = -1;
	char * temp_buf = "0";

    fd = open(PL_DEVICE_LCD_PWR, O_WRONLY) ;
    if (fd < 0) {
        errUser("lcdPwrClose open is error\n");
    	return SA_LCD_PWR_CLOSE;
    }
	ret = write(fd, temp_buf, strlen(temp_buf));
	if (ret <= 0) {
		errUser("lcdPwrClose write is error\n");
		return SA_LCD_PWR_CLOSE;
	}
	ret = close(fd);
	return DI_SUCCESS;
#endif
}

/*************************************************
Function: fan device node open 
Description: open fan device
Calls: PlMiscOpen  ioctl
Called By: extern
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 fanOpen(DiSession devHandle)
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x0B,0x01};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG fanOpen write is error\n");
          pthread_mutex_unlock(&g_mcuMutex);
   	  return SA_FAN_OPEN;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG fanOpen read is error\n");
   	  return SA_FAN_OPEN;
   }

   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
	   #ifdef PL_MISC_DBUG
	   int i;
	   PRINTF("fanOpen rec:\n");
	   for(i=0;i<sizeof(rec_buf);i++)
	   {
		  PRINTF(" 0x%x",rec_buf[i]);

	   }
	   PRINTF("\n");
		#endif
      if(rec_buf[4]==0x01)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      errUser("PL_MISC_DBUG fanOpen is error\n");
      return SA_FAN_OPEN;
   }
   return DI_SUCCESS;
}

/*************************************************
Function: fan device node close
Description: close fan device
Calls: plMiscOpen  ioctl
Called By: extern
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0 fail-1
Others: null
*************************************************/
DiInt32 fanClose(DiSession devHandle)
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x0B,0x00};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
		errUser("PL_MISC_DBUG fanClose write is error\n");
		pthread_mutex_unlock(&g_mcuMutex);
		return SA_FAN_CLOSE;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG fanClose read is error\n");
   	  return SA_FAN_CLOSE;
   }

   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
	  #ifdef PL_MISC_DBUG
	   int i;
	   PRINTF("fanClose rec:\n");
	   for(i=0;i<sizeof(rec_buf);i++)
	   {
		  PRINTF(" 0x%x",rec_buf[i]);

	   }
	   PRINTF("\n");
		#endif
      if(rec_buf[4]==0x00)
      {
         return DI_SUCCESS;
      }

   }
   else
   {
      return SA_FAN_CLOSE;
   }


   return DI_SUCCESS;	
}

/*************************************************
Function: usb hub rst  pin is open
Description: control usb hub rst pin 
Calls: plMiscOpen  ioctl
Called By:  extern
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0 fail-1
Others: null
*************************************************/
DiInt32 usbHubOpen(DiSession devHandle)
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x08,0x01};//
   DiChar rec_buf[10]={0};
   
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
		errUser("PL_MISC_DBUG usbHubOpen write is error\n");
		pthread_mutex_unlock(&g_mcuMutex);
		return SA_USBHUB_OPEN;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG usbHubOpen read is error\n");
   	  return SA_USBHUB_OPEN;
   }
   #ifdef PL_MISC_DBUG
   int i;
   PRINTF("rec:\n");
   for(i=0;i<sizeof(rec_buf);i++)
   {
      PRINTF(" %x",rec_buf[i]);

   }
   PRINTF("\n");
    #endif
   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
      if(rec_buf[4]==0x01)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      errUser("PL_MISC_DBUG usbHubOpen open is error\n");
      return SA_USBHUB_OPEN;
   }
   return DI_SUCCESS;
}
/*************************************************
Function: usb hub rst  pin is close
Description: control usb hub rst pin 
Calls: plMiscOpen  ioctl
Called By:  extern
Table Accessed:
Table Updated: 
Input: null
Output: null
Return: success 0 fail-1
Others: null
*************************************************/
DiInt32 usbHubClose(DiSession devHandle)
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x08,0x00};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
		errUser("PL_MISC_DBUG usbHubClose write is error\n");
		pthread_mutex_unlock(&g_mcuMutex);
		return SA_USBHUB_CLOSE;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
		errUser("PL_MISC_DBUG usbHubClose read is error\n");
		return SA_USBHUB_CLOSE;
   }
   #ifdef PL_MISC_DBUG
   int i;
   PRINTF("rec:\n");
   for(i=0;i<sizeof(rec_buf);i++)
   {
		PRINTF(" %x",rec_buf[i]);
   }
   PRINTF("\n");
    #endif
   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
      if(rec_buf[4]==0x00)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      return SA_USBHUB_CLOSE;
   }


   return DI_SUCCESS;	
}


/*************************************************
Function: serial port setting
Description: Set the serial port to use 
Calls: cfsetispeed  tcsetattr
Called By:gpsDevOpen
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail-1
Others: null
*************************************************/
static DiInt32 setSerial(DiInt32 fd,DiInt32 nSpeed,DiInt32 nBits,DiInt8 nEvent,DiInt32 nStop)  
{  
    struct termios newttys1,oldttys1;  
    if(tcgetattr(fd,&oldttys1)!=0)  
    {  
        perror("Setupserial 1");  
        return -1;  
    }  
    memset(&newttys1,0,sizeof(newttys1));
    newttys1.c_cflag|=(CLOCAL|CREAD); 
    newttys1.c_cflag &=~CSIZE;
    switch(nBits)  
    {  
       case 7:  
         newttys1.c_cflag |=CS7;  
         break;  
       case 8:  
         newttys1.c_cflag |=CS8;  
         break;  
    }  
    switch(nEvent)  
    {  
       case 'O':  
         newttys1.c_cflag |= PARENB;
         newttys1.c_iflag |= (INPCK | ISTRIP);   
         break;  
       case 'E':
         newttys1.c_cflag |= PARENB; 
         newttys1.c_iflag |= (INPCK | ISTRIP); 
         newttys1.c_cflag &= ~PARODD;
         break;  
       case 'N': 
         newttys1.c_cflag &= ~PARENB;  
         break;  
    }  
    switch(nSpeed)  
    {  
       case 2400:  
         cfsetispeed(&newttys1, B2400);  
         cfsetospeed(&newttys1, B2400);  
         break;  
       case 4800:  
         cfsetispeed(&newttys1, B4800);  
         cfsetospeed(&newttys1, B4800);  
         break;  
       case 9600:  
         cfsetispeed(&newttys1, B9600);  
         cfsetospeed(&newttys1, B9600);  
         break;  
       case 115200:  
         cfsetispeed(&newttys1, B115200);  
         cfsetospeed(&newttys1, B115200);  
         break;  
       default:  
         cfsetispeed(&newttys1, B9600);  
         cfsetospeed(&newttys1, B9600);   
         break;  
    }  
    if(nStop == 1)
    {  
        newttys1.c_cflag &= ~CSTOPB;
    }  
    else if(nStop == 2)  
    {  
        newttys1.c_cflag |= CSTOPB;
    }  
    newttys1.c_cc[VTIME] = 0;
    newttys1.c_cc[VMIN]  = 0; 
    tcflush(fd ,TCIFLUSH);
    if((tcsetattr(fd, TCSANOW,&newttys1))!=0)  
    {  
        perror("com set error");  
        exit(1);  
    }  
    return 0;  
} 

/*************************************************
Function: gps device is able
Description: gpsDevEnable 
Calls: ioctl
Called By:extern  
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 gpsDevEnable(DiSession devHandle)
{
#ifdef MCU_INTERFACE  //
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x03,0x01};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
		errUser("PL_MISC_DBUG gpsDevEnable write is error\n");
		pthread_mutex_unlock(&g_mcuMutex);
		return SA_GPS_ENABLE;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
		errUser("PL_MISC_DBUG gpsDevEnable read is error\n");
		return SA_GPS_ENABLE;
   }
   #ifdef PL_MISC_DBUG
   int i;
   PRINTF("rec:\n");
   for(i=0;i<sizeof(rec_buf);i++)
   {
      PRINTF(" %x",rec_buf[i]);

   }
   PRINTF("\n");
    #endif
   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
		if(rec_buf[4]==0x01)
		{
			return DI_SUCCESS;
		}
   }
   else
   {
		errUser("PL_MISC_DBUG gpsDevEnable open is error\n");
		return SA_GPS_ENABLE;
   }
   
#else
	DiInt32 fd = 0 ;
	DiInt32 ret = -1;
	char * temp_buf = "1";

    fd = open(PL_DEVICE_GPS_EN, O_WRONLY) ;
    if (fd < 0) {
        errUser("gpsDevEnable open is error\n");
    	return SA_GPS_ENABLE;
    }
	ret = write(fd, temp_buf, strlen(temp_buf));
	if (ret < 0) {
		errUser("gpsDevEnable write is error\n");
		return SA_GPS_ENABLE;
	}
	ret = close(fd);
    if(ret < 0)
    {
        errUser("gpsDevEnable close is error\n");
		return SA_GPS_ENABLE; 
    }
	#endif
   // gpsDevSetModel(g_gpsFd);
	return DI_SUCCESS;


}
/*************************************************
Function: gps device disable
Description: disable  gps device 
Calls: pthread_mutex_destroy  pthread_mutex_unlock mcuDevReadDate
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 gpsDevDisable(DiSession devHandle)
{
#ifdef MCU_INTERFACE  //
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x06,0x03,0x00};//
   DiChar rec_buf[10]={0};
   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   } 
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
		errUser("PL_MISC_DBUG gpsDevDisable write is error\n");
		pthread_mutex_unlock(&g_mcuMutex);
		return SA_GPS_DISABLE;
   }
   usleep(DELAY_US);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	  errUser("PL_MISC_DBUG gpsDevDisable read is error\n");
   	  return SA_GPS_DISABLE;
   }
   #ifdef PL_MISC_DBUG
   int i;
   PRINTF("rec:\n");
   for(i=0;i<sizeof(rec_buf);i++)
   {
      PRINTF(" %x",rec_buf[i]);

   }
   PRINTF("\n");
    #endif
   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
      if(rec_buf[4]==0x00)
      {
         return DI_SUCCESS;
      }
   }
   else
   {
      return SA_GPS_DISABLE;
   }
   return DI_SUCCESS;	
#else
	DiInt32 fd = 0 ;
	DiInt32 ret = -1;
	char * temp_buf = "0";

    fd = open(PL_DEVICE_GPS_EN, O_WRONLY) ;
    if (fd < 0) {
        errUser("gpsDevDisable open is error\n");
    	return SA_GPS_DISABLE;
    }
	ret = write(fd, temp_buf, strlen(temp_buf));
	if (ret < 0) {
		errUser("gpsDevDisable write is error\n");
		return SA_GPS_DISABLE;
	}
	ret = close(fd);
    if(ret < 0)
    {
		errUser("gpsDevDisable close is error\n");
		return SA_GPS_DISABLE;
    }
	return DI_SUCCESS;

#endif
}
/*************************************************
Function: gps device read thread handle
Description: gps read handle 
Calls: ioctl
Called By:extern  
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
void threadGpsHandle()
{
    
    DiChar recbuf[200]={0};
    DiInt32 len=0;
    DiInt32 ret = 0;
    fd_set readfd; 
    DiInt32 rec_len= 0;
    DiInt32 i=0;
    DiChar buff[80]={0};
//DiChar tmpBuf[]=" $GPRMC,062818.00,A,3556.84939,N,12009.15316,E,0.115,,220618,,,D*7A\r\n";
    nmeaINFO gps_info; 
    nmeaPARSER parser;              // nmea协议解析载体

    memset(&g_gps_info,0,sizeof(g_gps_info));
    nmea_zero_INFO(&gps_info);          // 填入默认的解析结果
    nmea_parser_init(&parser);      // 为解析载体分配内存空间
	while(1)
    {
		if(g_gps_thread_flag == 1)
        {
			pthread_mutex_lock(&g_gps_thread_mutex);
         	errUser("gps thread is cond_wait\n");
	 		pthread_cond_wait(&g_gps_cond,&g_gps_thread_mutex);	
         	g_gps_thread_flag = 0;
         	pthread_mutex_unlock(&g_gps_thread_mutex);
      	}

      	FD_ZERO(&readfd);
      	FD_SET(g_gpsFd,&readfd);
      	ret = select(g_gpsFd+1,&readfd,NULL,NULL,NULL); //将select置于阻塞状态，当文件描述符有变化为止
      	if(ret < 0)
      	{
    		errUser("ret error = %d\n",ret);
        }
        if(ret == 0)
		{
			errUser("select() timeout\n");
		    continue;
        }
        if(FD_ISSET(g_gpsFd,&readfd))
        {
			lseek(g_gpsFd, 0, SEEK_SET);  //	        
	  		len = read(g_gpsFd, buff, sizeof(buff));
	  		tcflush(g_gpsFd,TCIOFLUSH);

  			for(i=0; i<len; i++)
			{
				recbuf[rec_len+i] = buff[i];
			}		    
			rec_len += len;
			}
			if(recbuf[0] != '$')
			{
				rec_len = 0; 
               	memset(recbuf,0,sizeof(recbuf));			        
			    continue; 
			}
			for(i =0; i<rec_len;i++) 
			{
            	if(recbuf[i]=='\n')
                {
					recbuf[i]='\r';
					recbuf[i+1]='\n';
                    //PRINTF("\n%s\n\n",recbuf);
                    if(recbuf[2]!='P')//
                    {					
						gpsDevSetModel(g_gpsFd);
                    }
			    	if( (nmea_parse(&parser, recbuf, strlen(recbuf), &gps_info)) > 0 )
				 	{
                		g_gps_info = gps_info;
                		/*#ifdef PL_MISC_DBUG
						PRINTF("gps---time: %04d-%02d-%02d %02d:%02d:%02d\n",g_gps_info.utc.year+1900,g_gps_info.utc.mon,g_gps_info.utc.day+1,g_gps_info.utc.hour+8,g_gps_info.utc.min,g_gps_info.utc.sec);  

						PRINTF("gps quality indicator:\t%d\n",g_gps_info.sig); 
						PRINTF("longitude   %.5f\r\n",g_gps_info.lon);
						PRINTF("latitude    %.5f\r\n",g_gps_info.lat);
						PRINTF("speed       %.2f\r\n",g_gps_info.speed);
						PRINTF("elv         %.2f\r\n",g_gps_info.elv);
						PRINTF("sig         %d\r\n",g_gps_info.sig);
						PRINTF("fix         %d\r\n",g_gps_info.fix);
						PRINTF("inuse       %d\r\n",g_gps_info.satinfo.inuse);//Number of satellites in use (not those in view)
						PRINTF("inview       %d\r\n",g_gps_info.satinfo.inview);//Total number of satellites in view

						#endif */         
	     			}
             		rec_len = 0;
             		break;
          		}
     	    }

       }
}

/*************************************************
Function: gps device open
Description: open  gps device 
Calls: pthread_mutex_destroy  pthread_mutex_unlock
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 gpsDevOpen(DiPSession devHandle)  
{  
    DiInt32 ret = -1;
    if(g_gpsFlag == 0)
    {
        ret = pthread_mutex_init(&g_gpsMutex, NULL);
        if(ret < 0)
        {
           errUser("GPS_DBUG pthread_mutex_init\n");
           return SA_DEV_MUTEX_INIT;
        }
        ret = pthread_mutex_init(&g_gps_thread_mutex,NULL);
        if(ret < 0)
        {
           errUser("GPS_DBUG g_gps_thread_mutex init\n");
           return SA_DEV_MUTEX_INIT;
        }
        ret = pthread_cond_init(&g_gps_cond,NULL);
        if(ret < 0)
        {
           errUser("GPS_DBUG g_gps_cond init\n");
           return SA_DEV_MUTEX_INIT;
        }

    }
    if(pthread_mutex_lock(&g_gpsMutex) != 0)
    {
        errUser("GPS_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
    }
    #ifdef PL_MISC_DBUG
    PRINTF("GPS_DBUG pthread_mutex init is successful\n");
    #endif
    
    if(g_gpsFlag == 0)
    {
       // if((g_gpsFd = open(GPS_DEVICE_NAME, O_RDWR|O_NOCTTY|O_NDELAY)) < 0)
        if((g_gpsFd = open(GPS_DEVICE_NAME, O_RDWR|O_NOCTTY)) < 0)
        {
            errUser("PL_MISC_DBUG GPS_DEVICE_NAME is not open\n");
            return SA_GPS_OPEN;
        }             
        gpsDevEnable(g_gpsFd);
        sleep(1);
        gpsDevSetModel(g_gpsFd);
        pthread_create(&g_gps_thread,NULL,(void*)threadGpsHandle,NULL);
  
    }

    g_gpsFlag++;
    *devHandle = g_gpsFd;//
    pthread_mutex_unlock(&g_gpsMutex);
    fcntl(g_gpsFd,F_SETFL,0);
    
    return DI_SUCCESS;     
} 
/*************************************************
Function: gps device is close
Description: close  gps device 
Calls: pthread_mutex_destroy  pthread_mutex_unlock
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 gpsDevClose(DiSession devHandle) 
{
	DiInt32 ret = -1;
	if(g_gpsFlag)
    {
		if(pthread_mutex_lock(&g_gpsMutex) != 0)
	    {
	       errUser("GPS_DBUG pthread_mutex_lock error\n");
	       return SA_DEV_MUTEX_LOCK;
	    }
	    if(g_gpsFlag == 1)
	    {
	        g_gpsFlag = 0;
	        pthread_mutex_destroy(&g_gpsMutex);
			pthread_mutex_destroy(&g_gps_thread_mutex);
			pthread_cond_destroy(&g_gps_cond);
			ret = pthread_cancel(g_gps_thread);
    	    if (ret != 0)
			{   
        	  	errUser("GPS_DBUG cancel thread err\n");
				return SA_THREAD_CANCEL;
	        }
            pthread_join(g_gps_thread, NULL);
            gpsDevDisable(devHandle);
            close(devHandle);
	        return DI_SUCCESS;
	    }
	    else
        {
	  		g_gpsFlag --;             
	    }
        pthread_mutex_unlock(&g_plMutex);
	    return DI_SUCCESS;
    }
	else
		return SA_GPS_CLOSE;
    return DI_SUCCESS;	
}
/*************************************************
Function: gps device is Suspend
Description: Suspend  gps device 
Calls: pthread_mutex_destroy  pthread_mutex_unlock
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 gpsDevSuspend(DiSession devHandle)
{
    if(g_gpsFlag != 0)
	{
		pthread_mutex_lock(&g_gps_thread_mutex);
		g_gps_thread_flag = 1;//zuse
		pthread_mutex_unlock(&g_gps_thread_mutex);
	}

    return DI_SUCCESS;
}
/*************************************************
Function: gps device is Resume
Description: Resume  gps device 
Calls: pthread_mutex_destroy  pthread_mutex_unlock
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 gpsDevResume(DiSession devHandle)
{
    if(g_gpsFlag != 0)
    {
		pthread_mutex_lock(&g_gps_thread_mutex);
		pthread_cond_signal(&g_gps_cond);
		g_gps_thread_flag = 0;
		pthread_mutex_unlock(&g_gps_thread_mutex);
		setSerial(devHandle,9600,8,'N',1);
		
	  
		fcntl(devHandle,F_SETFL,0);
    }
    return DI_SUCCESS;
}
/*************************************************
Function: read gps device data
Description: read gps 
Calls: nmea_zero_INFO nmea_parser_init nmea_parse  nmea_parser_destroy
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/

DiInt32 gpsDevReadDate(DiSession devHandle,nmeaINFO *info)
{
    *info = g_gps_info;
 #ifdef PL_MISC_DBUG
	PRINTF("gps time: %04d-%02d-%02d %02d:%02d:%02d\n",g_gps_info.utc.year+1900,g_gps_info.utc.mon,g_gps_info.utc.day+1,g_gps_info.utc.hour+8,g_gps_info.utc.min,g_gps_info.utc.sec);  
	PRINTF("longitude   %.5f\r\n",g_gps_info.lon);
	PRINTF("latitude    %.5f\r\n",g_gps_info.lat);
	PRINTF("speed       %.2f\r\n",g_gps_info.speed);

	PRINTF("inuse       %d\r\n",g_gps_info.satinfo.inuse);//Number of satellites in use (not those in view)
    PRINTF("inview       %d\r\n",g_gps_info.satinfo.inview);//Total number of satellites in view

 #endif 
    return DI_SUCCESS;
	
} 

/*************************************************
Function:gps device set out pulse
Description: set gps device
Calls: write
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 gpsDevSetModel(DiSession devHandle)
{
	DiInt32 ret = -1;
	DiChar rec_buf[1024]={0};
	DiInt32 len = 0;

	const DiChar buff_old[] =                {0xB5,0x62,0x06,0x3E,0x34,0x00,0x00,0x00,0x10,0x06,0x00,0x08,0x10,0x00,0x01,0x00,0x01,0x01,0x01,0x01,0x03,0x00,0x00,0x00,0x01,0x01,0x03,0x08,0x10,0x00,0x00,0x00,0x01,0x01,0x04,0x00,0x08,0x00,0x00,0x00,0x01,0x01,0x05,0x00,0x03,0x00,0x00,0x00,0x01,0x01,0x06,0x08,0x0E,0x00,0x00,0x00,0x01,0x01,0x03,0xA5};

	const DiChar buff_new[] = {0xB5,0x62,0x06,0x31,0x20,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x9A,0x99,0x99,0x19,0x00,0x00,0x00,0x00,0x6F,0x00,0x00,0x00,0x2F,0x18};

   if(devHandle == 0)
   {
       errUser("GPS_DBUG gpsDevSetModel gps is not open\n");
       return -1;
   }
//fcntl(g_gpsFd,F_SETFL,0);
  
   tcflush(g_gpsFd,TCIOFLUSH);
   ret = write(devHandle,buff_old,sizeof(buff_old));
   if(ret < 0)
   {
      errUser("gpsDevSetModel uart write is error\n");
   }

   ret = write(devHandle,buff_new,sizeof(buff_new));
   if(ret < 0)
   {
      errUser("gpsDevSetModel uart write is error\n");
   }
   sleep(1);
}



/*************************************************
Function: read battery device data
Description: read battery info 
Calls: 
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/

DiInt32 batteryDevReadDate(DiSession devHandle,PowerInfo *info)
{
   DiInt32 ret = -1;
   DiChar rec_buff[30] = {0};              
   DiChar send_buf[5]={0xFE,0xFE,0x03,0x0D,0x0C};//

   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));
   if(ret<0)
   {
		errUser("BATTERY_DBUG batteryDevReadDate write date is error\n");
        pthread_mutex_unlock(&g_mcuMutex);
        return SA_BATTERY_READ;
   }

   usleep(DELAY_US*3);
   ret = mcuDevReadDate(devHandle,rec_buff,sizeof(rec_buff));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
   	    errUser("BATTERY_DBUG batteryDevReadDate read date is error\n");
        return SA_BATTERY_READ;
   }

   if(rec_buff[0]==0xFE&&rec_buff[1]==0xFE)
   {
	#if 1//#ifdef PL_MISC_DBUG
        PRINTF("batteryDevReadDate rec:");
		int i;
		for(i=0;i<sizeof(rec_buff);i++)
		{
			PRINTF(" 0x%x",rec_buff[i]);

		}
		PRINTF("\n");
	#endif 
       info->power_supply_capacity = rec_buff[3]<<8|rec_buff[2];//当前电量百分比
       info->power_supply_temp =((DiReal32)(rec_buff[5]<<8|rec_buff[4]))/100;//电池温度
       info->power_supply_voltage_now = ((DiReal32)(rec_buff[7]<<8|rec_buff[6]))/1000;  //电池电压 V
       info->power_supply_current_now = ((DiReal32)(rec_buff[9]<<8|rec_buff[8]))/1000;//当前电流  A
       if(rec_buff[12]==0x01)
       {
	       if(rec_buff[10] & 0x40)//放电状态
	       {
                info->power_supply_status = Discharging;
	       }
	       else if((rec_buff[10] & 0x40)==0x00)//充电状态
	       {
                info->power_supply_status = Charging;
	       }
       }
       else 
       {
             info->power_supply_status = Unknow;
       }
       info->power_supply_battery_check = rec_buff[12];       //电池存在/不存在
       info->power_supply_ac_detection = rec_buff[13];//电源接通/未接通
       if(rec_buff[14]==0x00)//放电电流
       {
          
       }
       else if(rec_buff[14]==0x01 && info->power_supply_battery_check==1)//充电电流
       {
          if(info->power_supply_capacity ==100)
		  {
             info->power_supply_status = Full;
		  }
       }
       info->fan_alarm_status = rec_buff[15];//20190318 test

	   if (rec_buff[11] & 0x10) {
	   		info->power_supply_status = ERR_OVERTEMP;
	   }
	   else if (rec_buff[11] & 0x80) {
	   		info->power_supply_status = ERR_OVERCHAR;
	   }

    /*   if(rec_buff[15]==0x00)
       {
          info->fan_alarm_status = 0;
       }
       else 
       {
          info->fan_alarm_status = 1;
       }*/
#ifdef PL_MISC_DBUG
       PRINTF("info->power_supply_status = %d\n",info->power_supply_status);
       PRINTF("info->power_supply_capacity = %d\n",info->power_supply_capacity);
       PRINTF("info->power_supply_temp = %.3f\n",info->power_supply_temp);
       PRINTF("info->power_supply_voltage_now = %.3f\n",info->power_supply_voltage_now);
       PRINTF("info->power_supply_current_now = %.3f\n",info->power_supply_current_now);
       PRINTF("info->power_supply_battery_check = %d\n",info->power_supply_battery_check);
       PRINTF("info->power_supply_ac_detection = %d\n",info->power_supply_ac_detection);   
       PRINTF("info->fan_alarm_status = %d\n",info->fan_alarm_status);  
#endif 

    }
    else 
    { 
       return SA_BATTERY_READ;
    }
    return DI_SUCCESS;
}


/*************************************************
Function: mcu device is open
Description: open  mcu device 
Calls: pthread_mutex_destroy  pthread_mutex_unlock
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 mcuDevOpen(DiPSession devHandle)  
{  
    DiInt32 ret=-1;
    if(g_mcuFlag == 0)
    {
        ret = pthread_mutex_init(&g_mcuMutex, NULL);
        if(ret < 0)
        {
           errUser("MCU_DBUG pthread_mutex_init\n");
           return SA_DEV_MUTEX_INIT;
        }
    }
    if(pthread_mutex_lock(&g_mcuMutex) != 0)
    {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
    }
    #ifdef PL_MISC_DBUG
    PRINTF("MCU_DBUG pthread_mutex init is successful\n");
    #endif
    
    if(g_mcuFlag == 0)
    {
        if((g_mcuFd = open(MCU_DEVICE_NAME, O_RDWR|O_NOCTTY|O_NDELAY)) < 0)
                return SA_MCU_OPEN;
     
        setSerial(g_mcuFd,9600,8,'N',1); 
    }
	g_mcuFlag++;
	*devHandle = g_mcuFd;//
    pthread_mutex_unlock(&g_mcuMutex);
    return DI_SUCCESS;     
} 
/*************************************************
Function: mcu device is close
Description: close  mcu device 
Calls: pthread_mutex_destroy  pthread_mutex_unlock
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 mcuDevClose(DiSession devHandle) 
{
  if(g_mcuFlag)
  {
	  if(g_mcuFlag == 1)
	  {

	      if(pthread_mutex_lock(&g_mcuMutex) != 0)
	      {
	          errUser("MCU_DBUG pthread_mutex_lock error\n");
	          return SA_DEV_MUTEX_LOCK;
	      }
	      close(devHandle);
	      g_mcuFlag = 0;
	      pthread_mutex_destroy(&g_mcuMutex);
	      return DI_SUCCESS;
	  }
	  else{
	  	  g_mcuFlag --;
	  }
	  pthread_mutex_unlock(&g_mcuMutex);
	  return DI_SUCCESS;
  }
  else
      return SA_MCU_CLOSE;
  return DI_SUCCESS;	
}
/*************************************************
Function:  read mcu device status
Description: mcu device status
Calls: pthread_mutex_destroy  pthread_mutex_unlock
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 mcuDevReadStatus(DiSession devHandle,McuStatusInfo *info)
{
   DiInt32 ret = -1;
   DiChar send_buf[5]={0xFE,0xFE,0x03,0x01,0x0C};//
   DiChar rec_buf[20]={0};


   if(pthread_mutex_lock(&g_mcuMutex) != 0)
   {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
   }
   ret = mcuDevWriteDate(devHandle,send_buf,sizeof(send_buf));

   if(ret<0)
   {
		pthread_mutex_unlock(&g_mcuMutex);
		errUser("PL_MISC_DBUG mcuDevReadStatus write is error\n");
		return -1;
   }
   usleep(DELAY_US*2);
   ret  = mcuDevReadDate(devHandle,rec_buf,sizeof(rec_buf));
   pthread_mutex_unlock(&g_mcuMutex);
   if(ret<0)
   {
		errUser("PL_MISC_DBUG mcuDevReadStatus read is error\n");
		return SA_MCU_READ;
   }

   if(rec_buf[0]==0xFE&&rec_buf[1]==0xFE)
   {
		#ifdef PL_MISC_DBUG
		int i;
		PRINTF("mcuDevReadStatus rec:\n");
		for(i=0;i<sizeof(rec_buf);i++)
		{
			PRINTF(" 0x%x",rec_buf[i]);
		}
		PRINTF("\n");
		#endif
		info->charger_shdn_status= rec_buf[2];
		info->gps_rst_status= rec_buf[3];
		info->gps_en_status= rec_buf[4];
		info->lcd_pwr_status= rec_buf[5];
		info->led_b_status= rec_buf[6];
		info->led_g_status= rec_buf[7];
		info->led_r_status= rec_buf[8];
		info->hub_rst_status= rec_buf[9];
		info->hskb_blue_led_status= rec_buf[10];
		info->key_backlight_status= rec_buf[11];
		info->fan_en_status= rec_buf[12];
		info->fan_alarm_status= rec_buf[13];
		info->battery_check_status= rec_buf[14];//电池在不在
		info->power_ac_check_status= rec_buf[15];//电源有没有接入
	}
	else
	{
		return SA_MCU_READ;
	}


   return DI_SUCCESS;	
}

DiInt32 enableKeyVoice(void)
{
	g_key_voice = 1;
	return 0;
}
DiInt32 disableKeyVoice(void)
{
	g_key_voice = 0;
	return 0;
}
DiInt32 BackLightEpollSuspend(DiSession devHandle)
{
    //errUser("BackLightEpollSuspend\n");
    g_backLight_flag = 0;
    keyBacklightClose(g_mcuFd);
    return 0;
}
DiInt32 BackLightEpollResume(DiSession devHandle)
{
    //errUser("BackLightEpollResume\n");
    g_backLight_flag = 1;
    keyBacklightOpen(g_mcuFd);
    g_key_flag = 1;
    return 0;
}

/*************************************************
Function:  thread time handle 
Description: keyBackLight delay
Calls: pthread_mutex_destroy  pthread_mutex_unlock
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
void threadTimeHandle(void *p)
{
    keyHandle = *(DiPSession)p;
    while(1)
    {	
        usleep(100000);
        if(g_key_flag == 1 )
        { 	    
           g_count++;
	       if(g_count>20)
           {
               #ifdef PL_MISC_DBUG
               PRINTF("This value is g_misc_fd = %d\n",g_misc_fd);
               #endif
               if(g_backLight_flag == 1)
               {
               	  keyBacklightClose(keyHandle);
               }
               g_count = 0;
               g_key_flag = 0;
           }

        }

        else 
        {
             g_count = 0;
        }

    }
}

/*************************************************
Function:  thread key handle 
Description: keyBackLight delay
Calls: pthread_mutex_destroy  pthread_mutex_unlock
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
void threadKeyHandle(void *p)
{
    //PRINTF("This value is %d\n",*(DiPSession)p);
    keyHandle = *(DiPSession)p;
    BackLightEpollResume(0);
    while(1)
    { 
		if(read(g_misc_fd, &g_key_event, sizeof(g_key_event)) == sizeof(g_key_event))
		{
			if(g_key_event.type==EV_KEY)
		    {
				if((g_key_event.code != 61) && (g_key_event.code != 62))
		        {
					if(g_key_event.value == 0)
					{
                        #ifdef PL_MISC_DBUG
               			PRINTF("g_key_event.code = %d\n",g_key_event.code);
		                PRINTF("key release\n");
                        #endif
				        g_key_flag = 1;
					}
				    else if(g_key_event.value == 1)
				    {
                        if(g_backLight_flag == 1)
						{
							if (g_key_voice) {
								playWav("voice/button.wav");
							}
							keyBacklightOpen(keyHandle);
							g_key_flag = 0; 	
                        }	                    
				    }
		        }

		    }	                         
		 }
     }
}
/*************************************************
Function:  open  backLight epoll
Description: keyBackLight epoll open
Calls: pthread_mutex_destroy  pthread_mutex_unlock
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 openBackLightEpoll(DiSession devHandle)  
{    
    if(g_mcuFlag<0)
    {
       errUser("open  mcu error");
	   return -1;
    }
    g_misc_fd = open("/dev/input/event0", O_RDONLY);  
    if (g_misc_fd <=0)  
    {
        errUser("openBackLightEpoll can't open!\n"); 
        return g_misc_fd ;
    }  
    g_backLight_epoll_handle  = devHandle;
    pthread_create(&g_key_thread,NULL,(void*)threadKeyHandle,&g_backLight_epoll_handle);
    pthread_create(&g_time_thread,NULL,(void*)threadTimeHandle,&g_backLight_epoll_handle);
    return 0;  
} 


/*************************************************
Function:  close  backLight epoll
Description: keyBackLight epoll close
Calls: pthread_mutex_destroy  pthread_mutex_unlock
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 closeBackLightEpoll(DiSession devHandle)
{
	DiInt32 ret = -1;
	ret = pthread_cancel(g_key_thread);
	if (ret != 0){   
		errUser("cancel thread err\n");
		return SA_THREAD_CANCEL;
	}
	pthread_join(g_key_thread, NULL);
	ret = pthread_cancel(g_time_thread);
	if (ret != 0){   
		errUser("cancel thread err\n");
		return SA_THREAD_CANCEL;
	}
	pthread_join(g_time_thread, NULL);
	close(g_misc_fd);
	return 0;
}
/*************************************************
Function:  micro usb open
Description: open micro usb
Calls: pthread_mutex_destroy  pthread_mutex_unlock
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 microUsbDevOpen(DiPSession devHandle)
{
    DiInt32 ret = -1;
    if(g_microUsbFlag == 0)
    {
        ret = pthread_mutex_init(&g_microUsbMutex, NULL);
        if(ret < 0)
        {
           errUser("MCU_DBUG pthread_mutex_init\n");
           return SA_DEV_MUTEX_INIT;
        }
    }
    if(pthread_mutex_lock(&g_microUsbMutex) != 0)
    {
        errUser("MCU_DBUG pthread_mutex error\n");
        return SA_DEV_MUTEX_LOCK;
    }
    #ifdef PL_MISC_DBUG
    PRINTF("MCU_DBUG pthread_mutex init is successful\n");
    #endif
    
    if(g_microUsbFlag == 0)
    {
        if((g_microUsbFd = open(MICRO_USB_DEVICE_NAME, O_RDWR,0)) < 0)
                return SA_MICRO_USB_OPEN;
    }
    g_microUsbFlag++;
    *devHandle = g_microUsbFd;//
    pthread_mutex_unlock(&g_microUsbMutex);

    return DI_SUCCESS; 

}
/*************************************************
Function:  micro usb close
Description: close micro usb
Calls: pthread_mutex_destroy  pthread_mutex_unlock
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 microUsbDevClose(DiSession devHandle) 
{
  if(g_microUsbFlag)
  {
	  if(g_microUsbFlag == 1)
	  {

	      if(pthread_mutex_lock(&g_microUsbMutex) != 0)
	      {
	          errUser("MCU_DBUG pthread_mutex_lock error\n");
	          return SA_DEV_MUTEX_LOCK;
	      }
          //FD_CLR(devHandle, &g_rfds);
	      close(devHandle);
	      g_microUsbFlag = 0;
	      pthread_mutex_destroy(&g_microUsbMutex);
	      return DI_SUCCESS;
	  }
	  else
	  {
	  	  g_microUsbFlag --;
	  }
      pthread_mutex_unlock(&g_microUsbMutex);
	  return DI_SUCCESS;
  }
  else
      return SA_MICRO_USB_CLOSE;
  return DI_SUCCESS;	
}
/*************************************************
Function:  micro usb read
Description: read micro usb
Calls: pthread_mutex_destroy  pthread_mutex_unlock
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 microUsbReadBuff(DiSession devHandle,DiPChar buff,DiInt32 len)
{

    DiInt32 ret = -1;
    DiInt32 length = -1;

    FD_ZERO(&g_rfds);
    FD_SET(devHandle,&g_rfds);

    ret = select(devHandle + 1,&g_rfds,NULL,NULL,NULL);
    if(ret > 0)
    {
		if(FD_ISSET(devHandle,&g_rfds)) 
        {
	    	length = read(devHandle, buff, len);
	    	if(length < 0)
            {
				errUser("microUsbReadBuff read failed\n");
	    	} 
        }
     }
     else if(ret == 0)
     {
		 return  SA_MICRO_USB_READ_TIME_OUT;
	 }
	 else if(ret < 0)
	 {
		 return SA_MICRO_USB_READ;
	 }
     return length;
}
/*************************************************
Function:  micro usb write
Description: write micro usb
Calls: pthread_mutex_destroy  pthread_mutex_unlock
Called By:extern   
Table Accessed:null
Table Updated:null
Input: null
Output: null
Return: success 0 fail -1
Others: null
*************************************************/
DiInt32 microUsbWriteBuff(DiSession devHandle,DiPChar buff,DiInt32 len)
{
   DiInt32 length = 0; 
   length = write(devHandle,buff,len);
   if (length < 0) 
   {
       errUser("microUsbWriteBuff write failed write_len= %d\n", length);
   } 
   return length;
}


//2018 08 21

static dev_fun_opt* pl_misc_fun;

void init_pl_misc(void)
{
	pl_misc_fun = (dev_fun_opt* )malloc(sizeof(struct dev_fun_opt));
	memset(pl_misc_fun,0,sizeof(struct dev_fun_opt));
	pl_misc_fun->bus_name   = "VIRTUAL";//
	pl_misc_fun->dev_num    = 0;
	pl_misc_fun->dev_type   = "DEVICE";
	pl_misc_fun->open = plMiscOpen;
	pl_misc_fun->close= plMiscClose;	
	pl_misc_fun->is_epoll = 1;
	register_dev_fun(pl_misc_fun);
}

void exit_pl_misc(void)
{
	free(pl_misc_fun);
	unregister_dev_fun(pl_misc_fun);
}

static dev_fun_opt* gps_fun;

void init_gps(void)
{
	gps_fun = (dev_fun_opt* )malloc(sizeof(struct dev_fun_opt));
	memset(gps_fun,0,sizeof(struct dev_fun_opt));
	gps_fun->bus_name   = "ASRL_PL";//gps 
	gps_fun->dev_num    = 0;
	gps_fun->dev_type   = "DEVICE";
	gps_fun->open = gpsDevOpen;
	gps_fun->close = gpsDevClose;	
	register_dev_fun(gps_fun);
}

void exit_gps(void)
{
	free(gps_fun);
	unregister_dev_fun(gps_fun);
}

static dev_fun_opt* mcu_uart_fun;

void init_mcu_uart(void)
{
	mcu_uart_fun = (dev_fun_opt* )malloc(sizeof(struct dev_fun_opt));
	memset(mcu_uart_fun,0,sizeof(struct dev_fun_opt));
	mcu_uart_fun->bus_name   = "ASRL_PL";//
	mcu_uart_fun->dev_num    = 1;
	mcu_uart_fun->dev_type   = "DEVICE";
	mcu_uart_fun->open = mcuDevOpen;
	mcu_uart_fun->close = mcuDevClose;	
	register_dev_fun(mcu_uart_fun);
}

void exit_mcu_uart(void)
{
	free(mcu_uart_fun);
	unregister_dev_fun(mcu_uart_fun);
}


static dev_fun_opt* micro_usb_fun;

void init_micro_usb(void)
{
	micro_usb_fun = (dev_fun_opt* )malloc(sizeof(struct dev_fun_opt));
	memset(micro_usb_fun,0,sizeof(struct dev_fun_opt));
	micro_usb_fun->bus_name   = "USB";//
	micro_usb_fun->dev_num    = 1;
	micro_usb_fun->dev_type   = "DEVICE";
	micro_usb_fun->open = microUsbDevOpen;
	micro_usb_fun->close = microUsbDevClose;	
    //micro_usb_fun->is_epoll = 1;
	register_dev_fun(micro_usb_fun);
}

void exit_micro_usb(void)
{
	free(micro_usb_fun);
	unregister_dev_fun(micro_usb_fun);
}












