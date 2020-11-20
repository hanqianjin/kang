/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              Pm_User_Variable
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              Roc
 **Created date:            2019.12.4
 **Descriptions:            PM Universal variable and function
 **
 *****************************************************************/
#ifndef PM_USER_VARIABLE_H
#define PM_USER_VARIABLE_H

#ifdef __GNUC__
#define VARIABLE_IS_NOT_USED __attribute__ ((unused))
#else
#define VARIABLE_IS_NOT_USED
#endif

#include <QObject>
#include "pm_define.h"
#include "gugedial_define.h"
#include "pm_file_user_variable.h"
//#include "user_system.h"

//Roc for Channel standard load
typedef struct
{
    qreal Min;
    qreal Max;
}__PM_Range__;

typedef struct
{
    __PM_Range__ Up;
    __PM_Range__ Down;
}__PM_Standard__;

class Pm_User_Variable : public QObject {
public:
    explicit Pm_User_Variable(QObject *parent = 0);
    ~Pm_User_Variable();

// function define
public:
    // set Universal variable default val, Albert 12/12
    void InitVariableDefaultVal();

    // 0 아닌 값의 위치를 끝에서 부터 찾기 Function
    qint32 notZeroPositionFindFunc(QString strGab);

    //!Albert added, date time dialog
    qint32  freqUnitFindProc(qreal _freq);   // Unit  (GHz, MHz, kHz, Hz)

    qint32 adjustFreqByCer(void);
    qint32 adjustFreqBySpan(qreal freq);
    qint32 adjustFreqByStart(void);
    qint32 adjustFreqByStop(void);

    qreal dbmToVoltCalculatorAndDisplayFunc(char *label, qreal _level, bool bDataByUnitIndex = false);
    qreal dbmToWattsCalculatorAndDisplayFunc(char *label, qreal _level, bool bDataByUnitIndex = false);
    void Delta_dbmToVoltCalculatorAndDisplayFunc(char *label, qreal _level);
    void Delta_dbmToWattsCalculatorAndDisplayFunc(char *label, qreal _level);
    qreal wattsToDbmCalculatorFunc(qreal _watts);
    qreal voltToDbmCalculatorFunc(qreal _volt);

     qreal adjustSpanBySpan(qreal freq);
//    qreal adjustSpanToSmall(qreal freq);

public:
    void getBandInfo(qint32 STDIndex);
    qint32 CalculateChannelNum();
    void adjustCHStandarByCerFreq(qreal freq);
    qreal adjustFreqByCHStandar();
    qreal adjustFreqByCHNum(qint32 index);
    bool IsFreqInCurChStd();

private:
    void analysisData(QString str);
private :
    qreal m_specFreqMin[2];
    qreal m_specFreqMax[2];
    qint32 m_nUnitIndex;

public:
    qint32 m_nPowerSensorFlg; //功率探头类型
    QString m_strPowerSensorModle;
    QString m_strPowerSensorSN;
    QString m_strPowerSensorFW;
    QString m_strPowerSensorType;


public:
     qreal gReadMeterDataSleepTime;//读取仪表数据时间间隔

    _PM_FILE_SAVE_LOAD_VARIABLE_ gMeterParam;//仪表内参数

    qint32      gMenu;
    qint32      entryInputMode;

    quint32     m_nMinSpan;
    quint32     m_nHalfMinSpan;

    qint32      KeyNumber;

    QVector <QString> *gCHName;
    QVector < __PM_Standard__> *gCHStandard;
    QVector < __PM_Standard__> *gFreqStandard;

    qint32 gLocal;

    qint32  startMode;
    qint32  gfileType;
    qint32  linkMode;
    qint32  gLinkfileType;
    bool    gRefreshAllParam;
    bool    gSuspendDrawFlag;
};


#endif // USER_VARIABLE_H
