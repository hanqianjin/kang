/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:softbus.h
** Latest Version: V0.0.1
** Latest modified Date:  2018-12-13
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2018-12-12
** Descriptions:for safe type,object relations attributes use const instead of macro;
**
*********************************************************************************************************/
#ifndef SOFTBUS_H
#define SOFTBUS_H

#include "QObject"

const qint32 SYSINTER = 1000;
const qint32 MODESWITCH = 200;
const qint32 TEMPERSWITCH = 5000;
const qint32 CTRLUPOVERTIME = 10000;
const qint32 BURNTIME = 3700000;

const qint32 PLUSMODX = 979;
const qint32 PLUSMODY = 117;
const qint32 SETDETAY = 25;

const qint32 UIMODMAXNUM = 4;
const qint32 INDEXBASE = 0;//!<just for index use
const quint32 BATTARYINI = 0;
/**
 * @brief The RUNMODE enum,may extend other mode,NONEMODE for num
 */
enum RUNMODE {SA_MODE = 0,RTSA_MODE,INTERF_MODE,PM_MODE,LTE_TDD_MODE,NONEMODE};
const QString modbtntext[] = {"SA-","RTSA-","IA-","PM-","LTE-"};

/**
 * @brief for commu with multi ana modes
 * @note
 * @author steve
 * @since {2019-01-15:c20190124}
*/
enum SAMEASURE{SPEC_MEAS = 0,CHPOWER_MEAS,OCCBW_MEAS,SPEEMIMASK_MEAS,ACP_MEAS,MACP_MEAS,SPUEMIMASK_MEAS,FIELD_MEAS,ANADEMO_MEAS};
const QString sameasbtntext[] = {"Spectrum","CP","Occupied BW","Spectrum EM","ACP","Multi ACP","Spurious EM","Field Strength","AM/FM Audio Demod"};

enum RTSAMEASURE{PERSIS_SPEC_MEAS = 0,PERSIS_SPECGRAM_MEAS};
const QString rtsameasbtntext[] = {"Persist Spectrum","Persist Spectrogram"};


enum INTERMEASURE{ISPEC_MEAS = 0,ISPECGRAM_MEAS,IRSSI_MEAS,ICM_MEAS,IPERSIS_SPEC_MEAS,IPERSIS_SPECGRAM_MEAS};
const QString intermeasbtntext[] = {"Spectrum","Spectrogram","RSSI","CM","Persist Spectrum","Persist Spectrogram"};


enum PMMEASURE{INTER_PM_MEAS = 0,EXTERN_PM_MEAS};
const QString pmmeasbtntext[] = {"Internal","External"};


enum LTETDDMEASURE{TDD_CP_MEAS = 0,TDD_OBW_MEAS,TDD_SEM_MEAS,TDD_ACP_MEAS,TDD_MACP_MEAS,TDD_SPUEM_MEAS,TDD_PTF_MEAS,TDD_PTS_MEAS,TDD_DC_MEAS};
const QString letddmeasbtntext[] = {"CP","Occupied BW","Spectrum EM","ACP","Multi ACP","Spurious EM","Power vs. Time(Frame)","Power vs. Time(Slot)","Data Channel"};

/**
 * @brief The EXITSWITCH enum,tell app to exit,the same state in all modes
 */
enum EXITSWITCH {BEXIT = 0,BRUN};

/**
 * @brief The SWITCHFLAG enum,can be used in all on/off state
 */
enum SWITCHFLAG {POFF = 0,PON};

/**
 * @brief The INIWSIZE enum
 */
enum INIWSIZE {PSTARTX = 1,PSTARTY = 52,PWIDTH = 1278,PHEIGHT = 713,MAXDETA = 52};

/**
* @brief 1:2:3:4
*/
const QByteArray TOPMENU[] = {":/bit/image/tab4.png",":/bit/image/tab3.png",":/bit/image/tab2.png",":/bit/image/tab1.png"};

const QByteArray NOBATPIC[] = {":/bit/image/icn_battery_5.png"};

const QByteArray CHARGEPIC[] = {":/bit/image/icn_charge_0.png",":/bit/image/icn_charge_1.png",":/bit/image/icn_charge_2.png",
                                ":/bit/image/icn_charge_3.png",":/bit/image/icn_charge_4.png",":/bit/image/icn_charge_5.png"};
const quint32 CHARGEREMAIN[] = {10,21,50,75,85,100};

const QByteArray DISCHARGEPIC[] = {":/bit/image/icn_battery_0.png",":/bit/image/icn_battery_low.png",":/bit/image/icn_battery_1.png",
                                   ":/bit/image/icn_battery_2.png",":/bit/image/icn_battery_3.png",":/bit/image/icn_battery_4.png",
                                   ":/bit/image/icn_battery_5.png"};
const quint32 DISCHARGEREMIAN[] = {0,9,21,28,50,75,85};

const QByteArray FULLPIC[] = {":/bit/image/icn_battery_5.png"};

/**
* @brief for delete and add mode to change plus btn position
*/
enum PLUSPOSI {SPX = 260,STEPP = 280,DETAP = 47,SPY = 10};

/**
* @brief for measure items widget position
*/
enum MESAWIDPOSI {MX = 769,MY = 119,MW = 428,MH = 520};

/**
* @brief for seting widget position
*/
enum SETWIDPOSI {SMX = 282,SMY = 45};

enum SETITEM {COM_SET = 0,DSDT_SET,NETWORK_SET,LICE_SET,HSW_SET,SYS_SET};

/**
* @brief indicate battary charge state
*/
enum BATTARYCHARGE {UN_BATT = 0,BATT_CHARGE,BATT_DISCHARGE,BATT_FULL};

/**
* @brief to trigger sys action
*/
#define PLT_IXT_ConfigSystem         (0x00000004)
#define PLT_IXS_IPAddress             0x00000001
#define PLT_IXS_NetMask               0x00000002
#define PLT_IXS_GateWayAddress        0x00000004
#define PLT_IXS_Local_Remote	  0x00000008
#define PLT_IXS_KeypadLight		  0x00000010
#define PLT_IXS_LCDBrightness         0x00000020
#define PLT_IXS_SleepMode		  0x00000040
#define PLT_IXS_Volume		  0x00000080
#define PLT_IXS_KeyBeep		  0x00000100
#define PLT_IXS_LimitBeep		  0x00000200
#define PLT_IXS_FWupdateRequest       0x00000400
#define PLT_IXS_TouchScreen           0x00000800
#define PLT_IXS_BurnAction            0x00001000

#define PLT_IXT_System_Info          (0x00000008)
#define PLT_IXS_InvenAppMajor         0x00000001
#define PLT_IXS_InvenAppMiinor        0x00000002
#define PLT_IXS_InvenDSPRevision      0x00000004
#define PLT_IXS_InvenDSPDate 	  0x00000008
#define PLT_IXS_InvenSerialNo 	  0x00000010
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
#define PLT_IXS_PSModel  		  0x00008000
#define PLT_IXS_PSType 		  0x00010000
#define PLT_IXS_PSMethod 		  0x00020000
#define PLT_IXS_PSSerialNo 		  0x00040000
#define PLT_IXS_PSInvenMajor 	  0x00080000
#define PLT_IXS_PSInvenMinor 	  0x00100000
#define PLT_IXS_PSTemp 		  0x00200000
#define PLT_IXS_PSStatus 		  0x00400000
#define PLT_IXS_GPSInfoAll		  0x00800000
#define PLT_IXS_GPSLongitude	  0x01000000
#define PLT_IXS_GPSDate		  0x02000000
#define PLT_IXS_GPSTime		  0x04000000
#define PLT_IXS_BatteryOnline	  0x08000000

#endif // SOFTBUS_H
