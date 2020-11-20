#ifndef shmengine_H
#define shmengine_H

#include <QObject>
#include <QVector>

#define SA_SHM_KEY 5500 //!<in sa ctrl app also
#define RTSA_SHM_KEY 5501 //!<in rtsa ctrl app also
#define HOME_SHM_KEY 5530 //!<in home app also

#define SYS_CONF_KEY 5602 //!<in sys ctrl app also
#define SYS_INFO_KEY 5605 //!<in sys ctrl app also

/**
* @brief should be defined in home app also
*/
typedef struct shmhome
{
  quint32 modetype;

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
  quint32 KeypadLight;				// [0]Off, [1]On
  quint32 LCDBrightness;		        // [0 ~ 100] %
  quint32 SleepMode;			        // [0]Off, [1 ~ 60] Minute
  quint32 Volume;				// [0 ~ 5]
  quint32 KeyBeep;				// [0]Off, [1]On
  quint32 LimitBeep;				// [0]Off, [1]On
  quint32 FWupdateRequest;			// [0]Off, [1]Request
  quint32 TouchScreen;
}SHM_SYS_CONF,*PSHM_SYS_CONF;

/**
* @brief should be defined in sys ctrl also
*/
typedef struct shmsysinfo
{
  quint32 InvenAppMajor;         //ControlApp Major Version
  quint32 InvenAppMiinor;        //ControlApp Minor Version
  quint32 InvenDSPRevision;      //DSP Revision Number
  quint32 InvenDSPDate;          //DSP Compile Date (0828 => 8/28)
  quint8 InvenSerialNo[16];      //System Serial Number
  float BoardTemp;               //Carrier Baord Temperature
  quint32  BatteryOnLine;        //[0] no battery, [1] have battery
  float BatteryTemp;             //Battery Temperature
  quint32 BatteryRemaind;        //[0 ~ 100] %
  quint32 BatterChargeStatus;    //[0]Unknown,[1]Charging, [2]Discharging, [3]Full
  quint32 ACStatus;              //[0]AC Power, [1]Battery Power
  quint32 LanPortStatus;         //[0]Link Down, [1]Link Up
  quint32 USBMemoryStatus;       //[0]None, [1]Insert
  quint8 DeviceMsg[50];          //Device Info / Error Message
  quint32 BoardTempAlarm;        //[0]Normal,
  quint32 BatteryTempAlarm;      //[0]Normal,
  quint8 PSModel[16];            //Power Sensor Model Name
  quint32 PSType;                //Power Sensor Type
  quint32 PSMethod;              //Power Sensor Method
  quint8 PSSerialNo[16];         //Power Sensor Serial Number
  quint32 PSInvenMajor;          //Power Sensor Major Version
  quint32 PSInvenMinor;          //Power Sensor Minor Version
  qreal PSTemp;                  //Power Sensor Temperature
  quint32 PSStatus;              //[0]Wait, [1]Conneted, [2]Disconnected
  quint8 GPSLatitude[100];       //GPS Info - Latitude (N 3722.04194)
  quint8 GPSLongitude[100];      //GPS Info - Longitude (E 12638.92059)
  quint8 GPSDate[11];            //GPS Info - Date (190117)
  quint8 GPSTime[12];            //GPS Info - Time (130934.00)
  qreal GPSElevation;            //GPS elevation
  quint32 GPSStatus;             //GPS status [0] Invalid [1] fixed [2] Differential [3] Sensitive
  quint32 GPSSatelliteNum;       //GPS Satellite in use
  quint8 WavFileName[100];       //WavFileName
  quint32 Volume;                // system volume
}SHM_SYS_INFO,*PSHM_SYS_INFO;

class shmengine
{
private:
  shmengine();

public:
  static qint32 GetSempC(qint32 semphandle);
  static qint32 ReleaseSempC(qint32 semphandle);
  static shmengine* getsingleshm();

  PSHM_HOME pshm_home;
  PSHM_SYS_CONF pshm_sysconf;
  PSHM_SYS_INFO pshm_sysinfo;
  QVector<quint32*> pctrlexitvec;

private:
  qint32 shm_home_id;  
  qint32 shm_sysconf_id;
  qint32 shm_sysinfo_id;
  qint32 shm_sa_id;
  qint32 shm_rtsa_id;  

  PSHM_SA pshm_sa;
  PSHM_RTSA pshm_rtsa;

  qint32 inishmengine();
  void inishmembers();
  void addallctrlexit();

  static shmengine *shmobj;
};

#endif // shmengine_H
