/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              RtSa_User_Variable
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              Albert
 **Created date:            2018/12/12
 **Descriptions:            RTSA Universal variable and function
 **
 *****************************************************************/
#ifndef RTSA_USER_VARIABLE_H
#define RTSA_USER_VARIABLE_H

#include <QObject>
#include "rtsa_define.h"
#include "rtsa_file_user_variable.h"
//#include "user_system.h"

//Albert for Channel standard load
typedef struct
{
    qreal Min;
    qreal Max;
}__RTSA_Range__;
typedef struct
{
    __RTSA_Range__ Up;
    __RTSA_Range__ Down;
}__RTSA_Standard__;


class RtSa_User_Variable : public QObject {
public:
    explicit RtSa_User_Variable(QObject *parent = 0);
    ~RtSa_User_Variable();

// function define
public:
    // set Universal variable default val, Albert 12/12
    void InitVariableDefaultVal();


//    void set_freq(qreal Freq) { gCenterFreq = Freq;}
    // 0 아닌 값의 위치를 끝에서 부터 찾기 Function
    qint32 notZeroPositionFindFunc(QString strGab);

    // 설정된 값의 소숫점 뒷자리 표기법 Function (주파수)
//    QString freqDotNumberDisplayFormatFixFunc(qreal freqVal, int unitNo, int numberLen);
//    QString timeDotNumberDisplayFormatFixFunc(qreal _timeVal, int unitNo, int numberLen);

//    void  createInputDialogMakeFunc(QWidget *_widget, QString inputTitle, int entryNo);
//    void  createInputAmptdDialogMakeFunc(QWidget *_widget, QString inputTitle, int entryNo);

    //!Albert added, date time dialog
//    void  createDateTimeDialogMakeFunc(QWidget *_widget);
//    void  createLanDialogMakeFunc(QWidget *_widget);
//    void  createGpsDialogMakeFunc(QWidget *_widget);
//    void  createSelfTestDialogMakeFunc(QWidget *_widget);
//    void  createVirtualkeyboardDialogMakeFunc(QWidget *_widget, uint filetype);
    qint32  freqUnitFindProc(qreal _freq);   // Unit  (GHz, MHz, kHz, Hz)

    //Tony 0911
//    qint32  timeUnitFindProc(qreal _time);
//    qint32 spanSettingCompareProcess(qreal freq);
    void stepFreqCalculatorFunc(void);    //   Step Freq.

    //added by Steve,0228
    qint32 adjustFreqByCer(void);
    qint32 adjustFreqBySpan(qreal freq);
    qint32 adjustFreqByStart(void);
    qint32 adjustFreqByStop(void);
    qint32 converFreqToShm(void);
//    qint32 convertBwToShm(void);

    //Albert 19/01/23
//    void converShmToGlobalVariable(void);

//    void dbmToWattsCalculatorAndDisplayFunc(char *label, qreal _level);
//    void dbmToVoltCalculatorAndDisplayFunc(char *label, qreal _level);
//    void charEmptySplitWorkerFunc(char *label);
    qreal wattsToDbmCalculatorFunc(qreal _watts);
    qreal voltToDbmCalculatorFunc(qreal _volt);

    // Marker 설정 초기화
//    void markerSettingInitFunc(void);
//    void gridAxisCalculatorFunc(void);  // Grid Display (Maker Display에 영향을 받음)
//    void centerFreqSettingFunc(void);   // CenterFreq의 Span 계산 Function

//    void markerEditInNputMarkerPosCalculatorFunc(qreal freq, int inputType);
//    void markerPositionReCalculatorFunc(void);

//    void checkRbwWithStart70MHz(void);       // Start <= 70 MHz 이하일 때, RBW는 30 kHz 이하만 되게 설정함
//    void checkRbwVbwBySpanFunc(void);   // Span에 의해  RBW 변하는 것 반영, RBW에 의해 VBW 값 변하는 것 적용

//    void checkVbwUnderRbw(void);
//    qint32 searchIndexSpanRbwVbwAutoGabFunc(qreal span);
//    qint32 searchIndexSpanRbwVbwManTableFunc(qreal span);
//    quint32 searchIndexRbwVbwMaxFunc(qint32 type, qint32 pos);
//    qint32 searchIndexRbwVbwManValidityFunc(qint32 type, qint32 pos, quint32 bw);
//    qint32 RbwVbwCompare(const void *a, const void *b);
//    bool screenCaptureFunc(void);
//    void saveFilenameAssignFunc(quint32 btnType, QString title);

//    void sharedMemoryVariableAssignFunc(void);
    //Tony 0906
    qreal adjustSpanBySpan(qreal freq);
    //Tony 0906
   quint32 adjustRbwBySpan(qreal freq);
    //Tony 0910
    qreal adjustSpanToSmall(qreal freq);


    //*******************Johnson 0802**************************
//    void setVariable(_RTSA_FILE_SAVE_LOAD_VARIABLE_ *pVariable,uint workMode = RTSA_SPAN_MODE);
//    bool loadVariable(_RTSA_FILE_SAVE_LOAD_VARIABLE_ *pVariable,uint workMode = RTSA_SPAN_MODE);
//    bool saveVariable(_RTSA_FILE_SAVE_LOAD_VARIABLE_ *pVariable,uint workMode = RTSA_SPAN_MODE);
//    void fileSaveLoadParaToglobalUserVariable(_RTSA_FILE_SAVE_LOAD_VARIABLE_ *pVariable);
//    void globalUserVariableTofileSaveLoadPara(_RTSA_FILE_SAVE_LOAD_VARIABLE_ *pVariable);
    //*********************************************************

    //Albert 0315
public:
    void getBandInfo(qint32 STDIndex);
    qint32 CalculateChannelNum();
    void adjustCHStandarByCerFreq(qreal freq);
    qreal adjustFreqByCHStandar();
    qreal adjustFreqByCHNum(qint32 index);
    bool IsFreqInCurChStd();

    //Albert 19/04/23
//    void DpxDataRefresh(void *pAddr);
    void openDpxDevice();
    void closeDpxDevice();

private:
    void analysisData(QString str);
public:
//    qint32      gPeakTrack;
    // 격자
//    qint32      gridXPos[11];    // 0~10, 11개
//    qint32      gridYPos[11];
//    qint32      gSharedMemoryInit;
    //added by Steve,used as the flag of inputdialog close style
//    qint32      inputCloseStyle;//0 by *,means the parent do nothing;1 will do
    //0713 steve
//    qint32      gsweepAuto;
    qreal       gautoMintimems;
//    qreal       gmanSettimems;
//    qreal       gfirsingletimems;
    //0725
//    quint32     ganamode;

    qint32      gMenu;
//    qint32      blRefresh;
    qint32      entryInputMode;
    qint32      gMeasurement;
//    qint32      gDemodulationType;
    qint32      gSweepTracePoint; // Set Graph Sweep Point

//    quint32     gTracePoint;
//    qreal       gTraceStepSize;
    qreal  gStartFreq; 	// Hz Unit
    qreal  gStopFreq; 	// Hz Unit
    qreal  gCenterFreq; 	// Hz Unit
    qreal  gCFFreq;   	// Hz Unit
    qreal  gSpanFreq; 	// Hz Unit
    qreal  gStepFreq;    // Hz  Unit
    quint32     gSpanMode;    //[0] Normal [1] Full Span  [2] Zero Span
    qreal       gfreqOffset;

    qreal       gRefLevel;     //무조건 dBm으로 저장함.
    qreal       gRefOffset;
    qreal       gScaleDiv;
    qint32      gAmptdUnit;

    //Johnson Add
    quint32     gAtten;    //[0]Auto    [1] Manul
    quint32     gPreamp;   // [0] Off  [1] O
//    quint32     gOverlap;   // [0] Off  [1] O

    //Johnson 0710
//    qreal  totalCount1,totalCount2,totalCount3;//Johnson 0709 used to Record the total time

    //added by Steve
//    quint32     gVbwtoRbw;
//    quint32     gAutoVbwtoRbw;
    //by Steve,0301
    quint32     gspanChangebyFreq;//1 means span changed when set freq such as start/stop/cer
    //by Steve,0302
    quint32     gbitsspan;
    quint32     gbithalfsspan;
    quint32     grbwChangedbyFreq;
    //added by Steve,0307
//    quint32     inputDialogOpenflag;
//    quint32     amptDialogOpenflag;

    //Tony 0904
    quint32     gAutoPersistenceTime;   //Persistence Time //Toggle Tony 0903
    quint32     gAutoAcqTime;   //gAcqTime Toggle //Tony 0903
    quint32     gMaskType;  //gMaskType Toggle //Tony 0904
//    quint32     gMarkerCount;  //gMarkerCount Toggle //Tony 0904

    //   quint32         ;

    //Tony 0905
    quint32     gFTTWindows;//Tony 0905
    qreal       gAcqTime;//Tony 0905
    qreal       gPersistenceTime;//Tony 0905
    qreal       gSleepTime;//Tony 0912
    quint32     gHighestDensity; //Tony 0912
    quint32     gLowestDensity; //Tony 0912
    float      gCurve; //Tony 0912

    quint32     gAutoAttenTrack;    // Tony 1105

    quint32     gAutoRbw;    // RBW Toggle 정보
    quint32     gAutoVbw;   // VBW Toggle 정보
//    quint32     gAutoSweepTime;//Johnson 0718
    qreal  gRbw;             // RBW 설정 값  Tony 0911
    qint32      gRbwIndex;             // RBWINDEX  //Tony 0906
    qint32      gRbwGrade;        //Rbw grade //Tony 0907

    quint32     gVbw;             // VBW 설정 값
    quint32     gDetectorMode;        // [0] Normal  [1] Peak [2] Sample  [3] Neg Peak  [4] Avg
    quint32     gSweepType;  // Sweep Type   CONT/Single/Sweep Off
//    qreal       gSweepTime;

    qreal       gAttenValue; //Johnson Add /Auto Atten
//    quint32     gAttenSelect;   // [0] 0  [1] 5   [2] 10    [3] 15   [4] 20  [5] 25   [6] 30
//    quint32     gExtTrigger;  // [0] Off  [1] On
    quint32     gTriggerMode;  // [0] FreeRun  [1] Rise  [2] Fall  [3] Delay
    quint32     gTriggerVideoSlope;  // [0] FreeRun  [1] Rise  [2] Fall  [3] Delay
    quint32     gTriggerExternSlope;  // [0] FreeRun  [1] Rise  [2] Fall  [3] Delay
    quint32     gTriggerRFBurstSlope;  // [0] FreeRun  [1] Rise  [2] Fall  [3] Delay
    quint32     gTriggerSlope;  // [0] FreeRun  [1] Rise  [2] Fall  [3] Delay
    qreal       gVideoTrigLevel;
    qreal       gExternTrigLevel;
    qreal       gRFBurstTrigLevel;
    bool        gVideoTrigDelayStatus;
    bool        gExternTrigDelayStatus;
    bool        gRFBurstTrigDelayStatus;
    bool        gPeriodTrigDelayStatus;
    qreal       gVideoTrigDelay;
    qreal       gExternTrigDelay;
    qreal       gRFBurstTrigDelay;
    qreal       gPeriodTrigDelay;
    qreal       gPeriodTrigTime;
    quint32     gVideoHoldOff;
    quint32     gRFBurstHoldOff;
    quint32     gExternHoldOff;
    quint32     gFMTHoldOff;

//    qreal       gZeroSpanTime;    // Set Zero Span Measure Time
//    quint32     gZeroSpanMode;    // [0] Amplitude    [1] Frequency   [2] Phase
//    quint32     gImageRejection;  // [0] Off  [1] On

    quint32*     gDpxData;//Johnson 0726
//    qreal       gOriginalMeasureVal[RTSA_NUM_SWEEP_POINT];  // App로 부터 공유한 Measure Val
    //   quint32 gOriginalDPXdata[BIT_DPXSIZE];  //Tony 1207 DPX data cache
    //added by Steve,0403
//    qreal       gBitTraceAverage[RTSA_NUM_TRACE][RTSA_NUM_SWEEP_POINT];


//    qreal       gTraceMeasureVal[RTSA_NUM_TRACE][RTSA_NUM_SWEEP_POINT];   // Trace별로 할당
//    qreal       gTrace1AvgArray[RTSA_TR_AVERAGE][RTSA_NUM_SWEEP_POINT];//attention:added by Steve,this alor is wrong 20180223
//    qreal       gTrace2AvgArray[RTSA_TR_AVERAGE][RTSA_NUM_SWEEP_POINT];
//    qreal       gTrace3AvgArray[RTSA_TR_AVERAGE][RTSA_NUM_SWEEP_POINT];

//    qint32      gSpanStepPos;    // Span Up, Down 버튼의 위치
    qreal  gLastSpanFreq; // Last Span Freq 저장
//    qint32      gZeroSpanAction;    // Zero Span Flag

//    qint32      gVolume; //Albert 1108s
    qint32      gDisplayMode; //Albert 1126

    // Power Sensor
    qreal  gPowersensorFreq;
    qreal       gPowersensorExtOffset;
//    bool        bShiftKeyPressed;//false:number key;  true:application key  Johnson 0611
    qint32      KeyNumber;//Johnson 0611

    //Albert 19/03/15
    qint32 gChannelNum;
    qreal gChannelStep;
    qreal RefreshTime;
    qint32 gCHIndex;
    qint32 gTecIndex;
    QVector <QString> *gCHName;
    QVector < __RTSA_Standard__> *gCHStandard;
    QVector < __RTSA_Standard__> *gFreqStandard;
    qint32 gCommuDirection;
    qint32 gLocal;
    qreal   gdpxApmtMin;
    qreal   gdpxAmptZoom;
    quint32 DpxHandle;
    bool gDpxOpenFlag;
    qint32  gFmtData[RTSA_NUM_SWEEP_POINT];
    qint32  startMode;
//    qint32  startPreset;
    qint32  gfmtType;
    qint32  gfileType;
    bool    gRefreshAllParam;
    bool    gSuspendDrawFlag;
    qint32  gFmtTriggerCriterion;
};


#if 0    // 여러 Class에서 호출 시 Multi defined Error가 발생하여 Main.h에서 초기화 함.
qreal RtSa_User_Variable::gStartFreq = 100000;
qreal RtSa_User_Variable::gStopFreq = 3000000000LL;
qreal RtSa_User_Variable::gCenterFreq = 1500050000;
qreal RtSa_User_Variable::gSpanFreq = 2999900000LL;
#endif

//extern RtSa_User_Variable MainUserVariable;


#endif // USER_VARIABLE_H
