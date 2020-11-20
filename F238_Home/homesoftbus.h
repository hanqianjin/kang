/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:homesoftbus.h
** Latest Version: V0.0.1
** Latest modified Date:  2018-12-17
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by: bithomeYang
** Created date: 2018-12-17
** Descriptions:used in all files
**
*********************************************************************************************************/
#ifndef HOMESOFTBUS_H
#define HOMESOFTBUS_H

#include "QObject"


class homedistrc
{
public:
  static const char* pltdismod[];
};

const qint32 SYSINTER = 1000;
const qint32 HIDEWAIT = 100000;//!<when cut mode to hide home ui after time
const qint32 BATTINTER = 5000;

const qint32 INDEXBASE = 0;//!<just for index use
const quint32 BATTARYINI = 0;

/**
 * @brief The RUNMODE enum,may extend other mode
 */
enum HRUNMODE {SA_MODE = 0,RTSA_MODE,INTERF_MODE,PM_MODE,LTE_FDD_MODE,LTE_TDD_MODE,FIVE_G_NR,NONEMODE};

/**
 * @brief The SWITCHFLAG enum,can be used in all on/off state
 */
enum SWITCHFLAG {POFF = 0,PON,PUZERO = -1};

/**
* @brief for multi types could extend
*/
enum PLTTYPE {PTY0 = 0,PTY1,PTY2,PTY3};

const QByteArray NOBATPIC[] = {":/bithome/image/icn_home_batter-charging.png"};
const QByteArray NOBATPICNIGHT[] = {":/bithome/image/icn_charge_night_ing.png"};

const QByteArray CHARGEPIC[] = {":/bithome/image/icn_home_charge_0.png",
                                ":/bithome/image/icn_home_charge_1.png",
                                ":/bithome/image/icn_home_charge_2.png",
                                ":/bithome/image/icn_home_charge_3.png",
                                ":/bithome/image/icn_home_charge_4.png",
                                ":/bithome/image/icn_home_charge_5.png"};
const QByteArray CHARGEPICNIGHT[] = {":/bithome/image/icn_charge_night_0.png",
                                ":/bithome/image/icn_charge_night_1.png",
                                ":/bithome/image/icn_charge_night_2.png",
                                ":/bithome/image/icn_charge_night_3.png",
                                ":/bithome/image/icn_charge_night_4.png",
                                ":/bithome/image/icn_charge_night_5.png"};

const quint32 CHARGEREMAIN[] = {10,21,50,75,85,100};

const QByteArray DISCHARGEPIC[] = {":/bithome/image/icn_home_battery_0.png",
                                   ":/bithome/image/icn_home_battery_low.png",
                                   ":/bithome/image/icn_home_battery_1.png",
                                   ":/bithome/image/icn_home_battery_2.png",
                                   ":/bithome/image/icn_home_battery_3.png",
                                   ":/bithome/image/icn_home_battery_4.png",
                                   ":/bithome/image/icn_home_battery_5.png"};
const QByteArray DISCHARGEPICNIGHT[] = {":/bithome/image/icn_battery_night_0.png",
                                   ":/bithome/image/icn_battery_night_low.png",
                                   ":/bithome/image/icn_battery_night_1.png",
                                   ":/bithome/image/icn_battery_night_2.png",
                                   ":/bithome/image/icn_battery_night_3.png",
                                   ":/bithome/image/icn_battery_night_4.png",
                                   ":/bithome/image/icn_battery_night_5.png"};

const quint32 DISCHARGEREMIAN[] = {0,9,21,28,50,75,85};

const QByteArray FULLPIC[] = {":/bithome/image/icn_home_battery_full.png"};
const QByteArray FULLPICNIGHT[] = {":/bithome/image/icn_charge_night_full.png"};

#define PLT_IXT_System_Info          (0x00000008)
#define PLT_IXS_BoardTemp 		  0x00000020
#define PLT_IXS_BatteryInfoAll        0x00000040
#define PLT_IXS_BatteryRemaind 	  0x00000080
#define PLT_IXS_BatterChargeStatus 	  0x00000100
#define PLT_IXS_ACStatus		  0x00000200
#define PLT_IXS_LanPortStatus 	  0x00000400
#define PLT_IXS_USBMemoryStatus 	  0x00000800
#define PLT_IXS_DeviceMsg  		  0x00001000
#define PLT_IXS_BoardTempAlarm 	  0x00002000
#define PLT_IXS_BatteryTempAlarm 	  0x00004000
#define PLT_IXS_GPSInfoAll		  0x00800000
#define PLT_IXS_GPSLongitude	  0x01000000
#define PLT_IXS_GPSDate		  0x02000000
#define PLT_IXS_GPSTime		  0x04000000
#define PLT_IXS_BatteryOnline	  0x08000000

/**
* @brief indicate battary charge state
*/
enum BATTARYCHARGE {UN_BATT = 0,BATT_CHARGE,BATT_DISCHARGE,BATT_FULL};

typedef struct Noticmsg
{
  short npflag;
  short ntype;
  short keep;
  short source;
  short logicmode;
  short keepex;
  short index;
}NOTICMSG,*PNOTICMSG;
quint32 GetNoticeCode(PNOTICMSG notichandle);
#endif // HOMESOFTBUS_H
