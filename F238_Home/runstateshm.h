#ifndef RUNSTATESHM
#define RUNSTATESHM

#include <QObject>

#define HOME_UI_SHOW_KEY 5550 //!<in all modes also,not shm but sync id
#define HOME_SHM_KEY 5530 //!<in platform app also
#define HOME_SEM_DICTION 5551

#define SYS_INFO_KEY 5605 //!<in platform app and sys ctrl app also
#define SYS_BURN_KEY 5688 //!<in sys ctrl app also

typedef struct home_notice
{
  quint32 noticode;//!< none zero means notice happened
}HOME_NOTIC_CODE,*PHOME_NOTIC_CODE;

/**
* @brief should be defined in platform also
*/
typedef struct shmhome
{
  quint32 remotecloseflag;//!<when remote and homeui show then seams by platform to close PON means to close
  quint32 modetype;
  quint32 systype;//when pon means setting sys
  qint32 modesource;
}SHM_HOME,*PSHM_HOME;

/**
* @brief should be defined in sys ctrl and platform also
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
  quint8 GPSLatitude[100];       //GPS Info - Latitude (N 3722.04194)
  quint8 GPSLongitude[100];      //GPS Info - Longitude (E 12638.92059)
  quint8 GPSDate[11];            //GPS Info - Date (190117)
  quint8 GPSTime[12];            //GPS Info - Time (130934.00)
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
  qint32 dismode;
}SHM_SYS_INFO,*PSHM_SYS_INFO;

/**
* @brief should be defined in sys ctrl also,to trig action
*/
typedef struct shmsysaction
{
  quint32 top_flag;  //Indicates a mode update
  quint32 system_flag;
}SHM_SYS_ACTION,*PSHM_SYS_ACTION;

class RunStateShm
{
private:
  RunStateShm();

public:
  qint32 homeuihandle;
  PSHM_HOME  pshm_home;
  PSHM_SYS_INFO pshm_sysinfo;
  PSHM_SYS_ACTION pshm_sysaction;
  PHOME_NOTIC_CODE pshm_homenotic;

private:
  qint32 IniSaShm();
  void IniShmMem();

public:
  static qint32 GetSemp(qint32 semphandle);
  static qint32 ReleaseSemp(qint32 semphandle);
  static RunStateShm* getsingleshm();
  static qint32 PassTrigToSys(quint32 itopflag,quint32 itemflag);

private:
  static RunStateShm *pshm;

  qint32 shm_home_id;
  qint32 shm_sysinfo_id;
  qint32 shm_sysaction_id;
  qint32 shm_homenoti_id;

};

#endif
