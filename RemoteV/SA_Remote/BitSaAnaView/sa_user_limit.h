#ifndef USER_LIMIT
#define USER_LIMIT

#include <QObject>
#include "define.h"
#include "sa_user_variable.h"
#include <QPoint>


#define NEEDVERSION 0  //Johnson 091008


class user_limit : public QObject {
public:
    explicit user_limit(user_variable &m_user_variable);
    user_variable *globalUserVariable;
    void sortLimitFreq(qint32 limitSelect = -1);
public:
#if NEEDVERSION
    //Edit Limit Johnson 0828
    qint32 gLimitType[LIMIT_SELECTSUM][LIMIT_TOTAL];
    qreal gStartX[LIMIT_SELECTSUM][LIMIT_TOTAL];
    qreal gStopX[LIMIT_SELECTSUM][LIMIT_TOTAL];
    qreal gStartY[LIMIT_SELECTSUM][LIMIT_TOTAL];
    qreal gStopY[LIMIT_SELECTSUM][LIMIT_TOTAL];

    qint32 lineXAxisStartX[LIMIT_SELECTSUM][LIMIT_TOTAL];
    qint32 lineXAxisStopX[LIMIT_SELECTSUM][LIMIT_TOTAL];
    qint32 lineYAxisStartY[LIMIT_SELECTSUM][LIMIT_TOTAL];
    qint32 lineYAxisStopY[LIMIT_SELECTSUM][LIMIT_TOTAL];


    qint32  LimitUpperDrawPoint[LIMIT_SELECTSUM][NUM_SWEEP_POINT];
    qint32  LimitLowerDrawPoint[LIMIT_SELECTSUM][NUM_SWEEP_POINT];

    void limitLineInterpolationCalculatorFunc(void);
    void limitLineXAxisCalculatorFunc(void);   // Limit Line Freq Setting Position Find & Save
    void limitLineYAxisCalculatorFunc(void);   // Limit Line Amplitude Setting Position Find & Save
#endif
    void limitVariableInitializationFunc(void);  // Limit Line 초기화
    void limitSetInitializationFunc(void);  // Limit Setting 초기화


    //Johnson 0906
    qint32 gLatestLimitTestResult[LIMIT_SELECTSUM];
    qint32 gLatestLimitEdgeResult[LIMIT_SELECTSUM];
    qint32 gLatestLimitType[LIMIT_SELECTSUM];
    qint32 gTotalDot[LIMIT_SELECTSUM];
    qint32 gXIndex[LIMIT_SELECTSUM][LIMIT_TOTALDOT];
    qint32 gXAxis[LIMIT_SELECTSUM][LIMIT_TOTALDOT];
    qint32 gYAxis[LIMIT_SELECTSUM][LIMIT_TOTALDOT];
    qint32 gEdgeYAxis[LIMIT_SELECTSUM][LIMIT_TOTALDOT];
    qreal  gFreq[LIMIT_SELECTSUM][LIMIT_TOTALDOT];
    qreal  gAmplitude[LIMIT_SELECTSUM][LIMIT_TOTALDOT];
    qint32 gLatestLimitDrawPoint[LIMIT_SELECTSUM][NUM_SWEEP_POINT];
    qint32 gLatestLimitEdgeDrawPoint[LIMIT_SELECTSUM][NUM_SWEEP_POINT];
    qint32 gLatestLimitUpperDrawPoint[NUM_SWEEP_POINT];
    qint32 gLatestLimitLowerDrawPoint[NUM_SWEEP_POINT];
    qint32 gLatestLimitUpperEdgeDrawPoint[NUM_SWEEP_POINT];
    qint32 gLatestLimitLowerEdgeDrawPoint[NUM_SWEEP_POINT];
    //Tony
    qint32 gCurLimitIndex[LIMIT_SELECTSUM];
    QPoint gSpurLimit[NUM_SWEEP_POINT];

    //Tony
    qint32        gFirstIn[LIMIT_SELECTSUM];
    //Johnson 0823
    qint32        gLimitSelect;
    qint32        gLimitEdge[LIMIT_SELECTSUM];
    qreal         gLimitEdgeValue[LIMIT_SELECTSUM];

    qint32        gLimitTestResult[LIMIT_SELECTSUM];   // Limit Test 후 결과 저장
    qint32        gLimitTest;   // Limit 관련 변수
    qint32        gLimitLine[LIMIT_SELECTSUM];
    qint32        gLimitAlarm[LIMIT_SELECTSUM];
    qint32        gLimitMessage[LIMIT_SELECTSUM];

    void limitXAxisCalculatorFunc(quint64 Freq,quint32 index,quint32 uLimitSelect);//caculate the x axis of every point
    void LatestLimitYAxisCalculatorFunc(qreal level,quint32 index,quint32 uLimitSelect);//caculate the y axis of every point
    void LatestLimitLineInterpolationCalculatorFunc(quint32 uLimitSelect);//get the y axis inside the limit dot rang
    void getLowerUpperLimitLineInterpolation(void);//get all dots'x_axis and y_axis

    void gridAxisCalculatorFunc(void);  // Grid Display (Maker Display에 영향을 받음)
    void caculateLimitTotalLine();

    qint32  limitYAxisCalculatorFunc(qreal level);
};
#endif // USER_LIMIT

