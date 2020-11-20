/****************************************Copyright (c)****************************************************
**
**                                     INNO Instrument(China) Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                sa_user_limit.cpp
** Latest Version:           V1.0.0
** Created by:               Johnson
** Created date:             2018/12/05
** Descriptions:             the class which used to define the global parameters relative to limit
**
*********************************************************************************************************/

#include "sa_user_limit.h"
#include <QDebug>
#include "sa_stdafx.h"
#include "sa_user_variable.h"
#include "define.h"
#include "default.h"
#include <math.h>

user_limit::user_limit(user_variable &m_user_variable)
{
    globalUserVariable = &m_user_variable;
#ifdef SAMPLE_LIMIT
    gUpperLimit = TABLEWIDGET_AMP_MAX;
    gLowerLimit = TABLEWIDGET_AMP_MIN;
    gUpperLimitStatus = SA_OFF;
    gLowerLimitStatus = SA_OFF;
    gUpperLimitTestResult = SA_PASS;
    gLowerLimitTestResult = SA_PASS;

    gATLdBcLimit = SA_ATL_DBC_LIMIT;
    gATLdBcLimitStatus = SA_OFF;
    gATLdBcLimitTestResult = SA_PASS;
#endif
    for(qint32 i = 0;i<LIMIT_SELECTSUM;i++)
    {
        gCurLimitIndex[i] = 1;
        gLimitTestResult[i] = SA_PASS;
        gLimitLine[i]       = SA_OFF;
        gLimitAlarm[i]      = SA_OFF;
        gLimitMessage[i]    = SA_OFF;
        gLimitEdge[i]       = SA_OFF;
        gLimitEdgeValue[i]  = 0.;
        gLatestLimitType[i] = UPPER;
        gTotalDot[i]        = 0;

        gLatestLimitTestResult[i]     = SA_PASS;
        gLatestLimitEdgeResult[i]     = SA_PASS;

        for(qint32 j = 0;j<LIMIT_TOTALDOT;j++)
        {
#if NEEDVERSION
            gLimitType[i][j]      = LIMIT_OFF;
            gStartX[i][j]         = 0.;
            gStopX[i][j]          = 0.;
            gStartY[i][j]         = 0.;
            gStopY[i][j]          = 0.;
            lineXAxisStartX[i][j] = 0;
            lineXAxisStopX[i][j]  = 0;
            lineYAxisStartY[i][j] = 0;
            lineYAxisStopY[i][j]  = 0;
#endif

            gXIndex[i][j]         = 0;
            gXAxis[i][j]          = 0;
            gYAxis[i][j]          = 0;
            gEdgeYAxis[i][j]      = 0;
            gFreq[i][j]           = 0.;
            gAmplitude[i][j]      = 0.;
        }

        for(qint32 k = 0;k<NUM_SWEEP_POINT;k++)
        {
#if NEEDVERSION
            LimitUpperDrawPoint[i][k] = 0;
            LimitLowerDrawPoint[i][k] = 0;
#endif
            gLatestLimitDrawPoint[i][k]     = 0;
            gLatestLimitEdgeDrawPoint[i][k] = 0;
        }
    }

    for(qint32 j = 0;j<NUM_SWEEP_POINT;j++)
    {
        gLatestLimitUpperDrawPoint[j]                 = 0;
        gLatestLimitLowerDrawPoint[j]                 = 0;
        gLatestLimitUpperEdgeDrawPoint[j]             = 0;
        gLatestLimitLowerEdgeDrawPoint[j]             = 0;
    }
    gLimitTest                 = SA_OFF;
    gLimitSelect               = LIMIT1;
}
qint32 user_limit::limitYAxisCalculatorFunc(qreal level)
{

    f64 f64dBmPerYPixel;
    qint32 ret;
    f64 f64ScaleDiv = globalUserVariable->gScaleDiv;//Johnson 0821
    f64 f64BaseLevel = globalUserVariable->gRefLevel + globalUserVariable->gRefOffset;

    //  qDebug() << "f64BaseLevel" << f64BaseLevel;

    f64dBmPerYPixel = f64ScaleDiv / (f64)(SA_guiDrawSet.gridVerStep);
    ret = (qint32)round((f64BaseLevel - level) / f64dBmPerYPixel);

    //***********Johnson 0821********************
    /*if (ret < 0)
        {
          ret = 0;
        }
      else if (ret > GRID_HEIGHT)
        {
          ret = GRID_HEIGHT;
        }*/

    //Johnson 0829 change
    /*if (ret < 0)
        {
          ret = 0;
        }
      else if (ret > globalUserVariable->gridYPos[10]-GRID_START_Y)
        {
          ret = globalUserVariable->gridYPos[10]-GRID_START_Y;
        }*/
    //***************************************

    return ret;
}
//Johnson 0912 Add
void user_limit::getLowerUpperLimitLineInterpolation()
{
    memset(gLatestLimitUpperDrawPoint,0,sizeof(qint32)*NUM_SWEEP_POINT);
    memset(gLatestLimitUpperEdgeDrawPoint,0,sizeof(qint32)*NUM_SWEEP_POINT);
    memset(gLatestLimitLowerDrawPoint,0,sizeof(qint32)*NUM_SWEEP_POINT);
    memset(gLatestLimitLowerEdgeDrawPoint,0,sizeof(qint32)*NUM_SWEEP_POINT);

    for(qint32 i = 0;i<LIMIT_SELECTSUM;i++){
        if(gLatestLimitType[i] == UPPER && gLimitLine[i] == SA_ON){
            for(qint32 j = 0;j<NUM_SWEEP_POINT;j++){
                if(gLatestLimitUpperDrawPoint[j] < gLatestLimitDrawPoint[i][j])
                    gLatestLimitUpperDrawPoint[j] = gLatestLimitDrawPoint[i][j];

                if(gLatestLimitUpperEdgeDrawPoint[j] < gLatestLimitEdgeDrawPoint[i][j])
                    gLatestLimitUpperEdgeDrawPoint[j] = gLatestLimitEdgeDrawPoint[i][j];
            }
        }
        else if(gLatestLimitType[i] == LOWER && gLimitLine[i] == SA_ON){
            for(qint32 j = 0;j<NUM_SWEEP_POINT;j++){
                if(gLatestLimitLowerDrawPoint[j] < gLatestLimitDrawPoint[i][j])
                    gLatestLimitLowerDrawPoint[j] = gLatestLimitDrawPoint[i][j];

                if(gLatestLimitLowerEdgeDrawPoint[j] < gLatestLimitEdgeDrawPoint[i][j])
                    gLatestLimitLowerEdgeDrawPoint[j] = gLatestLimitEdgeDrawPoint[i][j];
            }
        }
    }
}
//Johnson 0907 Add
void user_limit::LatestLimitLineInterpolationCalculatorFunc(quint32 uLimitSelect)
{
    qint32 i = 0;
    qint32 k = 0;
    qint32 cnt = 0;

    qint32 manualPreviousXPos = 0;
    qint32 manualCurrentXPos  = 0;

    qreal manualPreviousYPos = 0;
    qreal manualCurrentYPos = 0;
    qreal manualPreviousEdgeYPos = 0;
    qreal manualCurrentEdgeYPos = 0;
    qreal manualYStep = 0.;
    qreal manualEdgeYStep = 0.;
    qreal calYAxis = 0.;

    memset(gLatestLimitDrawPoint[uLimitSelect],0,sizeof(qint32)*NUM_SWEEP_POINT);
    memset(gLatestLimitEdgeDrawPoint[uLimitSelect],0,sizeof(qint32)*NUM_SWEEP_POINT);

    for (i = 1; i < gTotalDot[uLimitSelect]; i++){
        manualPreviousXPos = gXIndex[uLimitSelect][i-1];
        manualCurrentXPos = gXIndex[uLimitSelect][i];
        manualPreviousYPos = gYAxis[uLimitSelect][i-1];
        manualCurrentYPos = gYAxis[uLimitSelect][i];

        manualPreviousEdgeYPos = gEdgeYAxis[uLimitSelect][i-1];
        manualCurrentEdgeYPos = gEdgeYAxis[uLimitSelect][i];

        manualYStep     = (qreal)(manualCurrentYPos - manualPreviousYPos) / (qreal) (manualCurrentXPos - manualPreviousXPos);
        manualEdgeYStep = (qreal)(manualCurrentEdgeYPos - manualPreviousEdgeYPos) / (qreal) (manualCurrentXPos - manualPreviousXPos);

        cnt = 0;
        for (k = manualPreviousXPos; k < manualCurrentXPos; k++){
            calYAxis = manualPreviousYPos + (manualYStep * (qreal)cnt);

            if(calYAxis<DRAW_GRID_START_Y) calYAxis = DRAW_GRID_START_Y;
            else if(calYAxis>globalUserVariable->gridYPos[GRIDY_LENGTH - 1])
                calYAxis = globalUserVariable->gridYPos[GRIDY_LENGTH - 1];

            if ( gLatestLimitDrawPoint[uLimitSelect][k] < calYAxis)
                gLatestLimitDrawPoint[uLimitSelect][k] = calYAxis;

            //Limit Edge
            calYAxis = manualPreviousEdgeYPos + (manualEdgeYStep * (qreal)cnt);

            if(calYAxis<DRAW_GRID_START_Y) calYAxis = DRAW_GRID_START_Y;
            else if(calYAxis>globalUserVariable->gridYPos[GRIDY_LENGTH - 1])
                calYAxis = globalUserVariable->gridYPos[GRIDY_LENGTH - 1];

            if ( gLatestLimitEdgeDrawPoint[uLimitSelect][k] == 0)
                gLatestLimitEdgeDrawPoint[uLimitSelect][k] = calYAxis;
            else if ( gLatestLimitEdgeDrawPoint[uLimitSelect][k] < calYAxis)
                gLatestLimitEdgeDrawPoint[uLimitSelect][k] = calYAxis;

            cnt++;
        }
    }
}

#if NEEDVERSION
void user_limit::limitLineInterpolationCalculatorFunc()
{
    qint32 i = 0;
    qint32 k = 0;
    qint32 cnt = 0;

    qint32 manualXStartPos = 0.;
    qint32 manualXStopPos = 0.;

    qreal manualYStartPos = 0.;
    qreal manualYStopPos = 0.;
    qreal manualYStep = 0.;
    qreal calYAxis = 0.;




    for (i = 0; i < LIMIT_TOTAL; i++)    {

        if (gLimitType[gLimitSelect][i] != LIMIT_OFF) {

            manualXStartPos = lineXAxisStartX[gLimitSelect][i];
            manualXStopPos = lineXAxisStopX[gLimitSelect][i];

            manualYStartPos = lineYAxisStartY[gLimitSelect][i];
            manualYStopPos = lineYAxisStopY[gLimitSelect][i];

            //qDebug() << "[limitLineInterpolationCalculatorFunc]______" << lineYAxisStartY[gLimitSelect][i] << " / " << lineYAxisStopY[gLimitSelect][i] ;


            if (gLimitType[gLimitSelect][i] == UPPER)  {
                manualYStep = (qreal)(manualYStopPos - manualYStartPos) / (qreal) (manualXStopPos - manualXStartPos);

                cnt = 0;
                for (k = manualXStartPos; k < manualXStopPos; k++)    {   // upper  y 좌표
                    calYAxis = manualYStartPos + (manualYStep * (qreal)cnt);

                    //Johnson 0831
                    if(calYAxis<DRAW_GRID_START_Y) calYAxis = DRAW_GRID_START_Y;
                    else if(calYAxis>globalUserVariable->gridYPos[GRIDY_LENGTH - 1])
                        calYAxis = globalUserVariable->gridYPos[GRIDY_LENGTH - 1];

                    if ( LimitUpperDrawPoint[gLimitSelect][k] < calYAxis)
                        LimitUpperDrawPoint[gLimitSelect][k] = calYAxis;

                    cnt++;
                }
            }   else if (gLimitType[gLimitSelect][i] == LOWER)  {
                manualYStep = (qreal)(manualYStopPos - manualYStartPos) / (qreal) (manualXStopPos - manualXStartPos);

                cnt = 0;
                for (k = manualXStartPos; k < manualXStopPos; k++) {
                    calYAxis = manualYStartPos + (manualYStep * (qreal)cnt);

                    //Johnson 0831
                    if(calYAxis<DRAW_GRID_START_Y) calYAxis = DRAW_GRID_START_Y;
                    else if(calYAxis>globalUserVariable->gridYPos[GRIDY_LENGTH - 1])
                        calYAxis = globalUserVariable->gridYPos[GRIDY_LENGTH - 1];

                    if ( LimitLowerDrawPoint[gLimitSelect][k] == 0)
                        LimitLowerDrawPoint[gLimitSelect][k] = calYAxis;
                    else if ( LimitLowerDrawPoint[gLimitSelect][k] < calYAxis)
                        LimitLowerDrawPoint[gLimitSelect][k] = calYAxis;

                    cnt++;
                }
            }
        }
    }
}
#endif

#if NEEDVERSION
void user_limit::limitLineXAxisCalculatorFunc()    // 입력된 주파수 (StartX, StopX)로 Graph 상의 위치 Find
{
    qint32 i = 0;
    qint32 k = 0;
    quint64 startFreq = 0;
    quint64 stopFreq = 0;
    quint64 tempFreq = 0;
    quint64 vigeoFreq = 0;


    for (i = 0; i < LIMIT_TOTAL; i++) {
        if (gLimitType[gLimitSelect][i] != LIMIT_OFF) {
            startFreq = ((quint64) gStartX[gLimitSelect][i]) * SA_MHZ;
            stopFreq = ((quint64) gStopX[gLimitSelect][i]) * SA_MHZ;

            // Limit Line Start Freq Position Find
            for (k = 0; k < (globalUserVariable->gSweepTracePoint + 1); k++) {
                tempFreq =  globalUserVariable->gStepFreq * k;
                vigeoFreq = globalUserVariable->gStartFreq + tempFreq;

                if (vigeoFreq >= startFreq) {
                    lineXAxisStartX[gLimitSelect][i] = k;
                    break;
                } else if (startFreq < globalUserVariable->gStartFreq) {
                    lineXAxisStartX[gLimitSelect][i] = 0;
                    break;
                }
            }

            // Limit Line Start Freq Position Find
            for (k = 0; k < (globalUserVariable->gSweepTracePoint + 1); k++) {
                tempFreq =  globalUserVariable->gStepFreq * k;
                vigeoFreq = globalUserVariable->gStartFreq + tempFreq;

                if (vigeoFreq >= stopFreq) {
                    lineXAxisStopX[gLimitSelect][i] = k;
                    break;
                } else if (stopFreq >= globalUserVariable->gStopFreq) {
                    lineXAxisStopX[gLimitSelect][i] = globalUserVariable->gSweepTracePoint ;
                    break;
                }
            }

            //qDebug() << "______" << lineXAxisStartX[gLimitSelect][i] << " / " << lineXAxisStopX[LIMIT_SELECTSUM][i] ;
        }
    }
}
#endif

#if NEEDVERSION
void user_limit::limitLineYAxisCalculatorFunc()     // 입력된 Amplitude (StartY, StopY)로 Graph 상의 위치 Find

{
    qint32 k = 0;
    qint32 yAxis = 0;

    for (k = 0; k < LIMIT_TOTAL ; k++)
    {
        if (gLimitType[gLimitSelect][k] != LIMIT_OFF) {
            yAxis = (limitYAxisCalculatorFunc(gStartY[gLimitSelect][k]) + DRAW_GRID_START_Y);
            lineYAxisStartY[gLimitSelect][k] = yAxis;

            yAxis = (limitYAxisCalculatorFunc(gStopY[gLimitSelect][k]) + DRAW_GRID_START_Y);
            lineYAxisStopY[gLimitSelect][k] = yAxis;

            //qDebug() << "[limitLineYAxisCalculatorFunc]______" << lineYAxisStartY[gLimitSelect][k] << " / " << lineYAxisStopY[gLimitSelect][k] ;

        }
    }

}
#endif

void user_limit::limitVariableInitializationFunc()
{
    SA_guiDrawSet.limitLineOnCount = 0;

    for(qint32 i = 0;i<LIMIT_SELECTSUM;i++){
        gLatestLimitType[i] = UPPER;
        gTotalDot[i]        = 0;
        gLimitLine[i]       = SA_OFF;
        gLimitEdge[i]       = SA_OFF;
        gLimitEdgeValue[i]  = 0.;
    }

    gLimitTest = SA_OFF;

    memset(gXIndex[LIMIT_SELECTSUM],0,sizeof(qint32) * LIMIT_TOTALDOT);
    memset(gXAxis[LIMIT_SELECTSUM],0,sizeof(qint32) * LIMIT_TOTALDOT);
    memset(gYAxis[LIMIT_SELECTSUM],0,sizeof(qint32) * LIMIT_TOTALDOT);
    memset(gEdgeYAxis[LIMIT_SELECTSUM],0,sizeof(qint32) * LIMIT_TOTALDOT);
    memset(gFreq[LIMIT_SELECTSUM],0.,sizeof(qreal) * LIMIT_TOTALDOT);
    memset(gAmplitude[LIMIT_SELECTSUM],0.,sizeof(qreal) * LIMIT_TOTALDOT);

    memset(gLatestLimitDrawPoint[LIMIT_SELECTSUM],0,sizeof(qint32) * LIMIT_TOTALDOT);
    memset(gLatestLimitDrawPoint[LIMIT_SELECTSUM],0,sizeof(qint32) * LIMIT_TOTALDOT);
    memset(gLatestLimitUpperDrawPoint,0,sizeof(qint32) * LIMIT_TOTALDOT);
    memset(gLatestLimitLowerDrawPoint,0,sizeof(qint32) * LIMIT_TOTALDOT);
    memset(gLatestLimitUpperEdgeDrawPoint,0,sizeof(qint32) * LIMIT_TOTALDOT);
    memset(gLatestLimitLowerEdgeDrawPoint,0,sizeof(qint32) * LIMIT_TOTALDOT);
    /*memset(gStartX[gLimitSelect], 0., sizeof(qreal) * LIMIT_TOTAL);
    memset(gStopX[gLimitSelect], 0., sizeof(qreal) * LIMIT_TOTAL);
    memset(gStartY[gLimitSelect], 0., sizeof(qreal) * LIMIT_TOTAL);
    memset(gStopY[gLimitSelect], 0., sizeof(qreal) * LIMIT_TOTAL);

    memset(lineXAxisStartX[gLimitSelect], 0, sizeof(qint32) * LIMIT_TOTAL);
    memset(lineXAxisStopX[gLimitSelect], 0, sizeof(qint32) * LIMIT_TOTAL);
    memset(lineYAxisStartY[gLimitSelect], 0, sizeof(qint32) * LIMIT_TOTAL);
    memset(lineYAxisStopY[gLimitSelect], 0, sizeof(qint32) * LIMIT_TOTAL);

    memset(LimitLowerDrawPoint[gLimitSelect], 0, sizeof(qint32) * NUM_SWEEP_POINT);
    memset(LimitUpperDrawPoint[gLimitSelect], 0, sizeof(qint32) * NUM_SWEEP_POINT);*/

}
void user_limit::limitSetInitializationFunc()
{
    memset(gLimitLine,SA_OFF,sizeof(qint32)*LIMIT_SELECTSUM);
    memset(gLimitEdge,SA_OFF,sizeof(qint32)*LIMIT_SELECTSUM);
    memset(gLimitEdgeValue,0.,sizeof(qreal)*LIMIT_SELECTSUM);

    gLimitTest = SA_OFF;

    /*gLimitTest[gLimitSelect]      = SA_OFF;
    gLimitLine[gLimitSelect]      = SA_OFF;
    gLimitAlarm[gLimitSelect]     = SA_OFF;
    gLimitMessage[gLimitSelect]   = SA_OFF;
    gLimitEdge[gLimitSelect]      = SA_OFF;
    gLimitEdgeValue[gLimitSelect] = 0.;*/
    //gLimitSelect  = LIMIT1;
}

//Johnson 0906
void user_limit::limitXAxisCalculatorFunc(qint64 Freq,qint32 index,qint32 uLimitSelect)
{
    //Freq = Freq * SA_MHZ;

    // Limit Line Freq Position Find
    for (qint32 k = 0; k < (globalUserVariable->gSweepTracePoint + 1); k++) {
        qint64 tempFreq =  globalUserVariable->gStepFreq * k;
        qint64 vigeoFreq = globalUserVariable->gStartFreq + tempFreq;

        if (vigeoFreq >= Freq) {
            gXIndex[uLimitSelect][index] = k;
            break;
        } else if (Freq < globalUserVariable->gStartFreq) {
            gXIndex[uLimitSelect][index] = 0;
            break;
        }
        else if (Freq >= globalUserVariable->gStopFreq) {
            gXIndex[uLimitSelect][index] = globalUserVariable->gSweepTracePoint ;
            break;
        }
    }
}
void user_limit::LatestLimitYAxisCalculatorFunc(qreal level, quint32 index,quint32 uLimitSelect)
{
    qint32 yAxis = 0;

    yAxis = (limitYAxisCalculatorFunc(level) + DRAW_GRID_START_Y);
    gYAxis[uLimitSelect][index] = yAxis;

    if(gLatestLimitType[uLimitSelect] == UPPER){
        yAxis = (limitYAxisCalculatorFunc(level-gLimitEdgeValue[uLimitSelect]) + DRAW_GRID_START_Y);
    }
    else if(gLatestLimitType[uLimitSelect] == LOWER){
        yAxis = (limitYAxisCalculatorFunc(level+gLimitEdgeValue[uLimitSelect]) + DRAW_GRID_START_Y);
    }
    gEdgeYAxis[uLimitSelect][index] = yAxis;
}
void user_limit::gridAxisCalculatorFunc()
{
    //Johnson 1016 need to rewrite
#if 0
    qint32 calGridVstep = 0;

    if (gTraceType[gTraceSelect] != SA_TRACE_OFF) {

        qDebug() << "_____";
        if (gMarkerDisplay == MKR_TABLE && SA_guiDrawSet.markerOnCount != 0) {
            //Johnson 0807 add
            if(gMeasurement == SA_CHANNEL_POWER || gMeasurement == SA_ACP){
                if(gMeasurement == SA_CHANNEL_POWER)
                    SA_guiDrawSet.gridVerStep = (GRID_HEIGHT - (SA_guiDrawSet.markerOnCount * MARKER_FONT_HEIGHT)-MARKER_FONT_HEIGHT) / GRID_NUM_Y_TICKS;
                else
                    SA_guiDrawSet.gridVerStep = (GRID_HEIGHT - (SA_guiDrawSet.markerOnCount * MARKER_FONT_HEIGHT)-MARKER_FONT_HEIGHT*3) / GRID_NUM_Y_TICKS;

                for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++) {
                    gridXPos[i] = GRID_START_X + SA_guiDrawSet.gridHorStep * i;
                    gridYPos[i] = GRID_START_Y + SA_guiDrawSet.gridVerStep * i;
                }
            }
            else{
                calGridVstep = (GRID_HEIGHT - (SA_guiDrawSet.markerOnCount * MARKER_FONT_HEIGHT)) / GRID_NUM_Y_TICKS;
                SA_guiDrawSet.gridVerStep = calGridVstep;

                for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++) {
                    gridXPos[i] = GRID_START_X + SA_guiDrawSet.gridHorStep * i;
                    gridYPos[i] = GRID_START_Y + calGridVstep * i;
                }
            }
        } else {
            //Johnson 0807 add
            if(gMeasurement == SA_CHANNEL_POWER || gMeasurement == SA_ACP){
                if(gMeasurement == SA_CHANNEL_POWER) SA_guiDrawSet.gridVerStep = (GRID_HEIGHT-MARKER_FONT_HEIGHT)/GRID_NUM_Y_TICKS;
                else SA_guiDrawSet.gridVerStep = (GRID_HEIGHT-MARKER_FONT_HEIGHT*3)/GRID_NUM_Y_TICKS;
                for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++) {
                    gridXPos[i] = GRID_START_X + SA_guiDrawSet.gridHorStep * i;
                    gridYPos[i] = GRID_START_Y + SA_guiDrawSet.gridVerStep * i;
                }
            }
            else{
                SA_guiDrawSet.gridVerStep = GRID_HEIGHT /  GRID_NUM_Y_TICKS;
                for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++){
                    gridXPos[i] = GRID_START_X + SA_guiDrawSet.gridHorStep * i;
                    gridYPos[i] = GRID_START_Y + SA_guiDrawSet.gridVerStep * i;
                }
            }
        }
    } else {
        //Johnson 0807 add
        if(gMeasurement == SA_CHANNEL_POWER || gMeasurement == SA_ACP){
            if(gMeasurement == SA_CHANNEL_POWER) SA_guiDrawSet.gridVerStep = (GRID_HEIGHT-MARKER_FONT_HEIGHT)/GRID_NUM_Y_TICKS;
            else SA_guiDrawSet.gridVerStep = (GRID_HEIGHT-MARKER_FONT_HEIGHT*3)/GRID_NUM_Y_TICKS;
            for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++) {
                gridXPos[i] = GRID_START_X + SA_guiDrawSet.gridHorStep * i;
                gridYPos[i] = GRID_START_Y + SA_guiDrawSet.gridVerStep * i;
            }
        }
        else{
            SA_guiDrawSet.gridVerStep = GRID_HEIGHT /  GRID_NUM_Y_TICKS;
            for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++){
                gridXPos[i] = GRID_START_X + SA_guiDrawSet.gridHorStep * i;
                gridYPos[i] = GRID_START_Y + SA_guiDrawSet.gridVerStep * i;
            }
        }
    }
#else  //Johnson 1017
    qint32 calGridVstep = 0;

    //Johnson need to change ;globalUserVariable->mDrawHeight will change every time when table is changed

    /*if(globalUserVariable->gTraceType[globalUserVariable->gTraceSelect] != SA_TRACE_OFF && globalUserVariable->gMarkerDisplay == MKR_TABLE && SA_guiDrawSet.markerOnCount != 0)
    {
        if(globalUserVariable->gMeasurement == SA_CHANNEL_POWER || globalUserVariable->gMeasurement == SA_ACP || globalUserVariable->gMeasurement == SA_OCCUPIED_BW)
        {
            calGridVstep = (globalUserVariable->mDrawHeight -SA_TOPDIS -SA_BOTTOMDIS) / GRID_NUM_Y_TICKS;
            SA_guiDrawSet.gridVerStep = calGridVstep;

            for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++)
            {
                globalUserVariable->gridXPos[i] = DRAW_GRID_START_X + SA_guiDrawSet.gridHorStep * i;
                globalUserVariable->gridYPos[i] = DRAW_GRID_START_Y + calGridVstep * i;
            }
        }
        else
        {
            SA_guiDrawSet.gridVerStep = (globalUserVariable->mDrawHeight -SA_TOPDIS -SA_BOTTOMDIS) /  GRID_NUM_Y_TICKS;
            for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++)
            {
                globalUserVariable->gridXPos[i] = DRAW_GRID_START_X + SA_guiDrawSet.gridHorStep * i;
                globalUserVariable->gridYPos[i] = DRAW_GRID_START_Y + SA_guiDrawSet.gridVerStep * i;
            }
        }
    }
    else
    {
        if(globalUserVariable->gMeasurement == SA_CHANNEL_POWER || globalUserVariable->gMeasurement == SA_ACP || globalUserVariable->gMeasurement == SA_OCCUPIED_BW)
        {
            calGridVstep = (globalUserVariable->mDrawHeight -SA_TOPDIS -SA_BOTTOMDIS - globalUserVariable->widgetTableHeight) / GRID_NUM_Y_TICKS;
            SA_guiDrawSet.gridVerStep = calGridVstep;

            for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++)
            {
                globalUserVariable->gridXPos[i] = DRAW_GRID_START_X + SA_guiDrawSet.gridHorStep * i;
                globalUserVariable->gridYPos[i] = DRAW_GRID_START_Y + calGridVstep * i;
            }
        }
        else
        {
            SA_guiDrawSet.gridVerStep = (globalUserVariable->mDrawHeight -SA_TOPDIS -SA_BOTTOMDIS) /  GRID_NUM_Y_TICKS;
            for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++)
            {
                globalUserVariable->gridXPos[i] = DRAW_GRID_START_X + SA_guiDrawSet.gridHorStep * i;
                globalUserVariable->gridYPos[i] = DRAW_GRID_START_Y + SA_guiDrawSet.gridVerStep * i;
            }
        }
    }*/

    SA_guiDrawSet.gridVerStep = (globalUserVariable->mDrawHeight -SA_TOPDIS -SA_BOTTOMDIS) /  GRID_NUM_Y_TICKS;
    for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++)
    {
        globalUserVariable->gridXPos[i] = DRAW_GRID_START_X + SA_guiDrawSet.gridHorStep * i;
        globalUserVariable->gridYPos[i] = DRAW_GRID_START_Y + SA_guiDrawSet.gridVerStep * i;
    }

    /*if ((globalUserVariable->gTraceType[globalUserVariable->gTraceSelect] != SA_TRACE_OFF && globalUserVariable->gMarkerDisplay == MKR_TABLE && SA_guiDrawSet.markerOnCount != 0) ||
         globalUserVariable->gMeasurement == SA_CHANNEL_POWER || globalUserVariable->gMeasurement == SA_ACP || globalUserVariable->gMeasurement == SA_OCCUPIED_BW)
    {
//        if(globalUserVariable->bSmallCanvas)
//            calGridVstep = (SMALLDRAW_GRID_HEIGHT - (10 * MARKER_FONT_HEIGHT)) / GRID_NUM_Y_TICKS;
//        else
//            calGridVstep = (LARGEDRAW_GRID_HEIGHT - (10 * MARKER_FONT_HEIGHT)) / GRID_NUM_Y_TICKS;
        calGridVstep = (globalUserVariable->mDrawHeight -SA_TOPDIS -SA_BOTTOMDIS - (10 * MARKER_FONT_HEIGHT)) / GRID_NUM_Y_TICKS;
        SA_guiDrawSet.gridVerStep = calGridVstep;

        for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++)
        {
            globalUserVariable->gridXPos[i] = DRAW_GRID_START_X + SA_guiDrawSet.gridHorStep * i;
            globalUserVariable->gridYPos[i] = DRAW_GRID_START_Y + calGridVstep * i;
        }
    }
    else
    {
//        if(globalUserVariable->bSmallCanvas)
//            SA_guiDrawSet.gridVerStep = SMALLDRAW_GRID_HEIGHT /  GRID_NUM_Y_TICKS;
//        else
//            SA_guiDrawSet.gridVerStep = LARGEDRAW_GRID_HEIGHT /  GRID_NUM_Y_TICKS;
        SA_guiDrawSet.gridVerStep = (globalUserVariable->mDrawHeight -SA_TOPDIS -SA_BOTTOMDIS) /  GRID_NUM_Y_TICKS;
        for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++)
        {
            globalUserVariable->gridXPos[i] = DRAW_GRID_START_X + SA_guiDrawSet.gridHorStep * i;
            globalUserVariable->gridYPos[i] = DRAW_GRID_START_Y + SA_guiDrawSet.gridVerStep * i;
        }
    }*/
#endif

    //Johnson 0910
    caculateLimitTotalLine();
    if (SA_guiDrawSet.limitLineOnCount != 0)
    {

#if NEEDVERSION
        memset(LimitLowerDrawPoint, 0, sizeof(qint32) * NUM_SWEEP_POINT);
        memset(LimitUpperDrawPoint, 0, sizeof(qint32) * NUM_SWEEP_POINT);

        limitLineYAxisCalculatorFunc();
        limitLineInterpolationCalculatorFunc();
#endif


        LatestLimitLineInterpolationCalculatorFunc(gLimitSelect);

        //Johnson 0907 Add
        for(qint32 i = 0;i<LIMIT_SELECTSUM;i++)
        {
            for(qint32 j = 0;j<gTotalDot[i];j++)
            {
                LatestLimitYAxisCalculatorFunc(gAmplitude[i][j],j,i);
            }
        }
    }
}
void user_limit::caculateLimitTotalLine()
{
    SA_guiDrawSet.limitLineOnCount = 0;
    for(qint32 i = 0;i<LIMIT_SELECTSUM;i++){
        if(gTotalDot[i] != 0) SA_guiDrawSet.limitLineOnCount++;
    }
}

//sort
void user_limit::sortLimitFreq(qint32 limitSelect)
{
    if(limitSelect < 0 || limitSelect >= LIMIT_SELECTSUM)
    {
        limitSelect = gLimitSelect;
    }
    //sort freq
    for(qint32 i = 0;i<gTotalDot[limitSelect];i++)
    {
        for(int j = i+1;j<gTotalDot[limitSelect];j++)
        {
            if(gFreq[limitSelect][i] > gFreq[limitSelect][j])
            {
                if(gCurLimitIndex[limitSelect] == (i + 1))
                {
                    gCurLimitIndex[limitSelect] = j + 1;
                }else if(gCurLimitIndex[limitSelect] == (j + 1))
                {
                    gCurLimitIndex[limitSelect] = i + 1;
                }
                double tmp = 0.;
                tmp = gFreq[limitSelect][i];
                gFreq[limitSelect][i] = gFreq[limitSelect][j];
                gFreq[limitSelect][j] = tmp;

                tmp = gAmplitude[limitSelect][i];
                gAmplitude[limitSelect][i] = gAmplitude[limitSelect][j];
                gAmplitude[limitSelect][j] = tmp;
            }
            if(gFreq[limitSelect][i] == gFreq[limitSelect][j])
            {
                if(gAmplitude[limitSelect][i] > gAmplitude[limitSelect][j])
                {
                    double tmp = 0.;
                    tmp = gFreq[limitSelect][i];
                    gFreq[limitSelect][i] = gFreq[limitSelect][j];
                    gFreq[limitSelect][j] = tmp;

                    tmp = gAmplitude[limitSelect][i];
                    gAmplitude[limitSelect][i] = gAmplitude[limitSelect][j];
                    gAmplitude[limitSelect][j] = tmp;
                    if(gCurLimitIndex[limitSelect] == i)
                    {
                        gCurLimitIndex[limitSelect] = j + 1;
                    }
                    else if(gCurLimitIndex[limitSelect] == j)
                    {
                        gCurLimitIndex[limitSelect] = i + 1;
                    }
                }
            }
        }
    }
}

