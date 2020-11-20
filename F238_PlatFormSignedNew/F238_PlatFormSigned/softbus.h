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
#include "msgNoticeCode.h"

//Johnson 20200618
#define _DEBUG_ 0
//Johnson 20200317
#define USB_SPEED_TEST

#define _Linux_PLT_SA
#define _Linux_PLT_RTSA

#define _Linux_PLT_IA
#define _Linux_PLT_PM
#define _Linux_PLT_FDD
#define _Linux_PLT_TDD
#define _Linux_PLT_FGNR
#define _Linux_PLT_ALL

#define PLT_EXCE_SOURCE 18
#define PLT_STATE_COND
#define _Linux_F238_Log
#define _linux_238_netctrl
//#define plt_bit_238
#define plt_bit_239
//#define plt_bit_238_smart

#define PLT_CAL_HIDE 0

const qint32 PLTQUERY = 100;
const qint32 SYSINTER = 1000;
const qint32 MODESWITCH = 200;
const qint32 TEMPERSWITCH = 5000;
const qint32 CTRLUPOVERTIME = 10000;
const qint32 BURNTIME = 100000;
const qint32 CLOTIME = 100000;
const qint32 CTRLINTER = 100000;

const qint32 PLUSMODX = 979;
const qint32 PLUSMODY = 117;
const qint32 SETDETAY = 25;

const qint32 UIMODMAXNUM = 4;
const qint32 INDEXBASE = 0;//!<just for index use
const quint32 BATTARYINI = 0;
const qreal INIREF = 0.0;
const qreal SINGVOL = 10;//100 / 10
const qint32 SYSSLEEP = 600000;
const qint32 MAINBACKT = 100;
const qint32 BURNTIMEOUT = 8000;
const qint32 PLTMAXCIRLEN = 101;

const QString pltdismod[] =
{
  "indoor",
  "outdoor",
  "night"
};

enum PLTSYSDIS
{
  PLT_INDOOR = 0,
  PLT_OUTDOOR,
  PLT_NIGHT,
  PLT_DNONE
};
/**
 * @brief The RUNMODE enum,may extend other mode,NONEMODE for num
 */
enum RUNMODE
{
  SA_MODE = 0,
  RTSA_MODE,
  INTERF_MODE,
  PM_MODE,
  LTE_FDD_MODE,
  LTE_TDD_MODE,
  FIVE_G_NR,
  NONEMODE
};


const QString modbtntext[]=
{
  "Spectrum Analyzer",
  "Real-Time SA",
  "Interference Analyzer",
  "Power Meter",
  "LTE-A FDD",
  "LTE-A TDD",
  "5G-NR Analyzer"
};

/**
 * @brief for commu with multi ana modes
 * @note
 * @author steve
 * @since {2019-01-15:c20190124}
*/
enum SAMEASURE
{
  SPEC_MEAS = 0,
  CHPOWER_MEAS,
  OCCBW_MEAS,
  SPEEMIMASK_MEAS,
  ACP_MEAS,
  MACP_MEAS,
  SPUEMIMASK_MEAS,
  FIELD_MEAS,
  ANADEMO_MEAS,
  SANONE
};

const QString sameasbtntext[] = {
  "Swept SA",
  "Channel Power",
  "Occupied BW",
  "Spectrum Emission Mask",
  "Multi-ACP",
  "ACP",
  "Spurious Emission",
  "Field Strength",
  "AM/FM Audio Demod"
};

enum RTSAMEASURE
{
  PERSIS_SPEC_MEAS = 0,
  PERSIS_SPECGRAM_MEAS,
  PERSIS_DENSITY_MEAS,
  PERSIS_DENSITY_SPECGRAM_MEAS,
  RTSANONE
};

const QString rtsameasbtntext[] = {
  "Persist Spectrum",
  "Persist Spectrogram",
  "Persist Density",
  "Persist Density Spectrogram"
};

enum INTERMEASURE
{
  ISPEC_MEAS = 0,
  ISPECGRAM_MEAS,
  IRSSI_MEAS,
  ICM_MEAS,
  IPERSIS_SPEC_MEAS,
  IPERSIS_SPECGRAM_MEAS,
  INTERNONE
};

const QString intermeasbtntext[] = {
  "Spectrum",
  "Spectrogram",
  "RSSI",
  "Coverage Mapping",
  "Persist Spectrum",
  "Persist Spectrogram"
};

enum PMMEASURE
{
  INTER_PM_MEAS = 0,
  EXTERN_PM_MEAS,
  PMNONE
};

const QString pmmeasbtntext[] = {
  "Internal",
  "External"
};


enum LTEFDDMEASURE
{
  FDD_SPECTRUM_MEAS = 0,
  FDD_CP_MEAS,
  FDD_OBW_MEAS,
  //FDD_SEM_MEAS,
  //FDD_ACLR_MEAS,
  FDD_PTF_MEAS,  
  FDD_CONSTELL_MEAS,
  FDD_DATAC_MEAS,
  FDD_CONTROLC_MEAS,
  FDD_FRAMEANA_MEAS,  
  FDD_DAM_MEAS,
  FDD_CHASCA_MEAS,
  FDD_IDS_MEAS,
  FDD_RMAP_MEAS,
  FDD_CONCHA_MEAS,
  FDD_DATAGRAM_MEAS,
  //FDD_MULP_MEAS,
  FDD_CARAGG_MEAS,
  //FDD_CONFOR_TEST,
  //FDD_MAIN_TEST,
  //FDD_SIG_PERFOR,
  //FDD_DAS_TEST,
  //FDD_CCDF,
  LTEFDDNONE
};

const QString ltefddmeasbtntext[] = {
  "Spectrum",
  "Channel Power",
  "Occupied BW",
  //"Spectrum EM",
  //"ACLR",
  "Power vs Time(Frame)",  
  "Constellation",
  "Data Channel",
  "Control Channel",
  "Frame Analysis",  
  "Data Allocation Map",
  "Channel Scanner",
  "ID Scanner",
  "Route Map",
  "Control Channel",
  "Datagram",
 // "Multipath Profile",
  "Carrier Aggregation",
 // "Conformance Test",
 // "Maintenance Test",
 // "Signal Performance",
 // "DAS Test",
 // "Power Statistics CCDF"
};
enum LTETDDMEASURE
{
  TDD_SPECTRUM_MEAS = 0,
  TDD_CP_MEAS,
  TDD_OBW_MEAS,
  //TDD_SEM_MEAS,
  //TDD_ACLR_MEAS,
  TDD_PTF_MEAS,
  TDD_PTS_MEAS,
  TDD_CONSTELL_MEAS,
  TDD_DATAC_MEAS,
  TDD_CONTROLC_MEAS,
  TDD_FRAMEANA_MEAS,
  TDD_TAE_MEAS,
  TDD_DAM_MEAS,
  TDD_CHASCA_MEAS,
  TDD_IDS_MEAS,
  TDD_RMAP_MEAS,
  TDD_CONCHA_MEAS,
  TDD_DATAGRAM_MEAS,
 // TDD_MULP_MEAS,
  TDD_CARAGG_MEAS,
//  TDD_CONFOR_TEST,
//  TDD_MAIN_TEST,
//  TDD_SIG_PERFOR,
//  TDD_DAS_TEST,
//  TDD_CCDF,
  LTETDDNONE
};

const QString ltetddmeasbtntext[] = {
  "Spectrum",
  "Channel Power",
  "Occupied BW",
  //"Spectrum EM",
  //"ACLR",
  "Power vs Time(Frame)",
  "Power vs Time(Slot)",
  "Constellation",
  "Data Channel",
  "Control Channel",
  "Frame Analysis",
  "Time Alignment Error",
  "Data Allocation Map",
  "Channel Scanner",
  "ID Scanner",
  "Route Map",
  "Control Channel",
  "Datagram",
  //"Multipath Profile",
  "Carrier Aggregation",
//  "Conformance Test",
//  "Maintenance Test",
//  "Signal Performance",
//  "DAS Test",
//  "Power Statistics CCDF"
};

enum FGNRMEASURE
{
  FGNR_SPECTRUM,
  FGNR_CHANNEL_POWER,
  FGNR_OCCUPIED_BW,
  FGNR_MULTI_BEAM,
  FGNR_SINGLE_BEAM,
  FGNR_PCI_SACNER,
  FGNR_EIRP_NORMAL,
  FGNR_EIRP_QUICK,
  ROUTE_MAP,
  FGNRNONE
};

const QString fgnrmeasbtntext[] = {
  "Spectrum",
  "Channel Power",
  "Occupied BW",
  "Multi-Beam",
  "Single Beam",
  "PCI Scanner",
  "EIRP Normal View",
  "EIRP Quick View",
  "Route Map"
};


/**
 * @brief The EXITSWITCH enum,tell app to exit,the same state in all modes
 */
enum EXITSWITCH
{
  BEXIT = 0,
  BRUN
};

/**
 * @brief The SWITCHFLAG enum,can be used in all on/off state
 */
enum SWITCHFLAG
{
  POFF = 0,
  PON,
  PUZERO = -1
};

/**
 * @brief The INIWSIZE enum
 */
enum INIWSIZE
{
  PSTARTX = 1,
  PSTARTY = 52,
  PWIDTH = 1278,
  PHEIGHT = 713,
  MAXDETA = 52
};

/**
* @brief for multi types could extend
*/
enum PLTTYPE
{
  PTY0 = 0,
  PTY1,
  PTY2,
  PTY3,
  PTY4,
  PTY5,
  PTY6,
  PTY7,
  PTY8,
  PTY9,
  PTY10,
  PTY11,
  PTY12,
  PTY13,
  PTY14,
  PTY15
};

const QString GpsQos[] = {QObject::tr("Invalid"),QObject::tr("Fix"),QObject::tr("Differential"),QObject::tr("Sensitive")};
const QString GpsOperMod[] = {QObject::tr("Fix"),QObject::tr("2D"),QObject::tr("3D")};

/**
* @brief swith pic when plus or delete or change mode
*/
const QByteArray TOPMENU_4[] = {":/bit/image/4_tab1.png",
                                ":/bit/image/4_tab2.png",
                                ":/bit/image/4_tab3.png",
                                ":/bit/image/4_tab4.png"};

const QByteArray TOPMENU_night_4[] = {":/bit/image/4_tab1_night.png",
                                      ":/bit/image/4_tab2_night.png",
                                      ":/bit/image/4_tab3_night.png",
                                      ":/bit/image/4_tab4_night.png"};

const QByteArray TOPMENU_3[] = {":/bit/image/3_tab1.png",
                                ":/bit/image/3_tab2.png",
                                ":/bit/image/3_tab3.png"};

const QByteArray TOPMENU_night_3[] = {":/bit/image/3_tab1_night.png",
                                      ":/bit/image/3_tab2_night.png",
                                      ":/bit/image/3_tab3_night.png"};

const QByteArray TOPMENU_2[] = {":/bit/image/2_tab1.png",
                                ":/bit/image/2_tab2.png"};

const QByteArray TOPMENU_night_2[] = {":/bit/image/2_tab1_night.png",
                                      ":/bit/image/2_tab2_night.png"};

const QByteArray TOPMENU_1[] = {":/bit/image/1_tab1.png"};

const QByteArray TOPMENU_night_1[] = {":/bit/image/1_tab1_night.png"};

const QByteArray EXCENOTIC[] = {":/bit/image/notic.png",
                                ":/bit/image/exce.png"};

const QByteArray EXCENOTICNIGHT[] = {":/bit/image/noticnight.png",
                                     ":/bit/image/excenight.png"};

const QByteArray TOOLNOTIC[] = {":/bit/image/msg.png",
                                ":/bit/image/msgcome.png"};

const QByteArray TOOLNOTICNIGHT[] = {":/bit/image/msgnight.png",
                                     ":/bit/image/msgcomenight.png"};

/**
* @brief for battery
*/
const QByteArray NOBATPIC[] = {":/bit/image/icn_charge_ing.png"};
const QByteArray NOBATPICNIGHT[] = {":/bit/image/icn_charge_night_ing.png"};

const QByteArray CHARGEPIC[] = {":/bit/image/icn_charge_0.png",
                                ":/bit/image/icn_charge_1.png",
                                ":/bit/image/icn_charge_2.png",
                                ":/bit/image/icn_charge_3.png",
                                ":/bit/image/icn_charge_4.png",
                                ":/bit/image/icn_charge_5.png"};
const QByteArray CHARGEPICNIGHT[] = {":/bit/image/icn_charge_night_0.png",
                                     ":/bit/image/icn_charge_night_1.png",
                                     ":/bit/image/icn_charge_night_2.png",
                                     ":/bit/image/icn_charge_night_3.png",
                                     ":/bit/image/icn_charge_night_4.png",
                                     ":/bit/image/icn_charge_night_5.png"};

const quint32 CHARGEREMAIN[] = {10,21,50,75,85,100};

const QByteArray DISCHARGEPIC[] = {":/bit/image/icn_battery_0.png",
                                   ":/bit/image/icn_battery_low.png",
                                   ":/bit/image/icn_battery_1.png",
                                   ":/bit/image/icn_battery_2.png",
                                   ":/bit/image/icn_battery_3.png",
                                   ":/bit/image/icn_battery_4.png",
                                   ":/bit/image/icn_battery_5.png"};
const QByteArray DISCHARGEPICNIGHT[] = {":/bit/image/icn_battery_night_0.png",
                                        ":/bit/image/icn_battery_night_low.png",
                                        ":/bit/image/icn_battery_night_1.png",
                                        ":/bit/image/icn_battery_night_2.png",
                                        ":/bit/image/icn_battery_night_3.png",
                                        ":/bit/image/icn_battery_night_4.png",
                                        ":/bit/image/icn_battery_night_5.png"};

const quint32 DISCHARGEREMIAN[] = {0,9,21,28,50,75,85};

const QByteArray FULLPIC[] = {":/bit/image/icn_charge_full.png"};
const QByteArray FULLPICNIGHT[] = {":/bit/image/icn_charge_night_full.png"};
/**
* @brief for volume pic
*/
const QByteArray VOLPIC[] = {":/bit/image/sound_0.png",
                             ":/bit/image/sound_1.png",
                             ":/bit/image/sound_2.png",
                             ":/bit/image/sound_3.png",
                             ":/bit/image/sound_4.png",
                             ":/bit/image/sound_5.png",
                             ":/bit/image/sound_6.png",
                             ":/bit/image/sound_7.png",
                             ":/bit/image/sound_8.png",
                             ":/bit/image/sound_full.png"};

const QByteArray NIGHTVOLPIC[] = {":/bit/image/VOICE1.png",
                                  ":/bit/image/VOICE2.png",
                                  ":/bit/image/VOICE3.png",
                                  ":/bit/image/VOICE4.png",
                                  ":/bit/image/VOICE5.png",
                                  ":/bit/image/VOICE6.png",
                                  ":/bit/image/VOICE7.png",
                                  ":/bit/image/VOICE8.png",
                                  ":/bit/image/VOICE9.png",
                                  ":/bit/image/VOICE9.png"};

const QByteArray PLUSPICNORMAL[] = {":/bit/image/1_icn_add_normal.png",
                                    ":/bit/image/2_icn_add_normal.png",
                                    ":/bit/image/3_icn_add_normal.png",
                                    ":/bit/image/4_icn_add_normal.png"};

const QByteArray PLUSPICCLICK[] = {":/bit/image/1_icn_add_click.png",
                                   ":/bit/image/2_icn_add_click.png",
                                   ":/bit/image/3_icn_add_click.png",
                                   ":/bit/image/4_icn_add_click.png"};

const QByteArray PLUSPICNORMALNIGHT[] = {":/bit/image/1_night_plug_normal.png",
                                         ":/bit/image/2_night_plug_normal.png",
                                         ":/bit/image/3_night_plug_normal.png",
                                         ":/bit/image/4_night_plug_normal.png"};

const QByteArray PLUSPICCLICKNIGHT[] = {":/bit/image/1_night_plug_click.png",
                                        ":/bit/image/2_night_plug_click.png",
                                        ":/bit/image/3_night_plug_click.png",
                                        ":/bit/image/4_night_plug_click.png"};
/**
* @brief for delete and add mode to change plus btn position
*/
enum PLUSPOSI
{
  SPX = 297,
  STEPP = 279,
  DETAP = 47,
  SPY = 0
};

/**
* @brief for measure items widget position 769
*/
enum MESAWIDPOSI
{
  MX = 282,
  MY = 45,
  MW = 428,
  MH = 620
};

enum MODWIDPOSI
{
  MMX = 0,
  MMY = 44,
  MMW = 282,
  MMH = 720,
  MMD = 35
};

/**
* @brief for seting widget position
*/
enum SETWIDPOSI
{
  SMX = 282,
  SMY = 46,
  SMW = 997,
  SMH = 720
};

enum SETITEM
{
  COM_SET = 0,
  DSDT_SET,
  NETWORK_SET,
  LICE_SET,
  HSW_SET,
  SYS_SET
};

/**
* @brief indicate battary charge state
*/
enum BATTARYCHARGE
{
  UN_BATT = 0,
  BATT_CHARGE,
  BATT_DISCHARGE,
  BATT_FULL
};

/**
* @class
* @brief
*/
enum REFTYPE
{
  GPSREF = 0,
  EXT10M,
  EXT13M,
  EXT15M,
  INNER10M,
  NONEREF
};

/**
* @class
* @brief
* @since {2019-08-22}
*/
enum LANGTYPE
{
  CHINELAN = 0,
  ENGLISHLAN,
  JAPANLAN,
  KOREANLAN,
  NONELAN
};

enum NOTICEPOS
{
  PLTX = 475,
  PLTY = 265
};

/**
* @class for debug widget using
* @brief
*/
typedef struct Devel
{
  qint32 qsoci;
  qint32 secifatten;
  char swver[64];
  char hwver[64];
  char update[64];
}DEVEMSG,*PDEVEMSG;

/**
* @class sys state include power preset
* @brief
*/
typedef struct Plt_Pre_State
{
  qint32 powerstate;
}PLTPRESTATE,*PPLTPRESTATE;

/**
* @class plt all states to save and recover
* @brief
*/
typedef struct Plt_State_Param
{
  qint32 ilastallmesa[NONEMODE];
  qint32 iallmesa[NONEMODE];//!<this used to maintain all mode now measure index,
  //!<when any mode change measure itself should reflesh this butter at the same time

  qint32 iuimode[UIMODMAXNUM];//!<no more than 4 in ui

  qint32 nowshowmodsum;
  quint32 orimode;//!<last run modBitRtSa *pRtsaAna;  e,for compare now shm mode,if same,do nothing
  qint32 oribtnIndex;

  PLTPRESTATE pltpres;
  qint32 syssetindex;
  qint32 lantype;
  qint32 freqref;

  qint32 sleept;
  qint32 dismod;
  qint32 lcdbright;
  qint32 soundnum;
  qint32 soundswitch;
  qint32 datetype;

  qint32 gpswitch;
  qint32 gkeybeepswitch;
  qint32 lanport;
  char ipstr[32];
  char maskstr[32];
  char gatewaystr[32];

  qint32 remoteintertype;
  qint32 wifiswitch;
  qint32 blumode;
  qint32 bluetswitch;
  char wifimib[32];//unUsed
}PLTSTATEPARAM,*PPSTATEPARAM;

/**
* @brief to trigger sys action
*/
#define PLT_IXT_ConfigSystem         (0x00000004)
#define PLT_IXS_IPAddress             0x00000001
#define PLT_IXS_NetMask               0x00000002
#define PLT_IXS_GateWayAddress        0x00000004
#define PLT_IXS_Local_Remote	  0x00000008
#define PLT_IXS_LcdpadLight		  0x00000010
#define PLT_IXS_LCDBrightness         0x00000020
#define PLT_IXS_SleepMode		  0x00000040
#define PLT_IXS_Volume		  0x00000080
#define PLT_IXS_KeyBeep		  0x00000100
#define PLT_IXS_LimitBeep		  0x00000200
#define PLT_IXS_FWupdateRequest       0x00000400
#define PLT_IXS_TouchScreen           0x00000800
#define PLT_IXS_BurnAction            0x00001000
#define PLT_IXS_SwitchPic     0x00002000
#define PLT_IXS_InvenAppMajor         0x00004000
#define PLT_IXS_InvenAppMiinor        0x00008000
#define PLT_IXS_ADCOVER      0x00010000
#define PLT_IXS_SELFTEST	  0x00020000
#define PLT_IXS_InvenSerialNo 	  0x00040000
//this part about sys info use one command is OK
#define PLT_IXS_PSModel  		  0x00080000
#define PLT_IXS_FreqCalc 		  0x00100000
#define PLT_IXS_SecIfAtten 		  0x00200000
//#define PLT_IXS_PSSerialNo 		  0x00400000
//#define PLT_IXS_PSInvenMajor 	  0x00800000
//#define PLT_IXS_PSInvenMinor 	  0x01000000
//#define PLT_IXS_PSTemp 		  0x00100000
#define PLT_IXS_GPSWitch 		  0x00200000
#define PLT_IXS_WIFI    0x00400000
#define PLT_IXS_BLUETOOTH  0x00800000
#define PLT_IXS_Ref			  0x01000000
#define PLT_IXS_Calc			  0x02000000
#define PLT_IXS_PLAYMUSICON		  0x04000000
#define PLT_IXS_PLAYMUSICOFF		  0x08000000


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


#endif // SOFTBUS_H
