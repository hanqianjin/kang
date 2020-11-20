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

#ifdef __GNUC__
#define VARIABLE_IS_NOT_USED __attribute__ ((unused))
#else
#define VARIABLE_IS_NOT_USED
#endif

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

struct socketCmdAndRecvInfo
{
        QString strCmd;
        QString strRecvCmd;
        qreal* arrayRecv;
};
Q_DECLARE_METATYPE(socketCmdAndRecvInfo);

class RtSa_User_Variable : public QObject {
public:
    explicit RtSa_User_Variable(QObject *parent = 0);
    ~RtSa_User_Variable();

// function define
public:
    // set Universal variable default val, Albert 12/12
    void InitVariableDefaultVal();

    // 0 아닌 값의 위치를 끝에서 부터 찾기 Function
    qint32 notZeroPositionFindFunc(QString strGab);

    //!Albert added, date time dialog
    qint32  freqUnitFindProc(qreal _freq);   // Unit  (GHz, MHz, kHz, Hz)

    void stepFreqCalculatorFunc(void);    //   Step Freq.

    //added by Steve,0228
    qint32 adjustFreqByCer(void);
    qint32 adjustFreqBySpan(qreal freq);
    qint32 adjustFreqByStart(void);
    qint32 adjustFreqByStop(void);

    qreal wattsToDbmCalculatorFunc(qreal _watts);
    qreal voltToDbmCalculatorFunc(qreal _volt);

    void checkRbwVbwBySpanFunc(void);   // Span에 의해  RBW 변하는 것 반영, RBW에 의해 VBW 값 변하는 것 적용

    void checkVbwUnderRbw(void);
    qint32 searchIndexSpanRbwVbwAutoGabFunc(qreal span);
    qint32 searchIndexSpanRbwVbwManTableFunc(qreal span);
    quint32 searchIndexRbwVbwMaxFunc(qint32 type, qint32 pos);
    qint32 searchIndexRbwVbwManValidityFunc(qint32 type, qint32 pos, quint32 bw);
    //Tony 0906
    qreal adjustSpanBySpan(qreal freq);
    //Tony 0906
   quint32 adjustRbwBySpan(qreal freq);
    //Tony 0910
    qreal adjustSpanToSmall(qreal freq);


public:
    void getBandInfo(qint32 STDIndex);
    qint32 CalculateChannelNum();
    void adjustCHStandarByCerFreq(qreal freq);
    qreal adjustFreqByCHStandar();
    qreal adjustFreqByCHNum(qint32 index);
    bool IsFreqInCurChStd();

private:
    void analysisData(QString str);
public:

       qreal gReadMeterDataSleepTime;//读取仪表数据时间间隔

     _RTSA_FILE_SAVE_LOAD_VARIABLE_ gMeterParam;//仪表内参数

     quint32     gSpanMode;    //[0] Normal [1] Full Span  [2] Zero Span
     qint32      gRbwGrade;        //Rbw grade //Tony 0907


    qreal       gautoMintimems;

    qint32      gMenu;
    qint32      entryInputMode;
    qint32      gSweepTracePoint; // Set Graph Sweep Point


    quint32     gspanChangebyFreq;//1 means span changed when set freq such as start/stop/cer
    //by Steve,0302
    quint32     gbitsspan;
    quint32     gbithalfsspan;
    quint32     grbwChangedbyFreq;
    //Tony 0904
    quint32     gAutoPersistenceTime;   //Persistence Time //Toggle Tony 0903

    quint32     gMaskType;  //gMaskType Toggle //Tony 0904


    qreal       gPersistenceTime;//Tony 0905
    quint32     gHighestDensity; //Tony 0912
    quint32     gLowestDensity; //Tony 0912
    float      gCurve; //Tony 0912

    quint32     gAutoAttenTrack;    // Tony 1105

    quint32     gAutoVbw;   // VBW Toggle 정보
//    quint32     gAutoSweepTime;//Johnson 0718


    quint32     gVbw;             // VBW 설정 값
    quint32     gDetectorMode;        // [0] Normal  [1] Peak [2] Sample  [3] Neg Peak  [4] Avg


    quint32*     gDpxData;//Johnson 0726
    qreal  gLastSpanFreq; // Last Span Freq 저장

    qreal  gPowersensorFreq;
    qreal       gPowersensorExtOffset;
    qint32      KeyNumber;//Johnson 0611

    //Albert 19/03/15
    qreal RefreshTime;

    QVector <QString> *gCHName;
    QVector < __RTSA_Standard__> *gCHStandard;
    QVector < __RTSA_Standard__> *gFreqStandard;
    qint32 gLocal;
    qreal   gdpxApmtMin;
    qreal   gdpxAmptZoom;
    quint32 DpxHandle;
    bool gDpxOpenFlag;
    qint32  gFmtData[RTSA_NUM_SWEEP_POINT];
    qint32  startMode;
    qint32  gfmtType;
    qint32  gfileType;
       qint32  linkMode;
    qint32  gLinkfileType;
    bool    gRefreshAllParam;
    bool    gSuspendDrawFlag;
    qint32  gFmtTriggerCriterion;

};


#endif // USER_VARIABLE_H
