#ifndef RTSA_SHARED_MEMORY
#define RTSA_SHARED_MEMORY

#include <pthread.h>
#include <sys/types.h>
#include <qglobal.h>
// shared memory

#define RSA_MANA_SHM_KEY 5501
#define SM_Key_ConfigRsaCtrl	5700
#define RTSA_SM_Key_SweepData	5701
#define RTSA_SM_Key_Sync	5702
#define RTSA_SM_Key_ConfigUpdate	5703
#define SM_CTRL_KEY_START    5704

#define RTSA_SYNC_KEY       5711
#define RTSA_SYNC_KEY_GUI   5712
#define RTSA_SYNC_SWEEP     5713


//steve,0524
#define RTSA_HOME_UI_SHOW_KEY 5550
//0525
#define RSA_VISI_KEY 5503
#define IXT_RTSA_ConfigRsaCtrl                  (0x00000001) //IXT_ConfigSweep
#define IXS_RTSA_CenterFreq							0x00000001
#define IXS_RTSA_SpanFreq							0x00000002
#define IXS_RTSA_StartFreq							0x00000004
#define IXS_RTSA_StopFreq							0x00000008
#define IXS_RTSA_SpanMode							0x00000010
#define IXS_RTSA_TracePoint							0x00000020
#define IXS_RTSA_RBW                                0x00000040
#define IXS_RTSA_RBWAuto							0x00000080
#define IXS_RTSA_AcqTime                            0x00000100
#define IXS_RTSA_PersisTime							0x00000200
#define IXS_RTSA_DetectorMode						0x00000400
#define IXS_RTSA_RefLevel							0x00000800
#define IXS_RTSA_AttenSelect                        0x00001000
#define IXS_RTSA_SweepType							0x00002000
#define IXS_RTSA_ExtTrigger							0x00004000
#define IXS_RTSA_TriggerMode                        0x00008000
#define IXS_RTSA_Preamp                             0x00010000
#define IXS_RTSA_FilterType							0x00020000
#define IXS_RTSA_Refoffset                          0x00040000
#define IXS_RTSA_DPXAmptMin                         0x00080000
#define IXS_RTSA_DPXAmptZoom                        0x00100000
#define IXS_RTSA_FFT_Bucket_Num                     0x00200000
#define IXS_RTSA_Highest_Density                    0x00400000
#define IXS_RTSA_Lowest_Density                     0x00800000
#define IXS_RTSA_Fmt_Data                           0x01000000
#define ISX_RTSA_Curve                              0x02000000
#define IXS_Fmt_Trigger_Criterion                   0x04000000
#define IXS_RTSA_DPX_Probability                    0x08000000
//#define IXS_RTSA_Trigger_Delay                      0x02000000
//#define IXS_RTSA_Trigger_Period                     0x04000000
//#define IXS_RTSA_Trigger_Video_Level                0x08000000
//#define IXS_RTSA_Trigger_RF_Level                   0x10000000

#define ISX_CONGIG_ALL_PARAM                        0x0fffffff


#define IXT_RTSA_ConfigSystem						0x00000004
#define IXT_RTSA_System_Info                         0x00000008

#define IXT_RTSA_MeasureCtrl                     (0x00000002) //IXT_ConfigMeasure
#define IXS_RTSA_Density  0x00000001
#define IXS_RTSA_Spectrum   0x00000002
#define IXS_RTSA_Spectrogram  0x00000004
#define IXS_RTSA_Density_Spectrogram	 0x00000008

#define ISX_MEASURE_ALL_PARAM                        0x0000000f

#define IXT_RTSA_Trigger                             (0x00000004)
#define IXS_RTSA_Trigger_Slope						0x00000001
#define IXS_RTSA_Trigger_Delay						0x00000002
#define IXS_RTSA_Trigger_Period						0x00000004
#define IXS_RTSA_Trigger_Video_Level                0x00000008
#define IXS_RTSA_Trigger_RF_Level					0x00000010
#define IXS_RTSA_Trigger_HoldOff                    0x00000020

#define ISX_TRIGGER_ALL_PARAM                        0x0000003f

typedef struct
{
    quint32 appexit;
}RSA_RUN_SYNC,*PRSA_RUN_SYNC;

typedef struct
{
  qreal  CenterFreq; 	            // Hz
  qreal  SpanFreq; 	            // INDEX {0~14  100M 50M 20M 10M 5M 2M 1M 500K 200K 100K 50K 20K 10K 5K 2K}
  qreal  StartFreq; 	            // Hz
  qreal  StopFreq; 	            // Hz
  quint32 SpanMode;		    // [0]Normal, [1]Full SPAN
  quint32 TracePoint;        // [0]501, [1]1001, [2]2001, [3]3001 (point)
  quint32 RBW; 			    // Hz
  quint32 RBWAuto;		    // [0]Manual, [1]Auto
  quint32 DetectorMode;	    // [0]Max, [1]Min, [2]Sample, [3]Avg-Power, [4]Avg-Voltage
  qreal  RefLevel;				// +10 ~ -150 dBm
  quint32 SweepType;		    // [0]Continuous, [1]Single, [2]Sweep Offk
  quint32 ExtTrigger;		// [0]Off, [1]On
  quint32 TriggerMode;		// [0]Free Run, [1]Rise, [2]Fall, [3]Delay
  quint32 Preamp;
  qreal attenValue;			// [0]Off, [1]On
  quint32 attenAuto;//0 man,1 aut0
  quint32 ListenState;//
  qreal acqtimems;
  quint32 acqtimeword;
  qreal persistimems;
  quint32 persistimeword;
  quint32 flitertype;
  quint32 ischangeRbwitself;//when change rbw by freq,its value is 0,when change rbw by itself,its value is 1
  quint32 uisPreampChangedItself;
  quint32 AttenSelect;	//[0]0, [1]5, [2]10, [3]15, [4]20, [5]25, [6]30 (dB)
  quint32 channelnum;
  qint32 dpxApmtMin;    //DPX bottom value Albert 19/04/12
  qint32 dpxApmtZoom;    //DPX ampt zoom Albert 19/04/12
  qint32 dpxHighestDensity;
  qint32 dpxLowestDensity;
  qint32 fmtData[801];
  quint32 triggerDelay;
  quint32 triggerPeriod;
  float triggerVideoLevel;
  qreal triggerRFBurstLevel;
  quint32 triggerSlope;
  quint32 triggerHoldOffTime;
  float dpxCurve;
  qint32 FmtTriggerCriterion;
//  qint32 fmtData[1602];     // 801 top Y and 801 bottom Y

}_CONFIG_RSA_CTRL; // GUI -> Ctrlapp

typedef struct
{
  quint32 visiableflag;
}BIT_RTSA_VISI,*PBIT_RTSA_VISI;

typedef struct
{
  quint32 top_flag;
  quint32 sweep_flag;
  quint32 measure_flag;
  quint32 trigger_flag;
  quint32 stopFlag;
}_RTSA_CONFIG_UPDATE;

typedef struct
{
  quint32 _TotalNumber;
  //add by Steve
  qreal  _PwrLevel[10000];
  qreal  _Freq[10000];

  //qreal  _PwrLevel[80000];
  //qreal  _Freq[80000];
  quint32 SweepTime;
  quint32* DpxData;//Johnson 0726
}_RTSA_SWEEP_DATA; // Ctrlapp -> GUI
#if 0
typedef struct
{
  qreal  ChannelPwr;
  qreal  ACPR;
  qreal  ACPL;
  qreal  PSLevel;				// powersensor data - powerlevel
}_RTSA_MEASURE_DATA; // Ctrlapp -> GUI
#endif
typedef struct
{
  quint32 SweepUpdate;       //[0]Wait, [1]Update Ok, [2]ChangeParameter
  quint32 BWUpdate;          //BW Changed from ControlApp (Only BW Auto Mode)
  quint32 CtrlAppRunOk;      //ControlApp Alive Message (First RUN)
  quint32 CtrlAppAlive;      //ControlApp Alive Signal, [0]->[1]->[0]-> ��. (��1 second)
  quint32 DeviceMsgUpdate;   //Device Message Update

  quint32 SysparamReflesh;//1 reflesh over  Johnson 0712
}_RTSA_SM_SYNC;	// Ctrlapp -> GUI

typedef struct
{
  quint32 startedflag;//1 means not first start
            //inner use
}_RTSA_START_FLAG;

//typedef struct rtsa_temper_calc
//{
//    quint32 calctop;
//    qreal detatemp;
//}RTSA_TEMP_CALC,*RTSA_PTEMP_CALC;

//Johnson 0712
/*typedef enum
{
    SWEEP_CONTI = 0,
    SWEEP_SINGLE,
    SWEEP_IDLE
} SWEEPCTRL;
typedef enum
{
    ON = 0,
    OFF
} SWITCHCTRL;

*/



qint32 RtSa_init_shared_memory(void);
qint32 RtSa_Check_InitializeSharedMemory_fromGUI(void);
qint32 RtSa_Set_config_flag(quint32 modelist, quint32 changelist);






#endif // SHARED_MEMORY

