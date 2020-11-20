#ifndef __SYSDEV_H__
#define __SYSDEV_H__


#ifdef __cplusplus

extern "C" {

#endif
#include <linux/ioctl.h>
#include "BitVisaType.h" 
#include "../functions/nmealib/nmea.h"




/*********ÊŸÀý***************
POWER_SUPPLY_NAME=f238-battery
POWER_SUPPLY_ONLINE=1
POWER_SUPPLY_STATUS=Discharging
POWER_SUPPLY_CHARGE_TYPE=Fast
POWER_SUPPLY_HEALTH=Good
POWER_SUPPLY_CAPACITY_LEVEL=Normal
POWER_SUPPLY_CAPACITY=13
POWER_SUPPLY_CHARGE_FULL=100
POWER_SUPPLY_TIME_TO_FULL_NOW=7800
POWER_SUPPLY_TEMP=3010
POWER_SUPPLY_VOLTAGE_NOW=10777
******************************/

typedef enum CHARGE_TYPE
{
	Unknow = 0x01,
    Charging,
	Discharging,
	Full,
	ERR_OVERTEMP,
	ERR_OVERCHAR,
}Charge_Type;

typedef struct 
{
  //DiChar  power_supply_name[30];//
  //DiInt8  power_supply_online; //
  Charge_Type  power_supply_status; //
  //DiChar  power_supply_charge_type[20];//
  //DiChar  power_supply_health[20];//
  //DiChar  power_supply_capacity_level[20];//
  DiInt32 power_supply_capacity; //
  //DiInt32 power_supply_charge_full;//
  //DiInt32 power_supply_time_to_full_now;//
  DiReal32 power_supply_temp;  //
  DiReal32 power_supply_voltage_now;//
  DiReal32 power_supply_current_now;//
  DiInt8  power_supply_battery_check; //
  DiInt8  power_supply_ac_detection; //
  DiInt8  fan_alarm_status; //
}PowerInfo;


typedef struct 
{
  DiInt8 charger_shdn_status;
  DiInt8 gps_rst_status;
  DiInt8 gps_en_status;
  DiInt8 lcd_pwr_status;
  DiInt8 led_b_status;
  DiInt8 led_g_status;
  DiInt8 led_r_status;
  DiInt8 hub_rst_status;
  DiInt8 hskb_blue_led_status;  
  DiInt8 key_backlight_status;
  DiInt8 fan_en_status;
  DiInt8 fan_alarm_status;
  DiInt8 battery_check_status;//电池在不在
  DiInt8 power_ac_check_status;//电源有没有接入
}McuStatusInfo;

///////////////////////////////////////////////////////////////////
DiInt32 ledBlueOpen(DiSession devHandle);
DiInt32 ledBlueClose(DiSession devHandle);//
DiInt32 ledGreenOpen(DiSession devHandle);//
DiInt32 ledGreenClose(DiSession devHandle);//
DiInt32 ledRedOpen(DiSession devHandle);//
DiInt32 ledRedClose(DiSession devHandle);//
DiInt32 wifiBtOpen(DiSession devHandle);
DiInt32 wifiBtClose(DiSession devHandle);
DiInt32 keyBacklightOpen(DiSession devHandle);//ŒüÅÌ±³¹âŽò¿ª   --->  pl white
DiInt32 keyBacklightClose(DiSession devHandle);//ŒüÅÌ±³¹â¹Ø±Õ
DiInt32 batteryDevOpen(DiPSession devHandle);//µç³ØÉè±žŽò¿ª
DiInt32 batteryDevClose(DiSession devHandle);//µç³ØÉè±ž¹Ø±Õ



DiInt32 mcuDevOpen(DiPSession devHandle);
DiInt32 mcuDevClose(DiSession devHandle);
DiInt32 mcuDevReadStatus(DiSession devHandle,McuStatusInfo *info);
DiInt32 batteryDevReadDate(DiSession devHandle,PowerInfo *info);//
DiInt32 openBackLightEpoll(DiSession devHandle); 
DiInt32 closeBackLightEpoll(DiSession devHandle);
DiInt32 fanOpen(DiSession devHandle);//·çÉÈŽò¿ª
DiInt32 fanClose(DiSession devHandle);//·çÉÈ¹Ø±Õ
DiInt32 lcdPwrOpen(DiSession devHandle);
DiInt32 lcdPwrClose(DiSession devHandle);
DiInt32 lcdSwitchOpen(DiSession devHandle);
DiInt32 lcdSwitchclose(DiSession devHandle);
DiInt32 usbHubOpen(DiSession devHandle);//USB Œ¯ÏßÆ÷µÄžŽÎ»ÒýœÅ žßµçÆœ
DiInt32 usbHubClose(DiSession devHandle);//USB Œ¯ÏßÆ÷µÄžŽÎ»ÒýœÅ µÍµçÆœ
DiInt32 gpsDevEnable(DiSession devHandle);//GPS µçÔŽœÓÍšÊ¹ÄÜ
DiInt32 gpsDevDisable(DiSession devHandle);//GPS µçÔŽÒýœÅ²»Ê¹ÄÜ

DiInt32 gpsDevOpen(DiPSession devHandle); //GPS Éè±žœÚµãŽò¿ª
DiInt32 gpsDevClose(DiSession devHandle);//GPS Éè±žœÚµã¹Ø±Õ
DiInt32 gpsDevReadDate(DiSession devHandle,nmeaINFO *info);//¶ÁÈ¡GPSÉè±žÊýŸÝ
DiInt32 gpsDevSetModel(DiSession devHandle);


DiInt32 gpsDevSuspend(DiSession devHandle);
DiInt32 gpsDevResume(DiSession devHandle);

DiInt32 microUsbReadBuff(DiSession devHandle,DiPChar buff,DiInt32 len);//阻塞的读
DiInt32 microUsbWriteBuff(DiSession devHandle,DiPChar buff,DiInt32 len);

DiInt32 BackLightEpollSuspend(DiSession devHandle); 
DiInt32 BackLightEpollResume(DiSession devHandle);

DiInt32 enableKeyVoice(void);
DiInt32 disableKeyVoice(void);















#ifdef __cplusplus

}

#endif


#endif
