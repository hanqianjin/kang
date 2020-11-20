#ifndef shmengine_H
#define shmengine_H

#include <QObject>
#include <QVector>

#define SA_SHM_KEY 5500 //!<in sa ctrl app also
#define RTSA_SHM_KEY 5501 //!<in rtsa ctrl app also
#define HOME_SHM_KEY 5530 //!<in home app also
#define CALC_SHM_KEY 5531 //!<in calc notic app also
#define PLT_ALL_SHM_KEY 5551 //!<in all mod for notice

#define SYS_CONF_KEY 5602 //!<in sys ctrl app also
#define SYS_INFO_KEY 5605 //!<in sys ctrl app and home app also
#define SYS_BURN_KEY 5688 //!<in sys ctrl app also

typedef struct all_notice
{
  quint32 noticode;//!< none zero means notice happened
}ALL_NOTIC_CODE,*PALL_NOTIC_CODE;

typedef struct shmnotic
{
  qint32 notic; //!<1 means to start calc,-1 means to upgrade
}SHM_NOTIC,*PSHM_NOTIC;

/**
* @brief should be defined in home app also
*/
typedef struct shmhome
{
  quint32 remotecloseflag;
  quint32 modetype;
  quint32 systype;//!<this use when home set sys ctrl different with other mode switch
  qint32 modesource;//!<when mode switch by home modesource = ON
}SHM_HOME,*PSHM_HOME;

/**
* @brief should be defined in sa ctrl app also
*/
typedef struct shmsa
{
  quint32 appexit;

}SHM_SA,*PSHM_SA;

/**
* @brief should be defined in rtsa ctrl also
*/
typedef struct shmrtsa
{
  quint32 appexit;
}SHM_RTSA,*PSHM_RTSA;

/**
* @brief should be defined in sys ctrl also
*/
typedef struct shmsysconf
{
  qint8 IPAddress[16];
  qint8 NetMask[16];
  qint8 GateWayAddress[16];
  quint32 Local_Remote;				// [0]Local, [1]Remote
  quint32 LcdpadLight;				// [0]Off, [1]On
  quint32 LCDBrightness;		        // [0 ~ 100] %
  quint32 SleepMode;
  quint32 Volume;				// [0 ~ 5]
  quint32 KeyBeep;				// [0]Off, [1]On
  quint32 LimitBeep;				// [0]Off, [1]On
  quint32 FWupdateRequest;			// [0]Off, [1]Request
  quint32 TouchScreen;
  quint32 AnaMode;                              //in RUNMODE order to tell sys app whitch bitstream to burn
  quint32 PicSwitch;
  quint32 mainfpgaver;         //ControlApp Major Version
  quint32 spafpgaver;        //ControlApp Minor Version
  quint32 cpldver;      //DSP Revision Number
  quint32 adcover;
  quint32 selftest;
  quint8 InvenSerialNo[16];      //System Serial Number
  quint8 PSModel[16];            //Power Sensor Model Name
  quint32 PSType;                //Power Sensor Type
  quint32 PSFreqVol;              //Power Sensor Method
  quint8 PSSerialNo[16];         //Power Sensor Serial Number
  quint32 PSInvenMajor;          //Power Sensor Major Version
  quint32 PSInvenMinor;          //Power Sensor Minor Version
  qreal PSTemp;                  //Power Sensor Temperature
  quint32 Gpswitch;              //[0]disable, [1]enable
  char WavFileName[100];       //WavFileName
  qint32 wifiswitch;
  qint32 bluetwitch;  //PON open
  quint32 refset;  
  qint32 Convertflag;
  qint32 secifatten;
}SHM_SYS_CONF,*PSHM_SYS_CONF;

/**
* @brief should be defined in sys ctrl also
*/
typedef struct shmsysinfo
{
  qreal BoardTemp;               //Carrier Baord Temperature
  qreal RfTemp;               //Carrier Baord Temperature
  quint32  BatteryOnLine;        //[0] no battery, [1] have battery
  float BatteryTemp;             //Battery Temperature
  quint32 BatteryRemaind;        //[0 ~ 100] %
  quint32 BatterChargeStatus;    //[0]Unknown,[1]Charging, [2]Discharging, [3]Full
  quint32 ACStatus;              //[0]AC Power, [1]Battery Power
  float batvol;
  float batcurrent;
  quint32 LanPortStatus;         //[0]Link Down, [1]Link Up
  quint32 USBMemoryStatus;       //[0]None, [1]Insert
  quint8 DeviceMsg[50];          //Device Info / Error Message
  quint32 BoardTempAlarm;        //[0]Normal,
  quint32 BatteryTempAlarm;      //[0]Normal,

  char GPSLatitude[100];       //GPS Info - Latitude (N 3722.04194)
  char GPSLongitude[100];      //GPS Info - Longitude (E 12638.92059)
  char GPSDate[11];            //GPS Info - Date (190117)
  char GPSTime[12];            //GPS Info - Time (130934.00)
  qreal GPSElevation;            //GPS elevation
  quint32 GPSStatus;             //GPS status [0] Invalid [1] fixed [2] Differential [3] Sensitive
  quint32 GPSSatelliteNum;       //GPS Satellite in use 
  quint32 GPSInView;
  qreal GpsSpeedKmh;
  qreal GpsDirection;
  quint32 GpsOperMode;
  quint32 GpsPrnNumber;

  qreal FpgaTemp;
  quint32 datetype;
  qint32 dismode;//to tell Home App to Change dismode
}SHM_SYS_INFO,*PSHM_SYS_INFO;

/**
* @brief should be defined in sys ctrl also,to trig action
*/
typedef struct shmsysactionplt
{ 
  quint32 top_flag_conf;  //once mode
  quint32 top_flag_sys;//polling mode
  quint32 system_flag_conf;
  quint32 sys_flag_info;
}SHM_SYS_ACTION,*PSHM_SYS_ACTION;

class shmengine
{
private:
  shmengine();

public:
  static qint32 GetSempC(qint32 semphandle);
  static qint32 ReleaseSempC(qint32 semphandle);
  static shmengine* getsingleshm();
  static qint32 PassTrigToSys(quint32 itopflag,quint32 itemflag);
  static qint32 PassTrigToSysExt(quint32 itopflag,quint32 itemflag);

  PALL_NOTIC_CODE pshm_pltnotic;
  PSHM_HOME pshm_home;
  PSHM_SYS_CONF pshm_sysconf;
  PSHM_SYS_INFO pshm_sysinfo;
  PSHM_SYS_ACTION pshm_sysaction;
  PSHM_NOTIC pshm_calnotic;
  QVector<quint32*> pctrlexitvec;

private:
  qint32 shm_pltnoti_id;
  qint32 shm_home_id;  
  qint32 shm_sysconf_id;
  qint32 shm_sysinfo_id;
  qint32 shm_sysaction_id;
  qint32 shm_sa_id;
  qint32 shm_rtsa_id;  
  qint32 shm_calnot_id;

  PSHM_SA pshm_sa;
  PSHM_RTSA pshm_rtsa;

  qint32 inishmengine();
  void inishmembers();
  void addallctrlexit();

  static shmengine *shmobj;
};

#endif // shmengine_H
