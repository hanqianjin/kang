/****************************************Copyright (c)****************************************************
**
**                                     INNO Instrument(China) Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                user_variable.h
** Latest Version:           V1.0.0
** Created by:               Johnson
** Created date:             2018/12/13
** Descriptions:             customized class used to manage all variables that are used to save all status
**
*********************************************************************************************************/

#ifndef USER_VARIABLE_H
#define USER_VARIABLE_H

#include <QObject>
#include "define.h"
#include <math.h>
#include <stdio.h>
typedef struct
{
    qreal Min;
    qreal Max;
}__Range__;
typedef struct
{
    __Range__ Up;
    __Range__ Down;
}__Standard__;

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
class user_variable : public QObject
{
public:
    explicit user_variable();
public://***************Related with Paint
    qint32  gridXPos[GRIDX_LENGTH];    // 0~10, 11개
    qint32  gridYPos[GRIDY_LENGTH];
    bool    bSmallCanvas;
    qint32  mDrawWidth;
    qint32  mDrawHeight;
public://***************Related with Shm
    //qint32  gSharedMemoryInit;
    quint32 segmentNum;//decided by start and stop freq

    quint32 startIndex;		 //valid start index
    quint32 stopIndex;		 //valid stop index
    quint32 fftNum;			 //fft calc num
    qreal fftBucketnum;
    qreal singlefftTime;   //single fft num acq time
    qreal loStepHz;		 //lo step
    qreal validRatio;     //efficient

    quint32 seglokeeptime;//seg last part lo keep time
    qreal sumSweeptime;//span sweep time
    qreal firdottimems;
    qreal firBucketimeus;//means us
    quint32 segmentsDataSumNum;//from start to end all points num
    SA_FFT_FIR_COMMON_NUM comNum[19];

    qreal firstper;
    qreal secper;
    qreal spanperstep;
public://***************Related with Measure
    qint32  gOcc;
    //qint32  gDemodulationType;
    qreal   gOccupied_BW;//%
    qreal   gXdB;//dB
    quint64 gChannelBandwidth;    // Channel Power의 Channel BandWidth
    quint64 gChannelSpacing;    // SA_ACP 의 Channel Spacing
    qreal   dPowerValue;//channel power
    qreal   dPowerValue_ACPM,dPowerValue_ACPL,dPowerValue_ACPR;//SA_ACP Power
    qreal   dPowerValue_MultiACPM,dPowerValue_MultiACPFL,dPowerValue_MultiACPL,dPowerValue_MultiACPFR,dPowerValue_MultiACPR;//MultiACP Power
    qreal   dTotalPower;//dBm
    quint64 uOccupiedBW;//Hz
    quint64 uXdBBW;//Hz
    qreal   dPSD;// dBm/Hz

    qreal   dTmpChannelBandwidth;//Record the BW setted by acp and channelpower dialog
    qreal   dTmpChannelSpacing;  //Record the channel spacing setted by acp dialog

    qint32 gSpecEMDisplay; //Display Mode [Abs&Freq],[Ref&Freq],[Integ Power]
    qint32 gSpecEMRefType; //Ref type [Total Pwr Ref][PSD Ref][Spectrum Pk Ref]
    qreal  gSpecEMInteBW;
    qreal  gSpecEMTotalPwrRef;
    qreal  gSpecEMPSDRef;
    qreal  gSpecEMPeakRef;
    __SPEC_EM__ gSpecEMData[SA_SPECEM_FREQ_CNT];
    qint32 gSpecEMViewStatus[SA_SPECEM_FREQ_CNT];
    qint32 gSpecEMSweepIndex;  //one sweep include seven times.
    qint32 gSpecEMTestResult[SA_SPECEM_FREQ_CNT];

    qint32 gSpurEMCurRangeIndex;
    qint32 gSpurEMCurDrawRangeIndex;
    qint32 gSpurEMCurSpurIndex;
    __SPUR_EM__ gSpurEMPara[SPUR_EM_DATE_MAX]; //
    qint32 gSpurEMViewStatus[SA_SPUREM_RANGE_CNT];
    qint32  gSpurEMAveType;
    qint32  gSpurEMReportType;
    qint32 gSpurEMTableMode;
    qint32 gMsFirstFlag;

    __SPUR_POINT__ gSpurEMSpur[SA_SPUREM_RANGE_CNT*SA_SPUREM_SPUR_CNT];
    qint32 gSpurEMSpurCnt[SA_SPUREM_RANGE_CNT];
    qint32 gSpurEMTotalSpurCnt;
    qint32 gMeasureStatus;  //Measure  0 means complete measure and 1 means measuring
    qint32 gMsComplete;
public://***************Related with Sweep
    qint32  gsweepAuto;
    qreal   gautoMintimems;
    qreal   gmanSettimems;
    qreal   gfirsingletimems;
    quint32 ganamode;
    qint32  gcheckswitch;//when 1 means without checking action
    qint32  goldcheckswitch;
    qint32  gSweepTracePoint; // Set Graph Sweep Point
    quint32 gAutoSweepTime;//Johnson 0718
    quint32 gSweepType;  // Sweep Type   SA_CONT/Single/Sweep Off
    qreal   gSweepTime;
    quint32 gTriggerMode;  // [0] FreeRun  [1] Rise  [2] Fall  [3] Delay
#if 0
    quint32 gSweepSpeed;
#endif

    qreal   gDotSweepTime;
    quint32 gAutoDotSweepTime;
    quint32 gFixDotSweepTime;//equal SA_ON ,use the fixed value;equal SA_OFF,use the caculated value

    qreal gTriggerPerTimer; //only Periodic Timer
    qreal gTriggerLevel[TRIGGER_SOURCE_CNT];//except Periodic Timer
    quint32 gTriggerSlope[TRIGGER_SOURCE_CNT];//except Periodic Timer
    qint32 gTriggerDelayStatus[TRIGGER_SOURCE_CNT]; // SA_ON SA_OFF
    qreal gTriggerDelayValue[TRIGGER_SOURCE_CNT];
public://***************Related with Trace
    quint32 gTracePoint;
    qreal   gTraceStepSize;
    qint32  gTraceSelect;   // 선택된 Trace
    qint32  gViewAction[NUM_TRACE];    //Trace - View 선택시에만 동작할 수 있도록 Flag를 줌
    qint32  gTraceType[NUM_TRACE]; // Trace Type 저장
    qint32  gTraceAverage[NUM_TRACE]; // Trace별 Average On/off 적용 여부 저장
    qint32  gAverageCount[NUM_TRACE]; // Trace별 Average Count 설정
    qint32  gAverageNo[NUM_TRACE];//Average number index
    qint32  greAvager[NUM_TRACE];//1 means re average
    quint32 gDetectorMode;        // [0] Max  [1] Min  [2] Sample  [3] Avg - Power  [4] Avg - Voltage
    quint32 gTmpDetectorMode;//Johnson 1128 used to save the DetectorMode when marker noise is changed to SA_ON
    qreal   gOriginalMeasureVal[NUM_SWEEP_POINT];  // App로 부터 공유한 Measure Val
    qreal   gBitTraceAverage[NUM_TRACE][NUM_SWEEP_POINT];//added by Steve,0403
    qreal   gTraceMeasureVal[NUM_TRACE][NUM_SWEEP_POINT];   // Trace별로 할당
    qreal   gTraceViewDate[NUM_TRACE][NUM_SWEEP_POINT];
    qreal   gTraceSpecEMVal[NUM_SWEEP_POINT];
    qint32  gTraceView[NUM_TRACE];
    quint32 uMinMaxHoldReadComplete;
    //Johnson 190621
    qint32  gFsr;
    qreal   gFreqCount;
    qreal   gSignalFreq;
    //Johnson 190705
    qreal   calData;
    //Tony 19-06-11
    qint32 traceSusFlag;//trace view or resume 0--[resume] 1--[suspend]
public://***************Related with Freq/Span
    quint64 gStartFreq; 	// Hz Unit
    quint64 gStopFreq; 	// Hz Unit
    quint64 gCenterFreq; 	// Hz Unit
    quint64 gCFFreq;   	// Hz Unit
    quint64 gSpanFreq; 	// Hz Unit
    qint64  gfreqOffset;
//    quint64 gStepFreq;    // Hz  Unit
    qreal   gStepFreq;    // Hz  Unit
    quint32 gSpanMode;    //[2] Normal [0] Full Span  [1] Zero Span
    quint32 gspanChangebyFreq;//1 means span changed when set freq such as start/stop/cer
    quint32 gbitsspan;
    quint32 gbithalfsspan;
    qreal   gZeroSpanTime;    // Set Zero Span Measure Time
    quint64 gLastSpanFreq; // Last Span Freq 저장
    qint32  gZeroSpanAction;    // Zero Span Flag

    qint32  gFreqReference;    //Tony 05 07
public://***************Related with Amplitude
    qreal   gRefLevel;     //무조건 dBm으로 저장함.
    qreal   gRefOffset;
    qreal   gScaleDiv;
    qint32  gAmptdUnit;
    quint32 gAtten;    //[0]Auto    [1] Manul
    quint32 gPreamp;   // [0] Off  [1] O
    qreal   gAttenValue; //Johnson Add /Auto Atten
    qreal lowLevel,topLevel;//use to caculate limit
    quint32 gAutoAttenTrack;//Auto Atten Track Toggle Johnson 1112

    //Johnson 190410
    qint32 gZeroRestrainAtten;
    qreal gZeroRestrainPhase;
#if 0
public://***************Related with DPX
    //Johnson 0709 used to Record the shut times of every pixel
    qreal   density_Trace1[NUM_SWEEP_POINT][GRID_HEIGHT];
    qreal   density_Trace2[NUM_SWEEP_POINT][GRID_HEIGHT];
    qreal   density_Trace3[NUM_SWEEP_POINT][GRID_HEIGHT];
    qreal   density_Trace4[NUM_SWEEP_POINT][GRID_HEIGHT];
    qreal   density_Trace5[NUM_SWEEP_POINT][GRID_HEIGHT];
    qreal   density_Trace6[NUM_SWEEP_POINT][GRID_HEIGHT];
    quint64 hitCount_Trace1[NUM_SWEEP_POINT][GRID_HEIGHT];
    quint64 hitCount_Trace2[NUM_SWEEP_POINT][GRID_HEIGHT];
    quint64 hitCount_Trace3[NUM_SWEEP_POINT][GRID_HEIGHT];
    quint64 hitCount_Trace4[NUM_SWEEP_POINT][GRID_HEIGHT];
    quint64 hitCount_Trace5[NUM_SWEEP_POINT][GRID_HEIGHT];
    quint64 hitCount_Trace6[NUM_SWEEP_POINT][GRID_HEIGHT];
    quint64 totalCount1;
    quint64 totalCount2;
    quint64 totalCount3;//Johnson 0709 used to Record the total time
    quint64 totalCount4;
    quint64 totalCount5;
    quint64 totalCount6;//Johnson 0709 used to Record the total time
    quint32 gDpxData[DPX_LENGHT];//Johnson 0726
#endif
public://***************Related with Marker
    qint32  gMarkerSelect;      // 선택된 Marker
    qint32  gMarkerView[MARKER_TOTAL_CNT];    // Marker On/Off Flag 저장
    qint32  gMarkerType[MARKER_TOTAL_CNT];    // Marker Type Ref / Delta
    quint64 gMarkerRefFreq[MARKER_TOTAL_CNT];    // 각 Marker Ref Freq
    qint32  gMarkerRefPos[MARKER_TOTAL_CNT];
    quint64 gMarkerDeltaFreq[MARKER_TOTAL_CNT];    // 각 Marker Delta Freq
    qint32  gMarkerDeltaPos[MARKER_TOTAL_CNT];

    qreal gMarkerRefTime[MARKER_TOTAL_CNT];
    qreal gMarkerDeltaTime[MARKER_TOTAL_CNT];

    qint32  gMarkerDisplay;
    qint32  gMarkerNoise[MARKER_TOTAL_CNT];
    qreal   gMarkerNoiseValue[MARKER_TOTAL_CNT];
    qreal   gMarkerRefAmpt[MARKER_TOTAL_CNT];
    qreal   gMarkerDeltaAmpt[MARKER_TOTAL_CNT];
    qreal   gMarkerTmpRefAmpt[MARKER_TOTAL_CNT];
    qreal   gMarkerMarkerTmpRefPos[MARKER_TOTAL_CNT];

    qint32  gMarkerRefDelta;
    quint32 gMarkerFreqCount[MARKER_TOTAL_CNT];
public://***************Related with SA_BW
    qreal   gVbwtoRbw;
    quint32 gAutoVbwtoRbw;
    quint32 grbwChangedbyFreq;
    quint32 gAutoRbw;    // RBW Toggle 정보
    quint32 gAutoVbw;   // VBW Toggle 정보
    quint32 gRbw;             // RBW 설정 값
    quint32 gVbw;             // VBW 설정 값
public://***************Related with peak
    quint32 gPeakTrack;//Peak Track Toggle  Johnson 1112
#if 0
public://***************Related with other(unused)
    qint32  gMenu;

    qreal   gTrace1AvgArray[TR_AVERAGE][NUM_SWEEP_POINT];//attention:added by Steve,this alor is wrong 20180223
    qreal   gTrace2AvgArray[TR_AVERAGE][NUM_SWEEP_POINT];
    qreal   gTrace3AvgArray[TR_AVERAGE][NUM_SWEEP_POINT];
    qreal   gTrace4AvgArray[TR_AVERAGE][NUM_SWEEP_POINT];//attention:added by Steve,this alor is wrong 20180223
    qreal   gTrace5AvgArray[TR_AVERAGE][NUM_SWEEP_POINT];
    qreal   gTrace6AvgArray[TR_AVERAGE][NUM_SWEEP_POINT];

    quint64 gPowersensorFreq;
    qreal   gPowersensorExtOffset;
    quint32 gImageRejection;  // [0] Off  [1] On
#endif
public://***************Related with other
    bool    bShiftKeyPressed;//false:number key;  true:application key  Johnson 0611
    //qint32  KeyNumber;//Johnson 0611
    qint32  PrimaryAction;
    qint32  SecondaryAction;
    quint32 currentMode;
    //quint32 lastMode;//NOT USE

    qint32  startMode;
    qint32  startPreset;
    quint32 gCurrentWorkState;

    bool FullStatus;
    bool pbLeftHideChecked;
    qint32 gDisplayMode; //Tony 190614  [0] indoor [1] outdoor [2]night
public:
    quint32 uIFMode;
#if 0
    quint32 uIFRef;
    quint32 uBrtLevel;
#endif
    qint32 loadFileType;
    quint32 uTmpRbw;
    qint32 gIFOutputSpanModeChange;
//Tony 2019-01-23
public:
    qint32 gChannelNum;
    qint32 gChannelNumStep;
    qreal gChannelStep;

    qreal RefreshTime;
    qint32 gCHIndex;
    qint32 gTecIndex;
    QVector <QString> *gCHName;
    QVector < __Standard__> *gCHStandard;
    QVector < __Standard__> *gFreqStandard;
    qint32 gCommuDirection;

    qint32 gRunMode;//local or remote
    qint32 gLockStatus;//0 unlock   1 lock
    qint32 gIgnoreLimit;//0 -- not use  1 -- ignore the limit for interface
    qint32 gAutoRepeat;//Prevent repetitive setting of parameters
                        //0 -- not use  1 -- Open to remove duplicate settings

/*********Door Control Sweep Interface*************/
public:
    qint32 gDrCtrlSource;
    qint32 gLvlEdgSelect;
    qint32 gLvlEdgMode;
    qint32 gDrCtrlSweepMode;
    qint32 gPrdTrgSynchroSrc;
    qint32 gDrCtrlSwitch;
    qreal  gEdgTrigDely;
    qreal  gEdgTrigDoorWdth;
    qint32 gEdgTrigPrvntStatus;
    qreal  gEdgTrigPrvntTimes;
    qreal gRFBurstTrigLevel;
    qreal  gPrdTrgPeriod;
    qreal  gPrdTrgSrcDelay;
    qint32 gPrdTrigPrvntStatus;
    qreal  gPrdTrigPrvntTimes;
    quint32 gDrCtrlRbw;
    qint32 gGateSweepSpanChange;
    qint32 gGateViewStatus;
    qreal gGateViewStartTime;
public://Action Interface
    void setPrimaryAction(quint32 primaryAction);
    void setSecondaryAction(quint32 secondaryAction);
public:
    // 0 아닌 값의 위치를 끝에서 부터 찾기 Function
    qint32 notZeroPositionFindFunc(QString strGab);

    // 설정된 값의 소숫점 뒷자리 표기법 Function (주파수)
    QString freqDotNumberDisplayFormatFixFunc(qreal freqVal, qint32 unitNo, qint32 numberLen);
    QString timeDotNumberDisplayFormatFixFunc(qreal _timeVal, qint32 unitNo, qint32 numberLen);

    void  createInputDialogMakeFunc(QWidget *_widget, QString inputTitle, qint32 entryNo);
    void  createInputAmptdDialogMakeFunc(QWidget *_widget, QString inputTitle, qint32 entryNo);
    qint32  freqUnitFindProc(quint64 _freq);   // 주파수 Unit 찾기 (GHz, MHz, kHz, Hz)

    qint32 spanSettingCompareProcess(quint64 freq);
    void stepFreqCalculatorFunc(void);    // 설정된 주파수의 Step Freq를 구함.
    //added by Steve,0228
    qint32 adjustFreqByCer(void);
    qint32 adjustFreqBySpan(quint64 freq);
    qint32 adjustFreqByStart(void);
    qint32 adjustFreqByStop(void);
    qint32 converFreqToShm(void);
    qint32 convertBwToShm(void);

    void dbmToWattsCalculatorAndDisplayFunc(char *label, qreal _level);
    void dbmToVoltCalculatorAndDisplayFunc(char *label, qreal _level);
    void Delta_dbmToVoltCalculatorAndDisplayFunc(char *label, qreal _level);
    void Delta_dbmToWattsCalculatorAndDisplayFunc(char *label, qreal _level);
    void charEmptySplitWorkerFunc(char *label);
    qreal wattsToDbmCalculatorFunc(qreal _watts);
    qreal voltToDbmCalculatorFunc(qreal _volt);

    // Marker 설정 초기화
    void markerSettingInitFunc(void);

    void centerFreqSettingFunc(void);   // CenterFreq의 Span 계산 Function
    void markerEditInNputMarkerPosCalculatorFunc(quint64 freq, qint32 inputType);
    void markerEditZeroSpanMarkerPosCalculatorFunc(qreal time, qint32 InputType);

    void markerValueToTime(void);
    void markerValueToFreq(qreal timestep);

    void markerPositionReCalculatorFunc(void);

    void checkRbwWithStart70MHz(void);       // Start <= 70 MHz 이하일 때, RBW는 30 kHz 이하만 되게 설정함
    void checkRbwVbwBySpanFunc(void);   // Span에 의해  RBW 변하는 것 반영, RBW에 의해 VBW 값 변하는 것 적용
    void checkVbwUnderRbw(void);
    qint32 searchIndexSpanRbwVbwAutoGabFunc(quint64 span);
    qint32 searchIndexSpanRbwVbwManTableFunc(quint64 span);
    quint32 searchIndexRbwVbwMaxFunc(qint32 type, qint32 pos);
    qint32 searchIndexRbwVbwManValidityFunc(qint32 type, qint32 pos, quint32 bw);
    static qint32 RbwVbwCompare(const void *a, const void *b);
    bool screenCaptureFunc(void);
    void saveFilenameAssignFunc(quint32 btnType, QString title);

    void sharedMemoryVariableAssignFunc(void);

    void createVirtualkeyboardDialogMakeFunc(QWidget *_widget, uint filetype);
    qreal Round(qreal dSrc,qint32 iBit);

    QString freqValueToQstring(qint64 freq, qint32 precision = -1);
    qint32 freqnotZeroPosition(quint64 freq);
    QString amptTransformToQstring(qint32 unit,qreal value);
    qint32 getTimeUnit(qreal value);
    QString TimeTransformToQstring(qreal value);
#if 0
private:
    quint32 Preamp;			// 0 off, 1 on
    qreal RefLevel;				// +10 ~ -150 dBm
    quint32 AttenIndex;		// 0 0dB, 3 15dB, 0~3

    quint32 SweepOnOff;		// 0 continuous, 1 single, 2 sweep off
    qreal SweepTime;
    quint32 SweepMode;			// 0 slow sweep, 1 fast sweep, 2 rbw 5MHz, 3 zero span, 5 track gen, 7 phase noise, 9 bb sig peak

    qreal ZeroSpanSweepTime;		// milisecond

    quint32 RBWAuto;			// 0 off, 1 auto
    quint32 RBWSet; 			// x10 Hz		50Hz -> 500
    quint32 VBWAuto; 			// 0 off, 1 auto
    quint32 VBWSet; 			// x10 Hz		20Hz -> 200

    quint32 DetectorMode;		// 1 min&max, 2 min, 3 max, 4 average
    quint32 VP_MODE;			// 1 power. 2 voltage, 3 log, 4 bypass

    quint64 StartFreq; 	// Hz
    quint64 StopFreq; 	// Hz

    quint32 SpanMode;			// ?????????????????????
    quint64 CenterFreq; 	// Hz
    quint64 SpanFreq; 	// Hz
#endif


public:
    void getBandInfo(qint32 STDIndex);
    qint32 CalculateChannelNum();
    void adjustCHStandarByCerFreq(qreal freq);
    qreal CalculateFreqByCHStandar();
    qreal CalculateFreqByCHNum(qint32 index);
private:
    void analysisData(QString str);
};

#endif // USER_VARIABLE_H
