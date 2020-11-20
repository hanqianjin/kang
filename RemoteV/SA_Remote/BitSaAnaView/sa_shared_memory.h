#ifndef SHARED_MEMORY
#define SHARED_MEMORY
#include <pthread.h>
#include <sys/types.h>
#include <qglobal.h>

typedef struct
{
    quint32 rbwkHz;         //rbw
    qreal sampRateHz;	 //the fds
    qreal stepFreqHz;	 //lo step
    quint32 fftNum;		     //FFT num
    qreal winAlpha;		 //win coef
    qreal respondTimeus;	 //respond time(switch channel and IF fliter time)
    qreal validRatio;     //efficient
    quint32 singleacqTime;		 //the num of fs
    qreal tsms;
    quint32 orderNum;
} SA_CHANNEL_PARAM,*SA_PCHANNEL_PARAM;

#endif // SHARED_MEMORY
#if 0
#ifndef SHARED_MEMORY
#define SHARED_MEMORY

#include <pthread.h>
#include <sys/types.h>
#include <qglobal.h>
// shared memory
#define SM_SA_Key_ConfigSweep						5600
#define SM_SA_Key_ConfigMeasure					    5601
//#define SM_SA_Key_ConfigSystem						5602
#define SM_SA_Key_SweepData						    5603
#define SM_SA_Key_MeasureData						5604
//#define SM_SA_Key_SystemInfo						5605
#define SM_SA_Key_Sync							    5606
#define SM_SA_Key_ConfigUpdate					    5607



// index top flag
#define IXT_SA_ConfigSweep							0x00000001
#define IXT_SA_ConfigMeasure						0x00000002
#define IXT_SA_ConfigTrigger                        0x00000004
//#define IXT_SA_ConfigSystem						0x00000004
#define IXT_SA_ConfigDrCtrlSweep                    0x00000008


// index sub flag - config sweep
#define IXS_SA_ConfigSweepFlagMax				   26
#define IXS_SA_CenterFreq						   0x00000001
#define IXS_SA_SpanFreq							   0x00000002
#define IXS_SA_StartFreq						   0x00000004
#define IXS_SA_StopFreq							   0x00000008
#define IXS_SA_SpanMode							   0x00000010
#define IXS_SA_TracePoint						   0x00000020
#define IXS_SA_RBW			    				   0x00000040
#define IXS_SA_RBWAuto							   0x00000080
#define IXS_SA_VBW				    			   0x00000100
#define IXS_SA_VBWAuto							   0x00000200
#define IXS_SA_DetectorMode						   0x00000400
#define IXS_SA_RefLevel							   0x00000800
#define IXS_SA_AttenSelect						   0x00001000
#define IXS_SA_SweepType						   0x00002000
#define IXS_SA_ZeroSpanTime					       0x00010000
#define IXS_SA_ZeroSpanMode					       0x00020000
#define IXS_SA_Preamp							   0x00040000
#define IXS_SA_ImageRejection					   0x00080000
#define IXS_SA_SweepTimeAuto                       0x00100000//Johnson 0718
#define IXS_SA_SweepTime                           0x00200000//Johnson 0718
//#define IXS_MarkerCount                         0x00400000//Johnson 1129

//0829 steve
#define IXS_SA_CheckAciton                         0x00400000
#define IXS_SA_Refoffset                           0x00800000

#define IXS_SA_PARALOAD                            0x04000000//Johnson 190412
#define IXS_SA_ZeroRestrain                        0x08000000//Johnson 190422
#define IXS_SA_IFmode                              0x10000000//Johnson 0425
#define IXS_SA_MARKERFRECOUNT                      0x20000000//Johnson 0710
#define IXS_SA_DOTSWEEPTIME                        0x40000000//Johnson 0729

// index sub flag - config measure
#define IXS_SA_ConfigMeasureFlagMax				    7
#define IXS_SA_MeasureMode							0x00000001
#define IXS_SA_ChannelBW							0x00000002
#define IXS_SA_ChannelSpacing						0x00000004
#define IXS_SA_DemodFreq				        	0x00000008
#define IXS_SA_DemodIFBW		        			0x00000010
#define IXS_SA_DemodMode					        0x00000020
#define IXS_SA_PSFreq					   	        0x00000040

//index sbu flag ---- config trigger
#define IXS_SA_TriggerMode						   0x00000001
#define IXS_SA_TriggerDirect                       0x00000002
#define IXS_SA_TriggerDelayTime                    0x00000004
#define IXS_SA_TriggerPerTime                      0x00000008
#define IXS_SA_VedioTriggerAmp                     0x00000010
#define IXS_SA_RFBurstTriggerAmp                   0x00000020

//index sbu flag ---- config trigger
#define IXS_SA_DrCtrlSource                   0x00000001
#define IXS_SA_LvlEdgModeSelect               0x00000002
#define IXS_SA_LvlEdgValueSelect              0x00000004
#define IXS_SA_DrCtrlSweepMode                0x00000008
#define IXS_SA_PrdTrigSycSrcSelect            0x00000010
#define IXS_SA_DrCtrlSweepSwitch              0x00000020

#define IXS_SA_EdgTrigDelay                   0x00000040
#define IXS_SA_EdgTrigDrWidth                 0x00000080
#define IXS_SA_EdgTrigPrvtSwitch	          0x00000100
#define IXS_SA_EdgTrigPrvtValue               0x00000200
#define IXS_SA_RFBurst_TrigLevel              0x00000400

#define IXS_SA_PrdTrigPeriod                  0x00000800
#define IXS_SA_PrdTrigSycSrcDelay             0x00001000
#define IXS_SA_PrdTrigPrvtSwitch	          0x00002000
#define IXS_SA_PrdTrigPrvtValue               0x00004000


// index sub flag - config system
/*#define IXS_SA_ConfigSystemFlagMax					11
#define IXS_SA_IPAddress							0x00000001
#define IXS_SA_NetMask								0x00000002
#define IXS_SA_GateWayAddress						0x00000004
#define IXS_SA_Local_Remote						    0x00000008
#define IXS_SA_KeypadLight							0x00000010
#define IXS_SA_LCDBrightness						0x00000020
#define IXS_SA_SleepMode					        0x00000040
#define IXS_SA_Volume								0x00000080
#define IXS_SA_KeyBeep								0x00000100
#define IXS_SA_LimitBeep							0x00000200
#define IXS_SA_FWupdateRequest						0x00000400*/

//added by Steve
#define SYNC_SA_KEY       5611
#define SYNC_SA_KEY_GUI   5612
#define SM_SA_Key_Channelparam						5608
#define SM_SA_Key_FftFirCommonnum	5609
#define SM_SA_Key_SweepNum   5610
//#define SYNC_SWEEP    5613//Johnson 0712
#define SM_CTRL7_KEY_START    5614 //Johnson 190524

//steve,0524
#define SA_HOME_UI_SHOW_KEY 5550
//0525
#define SA_BSA_VISI_KEY 5502


//Johnson 091009
#define USABLE 0


typedef struct
{
  quint32 visiableflag;
}SA_BIT_BSA_VISI,*SA_PBIT_BSA_VISI;

typedef struct
{
    quint32 top_flag;
    quint32 sweep_flag;
    quint32 measure_flag;
#if USABLE
    quint32 system_flag;
#endif
    quint32 trigger_flag;
    quint32 doorControl_flag;
}SA_CONFIG_UPDATE;

typedef struct
{
    qreal CenterFreq; 	            // Hz
#if USABLE
    qreal SpanFreq; 	            // Hz
#endif
    qreal StartFreq; 	            // Hz
    qreal StopFreq; 	            // Hz
    quint32 SpanMode;		    // [0]Normal, [1]Zero SA_SPAN
    quint32 TracePoint;        // [0]501, [1]1001, [2]2001, [3]3001 (point)
    quint32 RBW; 			    // Hz
#if USABLE
    quint32 RBWAuto;		    // [0]Manual, [1]Auto
#endif
    quint32 VBW; 			    // Hz
#if USABLE
    quint32 VBWAuto; 		    // [0]Manual, [1]Auto
#endif
    quint32 DetectorMode;	    // [0]Max, [1]Min, [2]Sample, [3]Avg-Power, [4]Avg-Voltage
    qreal RefLevel;				// +10 ~ -150 dBm
#if USABLE
    quint32 AttenSelect;		// [0]0, [1]5, [2]10, [3]15, [4]20, [5]25, [6]30 (dB)
#endif
    quint32 SweepType;		    // [0]Continuous, [1]Single, [2]Sweep Offk
#if USABLE
    qreal ZeroSpanTime;	        // milisecond
    quint32 ZeroSpanMode;		// [0]Amplitude, [1]Frequency, [2]Phase
#endif
    quint32 Preamp;			// [0]Off, [1]On
#if USABLE
    quint32 ImageRejection;	// [0]Off, [1]On
#endif

    //added by Steve
    qreal attenValue;
    quint32 attenAuto;//0 man,1 aut0
    quint32 sweepMode;       //sweep mode 00 FIR,11 FFT
#if USABLE
    qreal VBWTORBW;	//the default  = 1.0
    quint32 VBWTORBWAuto;//	[0]Manual, [1]Auto
#endif
    quint32 ListenState;//0323

    //by steve,0423
    quint32 ischangeRbwitself;//when change rbw by freq,its value is 0,when change rbw by itself,its value is 1
#if USABLE
    //Johnson 0503
    quint32 uisPreampChangedItself;
    //Johnson 0718
    quint32 AutoSweepTime;
    qreal SweepTime;
#endif

    //0829 steve
    quint32 checkswitch;//0 check ,1 direct
    //0904 steve
    qint32 checkinsert;//this used for software ctrl only,-1 check and not insert,0 check and insert,1 direct and insert
    qreal firstper;//only when two channel will use secper
    qreal secper;
    //0905
    qreal spanperstep;

    //Johnson 190410
    qint32 dZeroRestrainAtten;
    qreal dZeroRestrainPhase;

    //Johnson 190412
    quint32 uSweepCompleteFlag;//1 means that current sweep complete,0 means that current sweep is running
    quint32 uAllSweepCompleteFlag;//GUI->CtrlApp    1 means that all sweep complete or average is not open,0 means that sweep is running
    //Johnson 190425
    quint32 uIFMode; //0 means SA_OFF    1 means Narrow 10MHz  2 means Wide 100MHz
#if USABLE
    quint32 uMsCompleteFlag;   //used to when mode is spurious or spectrum,1 means that measure complete,0 means that measure is running
#endif

    quint32 TriggerMode;
    quint32 TriggerDirect;
    qreal   TriggerDelayTime;
    qreal   TriggerPerTime;
    qint32   VedioTriggerAmp;
    qint32   RFBurstTriggerAmp;

    quint32 markerFreqCount;

    quint32 uMinMaxHoldComplete;//Johnson 190712 this param is 0 when trace type is setted maxHold or minHold,and it is 1 when the first series data is acquired
                                //completely at the maxHold or minHold trace type
    qreal signalFreq;

    qint32  DrCtrlSource;
    qint32  LvlEdgSelect;
    qint32  LvlEdgMode;
    qint32  DrCtrlSweepMode;
    qint32  PrdTrgSynchroSrc;
    qint32  DrCtrlSwitch;
    qreal   EdgTrigDely;
    qreal   EdgTrigDoorWdth;
    qint32  EdgTrigPrvntStatus;
    qreal   EdgTrigPrvntTimes;
    qreal   RFBurstTrigLevel;
    qreal   PrdTrgPeriod;
    qreal   PrdTrgSrcDelay;
    qint32  PrdTrigPrvntStatus;
    qreal   PrdTrigPrvntTimes;
}SA_CONFIG_SWEEP; // GUI -> Ctrlapp

typedef struct
{
    quint32 MeasureMode;	// [0]Off, [1]Channel Power, [2]SA_ACP, [3]Demoduleation, [4] Power Sensor
#if USABLE
    qreal ChannelBW;			// Hz
    qreal ChannelSpacing;		// Hz
    qreal DemodFreq;	        // Hz
    qreal DemodIFBW;	        // Hz
    quint32 DemodMode;	    // [0]SA_AM, [1]SA_FM, [2]SA_NFM
    qreal PSFreq; 	            // powersensor freq. Hz
#endif
}SA_CONFIG_MEASURE; // GUI -> Ctrlapp


/*typedef struct
{
    qint8 IPAddress[16];						// "255.255.255.255"	string
    qint8 NetMask[16];						// "255.255.255.255" string
    qint8 GateWayAddress[16];				// "255.255.255.255" string
    quint32 Local_Remote;				// [0]Local, [1]Remote
    quint32 KeypadLight;				// [0]Off, [1]On
    quint32 LCDBrightness;				// [0 ~ 100] %
    quint32 SleepMode;			        // [0]Off, [1 ~ 60] Minute
    quint32 Volume;					// [0 ~ 5]
    quint32 KeyBeep;					// [0]Off, [1]On
    quint32 LimitBeep;					// [0]Off, [1]On
    quint32 FWupdateRequest;			// [0]Off, [1]Request
    quint32 TouchScreen;			// [0]Disable, [1]Enable

}SA_CONFIG_SYSTEM;	// GUI -> Ctrlapp*/

typedef struct
{
#if USABLE
    quint32 _TotalNumber;
#endif
    //add by Steve
    qreal _PwrLevel[1000];
#if USABLE
    quint32 SweepTime;
#endif
    qint32  fsr;
    qreal CalData;
}SA_SWEEP_DATA; // Ctrlapp -> GUI

#if USABLE
typedef struct
{
    qreal ChannelPwr;
    qreal ACPR;
    qreal ACPL;
    qreal PSLevel;				// powersensor data - powerlevel
}SA_MEASURE_DATA; // Ctrlapp -> GUI
#endif

/*typedef struct
{
    quint32 InvenAppMajor;         //ControlApp Major Version
    quint32 InvenAppMiinor;        //ControlApp Minor Version
    quint32 InvenDSPRevision;      //DSP Revision Number
    quint32 InvenDSPDate;          //DSP Compile Date (0828 => 8/28)
    quint8 InvenSerialNo[16];        //System Serial Number
    float BoardTemp;                    //Carrier Baord Temperature
    quint32  BatteryOnLine;        //[0] no battery, [1] have battery
    float BatteryTemp;                  //Battery Temperature
    quint32 BatteryRemaind;        //[0 ~ 100] %
    quint32 BatterChargeStatus;    //[0]Unknown,[1]Charging, [2]Discharging, [3]Full
    quint32 ACStatus;              //[0]AC Power, [1]Battery Power
    quint32 LanPortStatus;         //[0]Link Down, [1]Link Up
    quint32 USBMemoryStatus;       //[0]None, [1]Insert
    quint8 DeviceMsg[50];            //Device Info / Error Message
    quint32 BoardTempAlarm;        //[0]Normal, [1]85 ��C Over
    quint32 BatteryTempAlarm;      //[0]Normal, [1]80 ��C Over
    quint8 PSModel[16];              //Power Sensor Model Name
    quint32 PSType;                //Power Sensor Type
    quint32 PSMethod;              //Power Sensor Method
    quint8 PSSerialNo[16];           //Power Sensor Serial Number
    quint32 PSInvenMajor;          //Power Sensor Major Version
    quint32 PSInvenMinor;          //Power Sensor Minor Version
    qreal PSTemp;                       //Power Sensor Temperature
    quint32 PSStatus;              //[0]Wait, [1]Conneted, [2]Disconnected
    quint8 GPSLatitude[100];     //GPS Info - Latitude (N 3722.04194)
    quint8 GPSLongitude[100];    //GPS Info - Longitude (E 12638.92059)
    quint8 GPSDate[11];           //GPS Info - Date (190117)
    quint8 GPSTime[12];          //GPS Info - Time (130934.00)
    qreal GPSElevation;                 //GPS elevation
    quint32 GPSStatus;             //GPS status [0] Invalid [1] fixed [2] Differential [3] Sensitive
    quint32 GPSSatelliteNum;       //GPS Satellite in use
    quint8 WavFileName[100];     //WavFileName
    quint32 Volume;                    // system volume
}SA_SYSTEM_INFO; // Ctrlapp -> GUI*/


typedef struct
{
    quint32 SweepUpdate;       //[0]Wait, [1]Update Ok, [2]ChangeParameter
    quint32 BWUpdate;          //SA_BW Changed from ControlApp (Only SA_BW Auto Mode)
    quint32 CtrlAppRunOk;      //ControlApp Alive Message (First RUN)
    quint32 CtrlAppAlive;      //ControlApp Alive Signal, [0]->[1]->[0]-> ��. (��1 second)
    quint32 DeviceMsgUpdate;   //Device Message Update

    //added by Steve
    quint32 AppExit;//the ctrlapp is over
    quint32 SysparamReflesh;//1 reflesh over  Johnson 0712
    quint32 BufferSync;//when 0 means the gui has finished copy the shm to gui local,and ctrl will copy ctrl local to shm then set 1
                            //when 1 means the ctrl has finished copy the ctrl local to shm,and gui will copy the shm to gui local then set 0
}SA_SM_SYNC;	// Ctrlapp -> GUI


//190619
#define IXT_Tempercalc (0x00010000)
#define SM_Key_TemperCalc    5509
typedef struct sa_temper_calc
{
    quint32 calctop;
    qreal detatemp;
}SA_TEMP_CALC,*SA_PTEMP_CALC;

//added by Steve
typedef struct
{
    quint32 rbwkHz;         //rbw
    qreal sampRateHz;	 //the fds
    qreal stepFreqHz;	 //lo step
    quint32 fftNum;		     //FFT num
    qreal winAlpha;		 //win coef
    qreal respondTimeus;	 //respond time(switch channel and IF fliter time)
    qreal validRatio;     //efficient
    quint32 singleacqTime;		 //the num of fs
    qreal tsms;
    quint32 orderNum;
} SA_CHANNEL_PARAM,*SA_PCHANNEL_PARAM;

typedef struct
{
     quint32 segmentIndex;	 //segment index
     quint32 segmentDataNum;  //segment data num
     quint32 seglostartfreqinter;/*high 32bit*/
     quint32 seglostartfreqfrac;/*low 32bit*/
    qreal persegfftsegNum;//per segment fft step nums
	//by steve,0504
	//u_int64_t persegsweeptimes;//per segment sweep times
    qreal persegsweeptimes;

	//Steve,0328
    quint32 seglosteplow;//per segment lo step low 32 bits,fir/fft mode
    quint32 seglostephigh;//per segment lo step high 16 bits,fir/fft mode
} SA_FFT_FIR_COMMON_NUM,*SA_PFFT_FIR_COMMON_NUM;

typedef struct
{
     quint32 startIndex;		 //valid start index
     quint32 stopIndex;		 //valid stop index
     quint32 fftNum;			 //fft calc num
     //quint32 fftBucketnum;//fft bucket num
     //0726
    qreal fftBucketnum;
    qreal singlefftTime;   //single fft num acq time
    qreal loStepHz;		 //lo step
    qreal validRatio;     //efficient
     quint32 segmentNum;//decided by start and stop freq
     //quint32 lostepdivfreqlow;/*0~31bit*/
    // quint32 lostepdivfreqhigh;/*32~47bit*/
     quint32 seglokeeptime;//seg last part lo keep time
    qreal sumSweeptime;//span sweep time

    //0719 steve
    qreal firdottimems;

	//Steve 0424
    qreal firBucketimeus;//means us
    quint32 segmentsDataSumNum;//from start to end all points num
    SA_FFT_FIR_COMMON_NUM comNum[19];
    //SA_FFT_FIR_COMMON_NUM comNum[14];//Johnson 190919
}SA_SWEEP_NUM,*SA_PSWEEP_NUM;

typedef struct
{
    quint32 startedflag;
}SA_START_FLAG,*SA_PSTART_FLAG;

//LO:local oscillation

//Johnson 0712
/*typedef enum
{
    SWEEP_CONTI = 0,
    SWEEP_SINGLE,
    SWEEP_IDLE
} SWEEPCTRL;
typedef enum
{
    SA_ON = 0,
    SA_OFF
} SWITCHCTRL;

#define BSA_MANA_SHM_KEY 5500
//steve,0524
typedef struct
{
    quint32 appexit;

}BSA_RUN_SYNC,*PBSA_RUN_SYNC;*/

#include "sa_user_variable.h"

qint32 SA_init_shared_memory(user_variable *globalUserVariable);
qint32 SA_Check_InitializeSharedMemory_fromGUI(void);
qint32 SA_Set_config_flag(quint32 modelist, quint32 changelist);



#endif // SHARED_MEMORY

#endif
