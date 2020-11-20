/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              Pm_Pm_Interface
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              Roc
 **Created date:            2019/10/15
 **Descriptions:            PM all set/get SCPI function
 **
 *****************************************************************/

#ifndef PM_INTERFACE_H
#define PM_INTERFACE_H

#include <QObject>
#include "bitgaugedialview.h"
#include "rect_define.h"
#include <QMutex>
#include <QRegExp>
#include <qmath.h>
#include "pm_file_user_variable.h"
#include "pm_communication.h"
#include <QMap>

class BitPm_Interface : public QObject
{
    Q_OBJECT
public:
    explicit BitPm_Interface(QObject *parent = 0);
    ~BitPm_Interface();
private:
    QMutex _mutex;

public://SCPI
    //频率 Frequency
    void setCenterFreq(qulonglong freq);
    qulonglong getCenterFreq();

    void setStartFreq(qulonglong freq);
    qulonglong getStartFreq();

    void setStopFreq(qulonglong freq);
    qulonglong getStopFreq();

    void setStepFreq(qulonglong freq);
    qulonglong getStepFreq();

    void setSpan(qulonglong freq);
    qulonglong getSpan();

//    void setSpanUp(qint32 nlSpanUp);
//    qint32 getSpanUp();

//    void setSpanDown(qint32 nlSpanDown);
//    qint32 getSpanDown();

    void setSpanType(qint32 index);
    qint32 getSpanType();

    void setCHStandard(qint32 index);
    qint32 getCHStandard();

    void setBandIndex(qint32 bandIndex);
    qint32 getBandIndex();

    void setChannelNumber(qint32 number);
    qint32 getChannelNumber();

    void setCommuDirection(qint32 direction);
    qint32 getCommuDirection();

    void setOffset(bool isOffset);
    bool IsOffset();

    void setFreqOffset(qlonglong freq);
    qlonglong getFreqOffset();

//    void setFreqOffsetSize(qulonglong freq);
//    qulonglong getFreqOffsetSize();

    //幅度 Amplitude
    void setAmptMax(qreal ampMax);
    qreal getAmptMax();

    void setAmptMin(qreal ampMin);
    qreal getAmptMin();

    void setAmptOffset(qreal ampOffset);
    qreal getAmptOffset();

    void setAmptUnit(qint32 unitIndex);
    qint32 getAmptUint();

    void setAutoScale();

    void setAmptForwardRelative(qint32 IsAmptForwardRelative);
    qint32 IsAmptForwardRelative();

    void setAmptForwardRelativeData(qreal fAmptForwardRelative);
    qreal getAmptForwardRelativeData();

    void setForwardRelativeCurFlg(bool bRead);
    bool getForwardRelativeCurFlg();

    void setAmptReverseRelative(qint32 IsAmptReverseRelative);
    qint32 IsAmptReverseRelative();

    void setAmptReverseRelativeData(qreal fAmptReverseRelative);
    qreal getAmptReverseRelativeData();

    void setReverseRelativeCurFlg(bool bRead);
    bool getReverseRelativeCurFlg();

    //扫描 Sweep
    void setSweepContinous(qint32 nContinous); // [0] means single, [1] means cont;
    bool IsSweepContinous();

    void setSweepTime(quint32 nTime);
    quint8 getSweepTime();

    void setDutyCycle(qreal fDutyCycle);
    qreal getDutyCycle();

    void setMeasureOffset(qreal fOffset);
    qreal getMeasureOffset();
    //average
    void setAverageAcq(qint32 index);
    qint32 IsAcqType();

    void setRunningAverage(bool bIsAverageFlg);
    bool IsRunningAverage();

    void setAveragePoint(qint32 averagePoint);
    qint32 getAveragePoint();

    void setMaxHold(bool isMaxHold);
    bool IsMaxHold();

    //Zero/Cal
    void setZero(bool isZero);
    bool IsZero();

    void setForwardZero(qreal fZeroBase);
    qreal getForwardZero();
    void setReverseZero(qreal fZeroBase);
    qreal getReverseZero();

    void setCalCenterFreqMHz(quint16 llFreq);
    qint16 getCalCenterFreqMHz();

    void setCalArray(quint16 arrayNo);
    qint16 getCalArray();

    void setCalSelectType(qint8 nSelectType);
    qint8 getCalSelectType();

    // 极限线 Limit
    void setLimit(bool isLimt);
    qint32 IsLimit();

    void setForwardUpperLimt(qreal forwardUpperLimt);
    qreal getForwardUpperLimt();

    void setForwardLowerLimt(qreal forwardLowerLimt);
    qreal getForwardLowerLimt();

    void setReverseUpperLimt(qreal reverseUpperLimt);
    qreal getReverseUpperLimt();

    void setReverseLowerLimt(qreal reverseLowerLimt);
    qreal getReverseLowerLimt();

    void setLimtVidoBW(qint32 index);
    qint32 getLimtVidoBW();

    void setCCDF(qreal ccdf);
    qint32 getCCDF();

    //显示 Display
    void setForwardDisplay(qint32 mDisMode);
    qint32 getForwardDisplay();
    void setReverseDisplay(qint32 mDisMode);
    qint32 getReverseDisplay();
    void setSummaryDisplay();
    qint32 getSummaryDisplay();

    void autoFindSensor(QString strComFlg);

    void setPowerSensorFlg(qint32 mSensorFlg);
    qint32 getPowerSensorFlg();

    void setSensorModle(QString strModle);
    QString getSensorModle();
    void setSensorSN(QString strSN);
    QString getSensorSN();
    void setSensorType(QString strType);
    QString getSensorType();
    void setSensorFW(QString strFW);
    QString getSensorFW();

    //调整函数
public:
    //频率 Frequency
    QString getFreqAdjustStr(qreal freq,qint32 DecPrecision = 12);
    QString getFreqMHzAdjustStr(qint32  nFreq,qint32 DecPrecision = 12);
    quint16 getFreqAdjustMHz(qulonglong  freq);
    void adjustFreqByCal(qulonglong freq);
    qint32 freqUnitFindProc(qreal freq);
    qreal freqBaseFindProc(qreal freq);
    qint32 timeUnitFindProc(qreal time);
    QString getFreqStr(qint32 freqID);
    QString dBmTransformToQstring(qint32 nUnitIndex,qreal value);

    void cmd_GetSensorInventoryData();
    void cmd_GetSensorControlData();
    void cmd_GetSensorPower(qint32 nContinous);
    void cmd_GetSensorCalibrationData();
    void cmd_setSensorCalibrationData();

    void setDisplayMode(qint32 mDisMode);
    qint32 getDisplayMode();

//    void setSensorForward(qint32 isForward);
//    qint32 IsSensorForward();

//    void setSensorRelative(qint32 isReverse);
//    qint32 IsSensorRelative();

private:
    void setMeasureModle(quint8 nModle);
    quint8 getMeasureModle();

    void cmd_StopSensorContinousP();
    //频率 Frequency
    void adjustSpanFreq(qreal freq);

    //幅度 Amplitude 
    void ChangeOtherUnitTodBm(qreal refLevel);
    qreal ChangedBmToOherUnit();

    void setSleepTime(qreal sleepTime);

public:
    // all bitview initial to bitpm class
    void InitBitView(QWidget* widget);
    void setGobalVariable(Pm_User_Variable* globalVariable);

    //set zoom flag
    void setZoomFlag(bool isZoomIn);
    //set drag flag
    void setDragFlag(bool dragFlag);
    bool getDragFlag();

    void setZoomIn();
    void setZoomOut();

    void setShiftKeyEnable(bool isEnable);
    bool isShiftKeyEnable();

    void changeSize(qint32 width, qint32 height);

    qreal getMaxDialData();
    qreal getMinDialData();

    qreal* getCalAmptArrayData();
    void setCalAmptData(qint32 nIndex,qreal fData);
    void setCalCmdData(qint32 nIndex,qreal fData);
    qreal getCalAmptData(qint32 nIndex);
    void setCalAmptNo(qint32 nRow);
    qint32 getCalAmptNo();

    // PM draw all pixmap. trace,limit,marker etc.
    void Draw();
    void DrawFlag(bool isSuspend);
    bool getDrawFlag();
    QString getAdjustTimeStr(qreal time);

    void setSystemDisplay(qint32 sysDisplay);//0 -- indoor 1 -- outdoor 2 -- night

    qint32 getSystemDisplay();//0 -- indoor 1 -- outdoor 2 -- night
private:
    void updateGeneralDataToBitview(qint32 datatype);

    void ReDrawLeftInfo();
    void showBitViewBottomMsg(qint32 bottomDisplay);

    void setCurBitView(qint32 index);

    void saveDisplayParam(qint32 display);
    void loadDisplayParam(qint32 display);

    //set display language
    void setLanguage(qint32 language);
    qint32 getLanguage();


public:    //save/load cond file
    bool sendConnectCommand();
    //get GlobaluserParam
    Pm_User_Variable* getGlobalUserVariable();
    // 0 means default.cond 1 means last.cond 2 means user.cond
    void PltCurAnaMode(qint32 imod);
    qint32 PltSaveConditions(qint32 itype);
    qint32 PltLoadConditions(qint32 itype);
    qint32 PltSavePres(qint32 itype);

    void initDefaultParam();
    void initStateParam(qint32 nSensorType);
    void setStateParam(qint32 nSensorType);
    qint32 saveState(QString fileName);
    qint32 loadState(QString fileName);
    qint32 PltSaveLinkFlg(qint32 itype);
    void PltCurLinkMode(qint32 imod);

    //by Roc 2019.10.17
    qint32 saveLinkState();
    qint32 loadLinkState();

    qint32 savePresState();
    qint32 loadPresState();

    void initFileType(qint32 fileType);
    void parseFile(QString fileName);

signals:
    void ZeroDlgSleep(quint32 nTime);
    void ZeroDlgClose();

    void ZeroDlgShow();
    void BitViewChanged(quint32 index);
    void ParentFocus();

    //use info signal to redraw info display
    void RedrawInfoShow(qint32 infoID);
    void setThreadContinous(qint32 nContinous);

    void finishCmd();
    void finishCal();
    void setUnitSingle(qint32 nUnitIndex);
public slots:
    void analysisCommPort(qint32 nAddOrRemove,QString strComFlg = "");
    void setcurrentview(quint32 index);
    void changeBitViewSize(bool isDoubleClicked);

    void StopSendPower();
    void anaSystemInfo(QByteArray arrayData);
    void anaAmptCal(QByteArray arrayData);

public: //做虚函数
    void setCurrentMode(quint32 mode);
    quint32 getCurrentMode();

    void SetLocalPmMode(qint32 mode);
    qint32 GetLocalPmMode();

    void ChangeLcdStateWithNoSig(qint32 ilock);
    qint32 GetLcdState();

public:
    _PM_SENSOR_DATA m_curSensorData;

    Pm_Communication *m_pPmComm;
    BitGaugeDialView* m_BitViewGauageDial;

private:
    Pm_User_Variable* globalUserVariable; //软件数据 配置
    _PM_FILE_SAVE_LOAD_VARIABLE_ m_sensorStateParam[2];//软件保存参数

private:
    QMap<QString,bool> m_mapComm;
    qint32 m_viewbottomdisplay;
    qint32 m_viewtopdisplay;

    qint32 nCurWindowIndex;//当前视图索引

    qint32 wintotalnum;
    qint32 mWidth;//缩放宽度
    qint32 mHeight;//缩放高度

    qint32 m_nCalAmptRow;
    QRegExp rx;
    bool  mIsZoomIn;
    bool  mDragFlag;

    bool  mSingleFinished;
    bool mIsShiftKeyEnable;

    bool mIsCurBitViewSizeChange;
    qulonglong mFileType;

    QString recvSovket;  //Socket 数据接收
private:
    qreal m_fV90AmptCalData[PM_V90_CAL_AMPT];
    qreal m_fV90WriteCalData[PM_V90_CAL_AMPT];

private:
    bool m_bReadForwardBase; //是否读取Forward实时数据
    bool m_bReadReverseBase;//是否读取Reverse实时数据

    bool bGetDataFromScpi; //是否实时读取SCPI数据
    QString m_strCommName;
public:
    qint32 pSocketLinkStatus; //socket Link Flg
    QString m_comNowRuning;
};

#endif // PM_INTERFACE_H
