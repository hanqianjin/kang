#include "sa_measure_control.h"
#include "sa_stdafx.h"
#include <QDebug>

sa_Measure_Control::sa_Measure_Control(user_variable &m_user_variable, user_limit &m_user_limit)
{
    globalUserVariable = &m_user_variable;
    globalUserLimit    = &m_user_limit;

    initVariable();

    leftPos = 0;
    rightPos = 0;

    memset(gTraceAverage,0,sizeof(qreal)*NUM_SWEEP_POINT);
    gTraceNumber = 0;
}
sa_Measure_Control::~sa_Measure_Control()
{
    //delete globalUserLimit;
    //delete globalUserVariable;
}
void sa_Measure_Control::initVariable()
{
    dTotalPower = 0.;
    uOccBW = 0.;
    uXdBBW = 0.;
}
/**
 * @brief sa_Measure_Control::caculateTotalPower
 * @return totalPower
 */
qreal sa_Measure_Control::caculateTotalPower()
{
#if !NEW_FORMULA
    dTotalPower = 0.;
    for(qint32 i = 0;i<NUM_SWEEP_POINT;i++){
        if(globalUserVariable->gTraceType[globalUserVariable->gTraceSelect] == SA_VIEW)
        {
            dTotalPower += pow(10, globalUserVariable->gTraceViewDate[globalUserVariable->gTraceSelect][i] / 10.)/1000.;//dTotalPower's unit is W
        }
        else
        {
            dTotalPower += pow(10, globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i] / 10.)/1000.;//dTotalPower's unit is W
        }
    }
    globalUserVariable->dTotalPower = globalUserVariable->wattsToDbmCalculatorFunc(dTotalPower);
#else
    qreal dbmPower = 0.;
    for(int i = 0;i<NUM_SWEEP_POINT;i++){
        if(globalUserVariable->gTraceType[globalUserVariable->gTraceSelect] == SA_VIEW)
        {
            dbmPower += pow(10,globalUserVariable->gTraceViewDate[globalUserVariable->gTraceSelect][i] / 10.);
        }
        else
        {
            dbmPower += pow(10,globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i] / 10.);
        }
    }
    globalUserVariable->dTotalPower = 10 * log10((qreal)((qreal)globalUserVariable->gSpanFreq/globalUserVariable->gRbw)/NUM_SWEEP_POINT*dbmPower);
    dTotalPower = (qreal)((qreal)globalUserVariable->gSpanFreq/globalUserVariable->gRbw)/NUM_SWEEP_POINT*dbmPower;
#endif
    return dTotalPower;
}
/**
 * @brief sa_Measure_Control::calculatePower
 * @param startx int
 * @param horWidth int
 * @param pixelStep double
 * @return power value
 */
qreal sa_Measure_Control::calculatePower(qint32 startx, qint32 horWidth, qint32 gridWidth, qreal pixelStep, qint64 bandwidth)
{
    qreal powervalue = 0.;

//    if(globalUserVariable->bSmallCanvas) gridWidth = SMALLDRAW_GRID_WIDTH;
//    else gridWidth = LARGEDRAW_GRID_WIDTH;

    if(startx<DRAW_GRID_START_X) startx = DRAW_GRID_START_X;
    if(horWidth>gridWidth) horWidth = gridWidth;
    int beginPointIndex = (startx-DRAW_GRID_START_X)/pixelStep;
    int endPointIndex   = (startx+horWidth-DRAW_GRID_START_X)/pixelStep;

    if(endPointIndex == NUM_SWEEP_POINT) endPointIndex = NUM_SWEEP_POINT-1;
#if !NEW_FORMULA
    for(int i = beginPointIndex;i<endPointIndex+1;i++){
        if(globalUserVariable->gTraceType[globalUserVariable->gTraceSelect] == SA_VIEW)
        {
            powervalue += pow(10, globalUserVariable->gTraceViewDate[globalUserVariable->gTraceSelect][i] / 10.)/1000.;//W
        }
        else
        {
            powervalue += pow(10, globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i] / 10.)/1000.;//W
        }
    }
    powervalue = globalUserVariable->wattsToDbmCalculatorFunc(powervalue);
#else
    qreal dbmPower = 0.;
    for(int i = beginPointIndex;i<endPointIndex+1;i++){
        if(globalUserVariable->gTraceType[globalUserVariable->gTraceSelect] == SA_VIEW)
        {
            dbmPower += pow(10,globalUserVariable->gTraceViewDate[globalUserVariable->gTraceSelect][i] / 10.);
        }
        else
        {
            dbmPower += pow(10,globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i] / 10.);
        }
    }
    powervalue = 10 * log10((qreal)((qreal)bandwidth/globalUserVariable->gRbw)/(endPointIndex - beginPointIndex + 1)*dbmPower);
#endif
    return powervalue;
}
void sa_Measure_Control::calAverageData()
{
    if(gTraceNumber >= 100)//Johnson 190417
    {
        gTraceNumber = 100;
    }

    for(qint32 i = 0; i < globalUserVariable->gSweepTracePoint; i++)
    {
        *(gTraceAverage + i) = (*(gTraceAverage+i) * gTraceNumber + (*(globalUserVariable->gOriginalMeasureVal+i))) / (gTraceNumber + 1);
    }

    gTraceNumber++;
}
quint64 sa_Measure_Control::caculateOccBW()
{
    if(globalUserVariable->gTraceType[globalUserVariable->gTraceSelect] == SA_VIEW)
    {
        uOccBW = calculateOccupiedBW(leftPos,rightPos,dTotalPower,SA_OCCUPIED,globalUserVariable->gTraceViewDate[globalUserVariable->gTraceSelect],NUM_SWEEP_POINT,globalUserVariable->gOccupied_BW/100.);
    }
    else
    {
#if 0
        if(globalUserVariable->gTraceType[globalUserVariable->gTraceSelect] == SA_CLEAR_WRITE)
        {
            calAverageData();
            uOccBW = calculateOccupiedBW(leftPos,rightPos,dTotalPower,SA_OCCUPIED,gTraceAverage,NUM_SWEEP_POINT,globalUserVariable->gOccupied_BW/100.);
        }
        else
        {
            gTraceNumber = 0;
            memset(gTraceAverage,0,sizeof(qreal)*NUM_SWEEP_POINT);
            uOccBW = calculateOccupiedBW(leftPos,rightPos,dTotalPower,SA_OCCUPIED,globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect],NUM_SWEEP_POINT,globalUserVariable->gOccupied_BW/100.);
        }
#else
        uOccBW = calculateOccupiedBW(leftPos,rightPos,dTotalPower,SA_OCCUPIED,globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect],NUM_SWEEP_POINT,globalUserVariable->gOccupied_BW/100.);
#endif
    }

    globalUserVariable->uOccupiedBW = uOccBW;
    return uOccBW;
}
quint64 sa_Measure_Control::caculateXdBBW()
{
    if(globalUserVariable->gTraceType[globalUserVariable->gTraceSelect] == SA_VIEW)
    {
        uXdBBW = calculateOccupiedBW(leftPos,rightPos,dTotalPower,SA_XDB,globalUserVariable->gTraceViewDate[globalUserVariable->gTraceSelect],NUM_SWEEP_POINT,globalUserVariable->gXdB);
    }
    else
    {
        uXdBBW = calculateOccupiedBW(leftPos,rightPos,dTotalPower,SA_XDB,globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect],NUM_SWEEP_POINT,globalUserVariable->gXdB);
    }
    globalUserVariable->uXdBBW = uXdBBW;
    return uXdBBW;
}
qint32 sa_Measure_Control::calibrateLeftDotIndex(qint32 peakPos,qreal searchPower,qreal leftPower,qreal *data,qreal powerValue)
{
    qreal PreviousSumValue = pow(10, data[0] / 10.)/1000;
    qreal CurrentSumValue = pow(10, data[0] / 10.)/1000;
    qreal refPowerValue = fabs(powerValue - (2*searchPower - leftPower));
    for(qint32 i = 1;i<peakPos;i++) {
        CurrentSumValue += pow(10, data[i] / 10.)/1000;

        if(PreviousSumValue >= refPowerValue) return i - 1;
        else if(CurrentSumValue == refPowerValue) return i;
        else if(PreviousSumValue < refPowerValue && CurrentSumValue > refPowerValue)
        {
            if(fabs(PreviousSumValue - refPowerValue) <= fabs(CurrentSumValue - powerValue - (2*searchPower - leftPower)))
                return i - 1;
            else return i;
        }

        if(i == peakPos - 1) return i;
        PreviousSumValue = CurrentSumValue;
    }

    return 0 ;
}
qint32 sa_Measure_Control::calibrateRightDotIndex(qint32 peakPos,qint32 num,qreal searchPower,qreal rightPower,qreal *data,qreal powerValue)
{
    qreal PreviousSumValue = pow(10, data[num -1] / 10.)/1000;
    qreal CurrentSumValue = pow(10, data[num - 1] / 10.)/1000;
    qreal refPowerValue = powerValue - (2*searchPower - rightPower);
    for(qint32 i = num - 2;i>peakPos;i--) {
        CurrentSumValue += pow(10, data[i] / 10.)/1000;
        if(PreviousSumValue >= refPowerValue) return i + 1;
        else if(CurrentSumValue == refPowerValue)return i;
        else if(PreviousSumValue < refPowerValue && CurrentSumValue > refPowerValue)
        {
            if(fabs(PreviousSumValue - refPowerValue) <= fabs(CurrentSumValue - refPowerValue)) return i + 1;
            else return i;
        }

        if(i == peakPos + 1) return i;
        PreviousSumValue = CurrentSumValue;
    }

    return 0 ;
}

/**
* @brief sa_Measure_Control::calculateLeftRightDotPos
* @param leftDotIndex
* @param rightDotIndex
* @param searchPowerValue
* @param data
* @param num
*/
void sa_Measure_Control::calculateLeftRightDotPos(qint32 &leftDotIndex, qint32 &rightDotIndex, qint32 peakPos,qreal searchPowerValue, qreal *data, qint32 num)
{
    qreal tmpPowerValue = 0.;

    if(searchPowerValue <= 0)
    {
        leftDotIndex = peakPos;
        rightDotIndex = peakPos;
    }
    else
    {
        if(peakPos == 0)
        {
            leftDotIndex = peakPos;

            //search from peakPos+1 to right
            for(qint32 i = peakPos+1;i<num;i++)
            {
#if !NEW_FORMULA
                tmpPowerValue += pow(10, data[i] / 10.)/1000;
#else
                tmpPowerValue += (qreal)((qreal)((qreal)globalUserVariable->gSpanFreq/NUM_SWEEP_POINT)/globalUserVariable->gRbw*pow(10,data[i]/10.))/1000;
#endif

                if(tmpPowerValue >= searchPowerValue )
                {
                    rightDotIndex = i;
                    break;
                }
                if(i == num - 1)
                {
                    rightDotIndex = i;
                    break;
                }
            }
        }
        else if(peakPos == num - 1)
        {
            rightDotIndex = peakPos;

            //search from peakPos-1 to left
            for(qint32 i = peakPos-1;i>=0;i--)
            {
#if !NEW_FORMULA
                tmpPowerValue += pow(10, data[i] / 10.)/1000;
#else
                tmpPowerValue += (qreal)((qreal)((qreal)globalUserVariable->gSpanFreq/NUM_SWEEP_POINT)/globalUserVariable->gRbw*pow(10,data[i]/10.))/1000;
#endif

                if(tmpPowerValue >= searchPowerValue )
                {
                    leftDotIndex = i;
                    break;
                }
                if(i == 0)
                {
                    leftDotIndex = i;
                    break;
                }
            }
        }
        else
        {
#if 1
            while(1)
            {
                if(tmpPowerValue == searchPowerValue) break;
                else if(tmpPowerValue < searchPowerValue)
                {
                    if(leftDotIndex > 0)
                    {
#if !NEW_FORMULA
                        tmpPowerValue += pow(10, data[--leftDotIndex] / 10.)/1000;
#else
                        tmpPowerValue += (qreal)((qreal)((qreal)globalUserVariable->gSpanFreq/NUM_SWEEP_POINT)/globalUserVariable->gRbw*pow(10,data[--leftDotIndex]/10.))/1000;
#endif
                    }

                    if(tmpPowerValue == searchPowerValue) break;
                    else if(tmpPowerValue > searchPowerValue)
                    {
                        while(1)
                        {
#if !NEW_FORMULA
                            tmpPowerValue -= pow(10, data[--rightDotIndex] / 10.)/1000;
#else
                            tmpPowerValue -= (qreal)((qreal)((qreal)globalUserVariable->gSpanFreq/NUM_SWEEP_POINT)/globalUserVariable->gRbw*pow(10,data[--rightDotIndex]/10.))/1000;
#endif
                            if(tmpPowerValue <= searchPowerValue) break;
                            if(rightDotIndex == peakPos) break;
                        }
                        break;
                    }
                    if(rightDotIndex < num - 1 && tmpPowerValue < searchPowerValue)
                    {
#if !NEW_FORMULA
                        tmpPowerValue += pow(10, data[++rightDotIndex] / 10.)/1000;
#else
                        tmpPowerValue += (qreal)((qreal)((qreal)globalUserVariable->gSpanFreq/NUM_SWEEP_POINT)/globalUserVariable->gRbw*pow(10,data[++rightDotIndex]/10.))/1000;
#endif
                    }
                    if(tmpPowerValue == searchPowerValue) break;
                    if(leftDotIndex == 0 && rightDotIndex == num - 1) break;
                    if(tmpPowerValue > searchPowerValue)
                    {
                        while(1)
                        {
#if !NEW_FORMULA
                            tmpPowerValue -= pow(10, data[++leftDotIndex] / 10.)/1000;
#else
                            tmpPowerValue -= (qreal)((qreal)((qreal)globalUserVariable->gSpanFreq/NUM_SWEEP_POINT)/globalUserVariable->gRbw*pow(10,data[++leftDotIndex]/10.))/1000;
#endif
                            if(tmpPowerValue <= searchPowerValue) break;
                            if(peakPos == leftDotIndex) break;
                        }
                        break;
                    }
                }
            }
#else
            while(1)
            {
                if(tmpPowerValue == searchPowerValue) break;
                else if(tmpPowerValue < searchPowerValue)
                {
                    if(leftDotIndex > 0)
                    {
                        tmpPowerValue += pow(10, data[--leftDotIndex] / 10.)/1000;
                    }

                    if(tmpPowerValue == searchPowerValue) break;
                    else if(tmpPowerValue > searchPowerValue)
                    {
                        qreal leftDotValue = pow(10, data[leftDotIndex] / 10.)/1000;
                        qreal rightDotValue = pow(10, data[rightDotIndex] / 10.)/1000;
                        if(leftDotValue >= rightDotValue)
                        {
                            if(rightDotIndex == peakPos) break;
                            else --rightDotIndex;
                        }
                        else
                        {
                            if(leftDotIndex == peakPos) break;
                            else ++leftDotIndex;
                        }
                        break;
                    }
                    if(rightDotIndex < num - 1 && tmpPowerValue < searchPowerValue)
                    {
                        tmpPowerValue += pow(10, data[++rightDotIndex] / 10.)/1000;
                    }
                    if(tmpPowerValue == searchPowerValue) break;
                    if(leftDotIndex == 0 && rightDotIndex == num - 1) break;
                    if(tmpPowerValue > searchPowerValue)
                    {
                        qreal leftDotValue = pow(10, data[leftDotIndex] / 10.)/1000;
                        qreal rightDotValue = pow(10, data[rightDotIndex] / 10.)/1000;
                        if(leftDotValue >= rightDotValue)
                        {
                            if(rightDotIndex == peakPos) break;
                            else --rightDotIndex;
                        }
                        else
                        {
                            if(leftDotIndex == peakPos) break;
                            else ++leftDotIndex;
                        }
                        break;
                    }
                }
                else break;
            }
#endif
        }
    }
}

/**
 * @brief sa_Measure_Control::calculateOccupiedBW
 * @param leftDotIndex
 * @param rightDotIndex
 * @param dTotalPower
 * @param mode
 * @param data
 * @param num
 * @param dValue
 * @return
 */
quint64 sa_Measure_Control::calculateOccupiedBW(qint32 &leftDotIndex, qint32 &rightDotIndex, qreal dTotalPower, qint32 mode, qreal *data, qint32 num, qreal dValue)
{
    qreal dBW = 0.;

    qreal beforeVal = 0.;
    qreal currentVal = 0;
    qreal afterVal = 0.;
    qreal peakVal  = 0.;
    qint32 peakPos = 0;

    static qreal tmppeakPosePower = 0.;
    static qreal tmpsearchPower = 0.;
    static qint32 tmppeakPose = 0.;
    static qint32 tmpLeftDotIndex = 0.;
    static qint32 tmpRightDotIndex = 0.;
    //*******************find peak value and index********************
    for (qint32 i = 0 ; i < num; i++)
    {
        currentVal = data[i];
        if (i == 0) peakVal = currentVal ;
        else if(i == num - 1)
        {
            if(peakVal<currentVal)
            {
                peakPos = i;
                peakVal = currentVal;
            }
        }
        else if (peakVal < currentVal)
        {
            beforeVal =  data[i - 1];
            afterVal =  data[i + 1];
            if (currentVal >= beforeVal && currentVal >= afterVal)
            {
                peakPos = i;
                peakVal = currentVal;
            }
        }
    }

    leftDotIndex = peakPos;
    rightDotIndex = peakPos;
    //*****************************************************************

    if(mode == SA_OCCUPIED) {
#if 1
    #if !NEW_FORMULA
        qreal peakPosPower = pow(10,data[peakPos]/10.)/1000;
        qreal searchPower  = dValue*dTotalPower - peakPosPower;
    #else
        qreal peakPosPower = (qreal)((qreal)((qreal)globalUserVariable->gSpanFreq/NUM_SWEEP_POINT)/globalUserVariable->gRbw*pow(10,data[peakPos]/10.))/1000;
        qreal searchPower  = dValue*dTotalPower/1000 - peakPosPower;
    #endif

        //Johnson 200210
        if(peakPos == tmppeakPose && fabs(peakPosPower - tmppeakPosePower) <= 1.0e-2 && fabs(searchPower - tmpsearchPower) <= 1.0e-2)
        {
            leftDotIndex = tmpLeftDotIndex;
            rightDotIndex = tmpRightDotIndex;
        }
        else
        {
            calculateLeftRightDotPos(leftDotIndex,rightDotIndex,peakPos,searchPower,data,num);
            tmppeakPose = peakPos;
            tmppeakPosePower = peakPosPower;
            tmpsearchPower = searchPower;
            tmpLeftDotIndex = leftDotIndex;
            tmpRightDotIndex = rightDotIndex;
        }
#else
        qreal peakPosPower = pow(10,data[peakPos]/10.)/1000;
        qreal searchPower  = (dValue*dTotalPower - peakPosPower)/2/**(dTotalPower - peakPosPower)*/;
        qreal tmpPreviousOcc_Bw = 0.;
        qreal tmpCurrentOcc_Bw = 0.;
        qreal leftPowerValue = 0.;
        qreal rightPowerValue = 0.;

        if(searchPower <= 0) {
            leftDotIndex = peakPos;
            rightDotIndex = peakPos;
        }
        else {
            if(peakPos == 0) {
                leftDotIndex = peakPos;

                //search from peakPos+1 to right
                tmpPreviousOcc_Bw = pow(10, data[peakPos+1] / 10.)/1000;
                tmpCurrentOcc_Bw = pow(10, data[peakPos+1] / 10.)/1000;

                for(qint32 i = peakPos+2;i<num;i++) {
                    tmpCurrentOcc_Bw += pow(10, data[i] / 10.)/1000;

                    if(tmpPreviousOcc_Bw >= searchPower*2 ) {
                        rightDotIndex = i - 1;
                        break;
                    }
                    else if(tmpCurrentOcc_Bw == searchPower*2 ) {
                        rightDotIndex = i;
                        break;
                    }
                    else if(tmpPreviousOcc_Bw < searchPower*2  && tmpCurrentOcc_Bw > searchPower*2 ) {
                        rightDotIndex = i;
                        break;
                    }
                    if(i == num - 1) {
                        rightDotIndex = i;
                        break;
                    }
                    tmpPreviousOcc_Bw = tmpCurrentOcc_Bw;
                }
            }
            else if(peakPos == num - 1) {
                rightDotIndex = peakPos;

                //search from peakPos-1 to left
                tmpPreviousOcc_Bw = pow(10, data[peakPos-1] / 10.)/1000;
                tmpCurrentOcc_Bw = pow(10, data[peakPos-1] / 10.)/1000;

                for(qint32 i = peakPos-2;i>=0;i--) {
                    tmpCurrentOcc_Bw += pow(10, data[i] / 10.)/1000;

                    if(tmpPreviousOcc_Bw >= searchPower*2 ) {
                        leftDotIndex = i+1;
                        break;
                    }
                    else if(tmpCurrentOcc_Bw == searchPower*2 ) {
                        leftDotIndex = i;
                        break;
                    }
                    else if(tmpPreviousOcc_Bw < searchPower*2  && tmpCurrentOcc_Bw > searchPower*2 ) {
                        leftDotIndex = i;
                        break;
                    }
                    if(i == 0) {
                        leftDotIndex = i;
                        break;
                    }
                    tmpPreviousOcc_Bw = tmpCurrentOcc_Bw;
                }
            }
            else {
                //caculate peak left total power
                for(qint32 i = peakPos -1;i>=0;i--) {
                    leftPowerValue += pow(10, data[i] / 10.)/1000;
                }
                //caculate peak right total power
                for(qint32 i = peakPos + 1;i<num;i++) {
                    rightPowerValue += pow(10, data[i] / 10.)/1000;
                }

                if(leftPowerValue <= searchPower && rightPowerValue <= searchPower) {
                    leftDotIndex = 0;
                    rightDotIndex = num - 1;
                }
                else if(leftPowerValue <= searchPower && rightPowerValue > searchPower) {
                    leftDotIndex = 0;
                    //search right DotIndex
                    tmpPreviousOcc_Bw = pow(10, data[peakPos+1] / 10.)/1000;
                    tmpCurrentOcc_Bw = pow(10, data[peakPos+1] / 10.)/1000;

                    for(qint32 i = peakPos+2;i<num;i++) {
                        tmpCurrentOcc_Bw += pow(10, data[i] / 10.)/1000;

                        if(tmpPreviousOcc_Bw >= 2*searchPower - leftPowerValue  ) {
                            rightDotIndex = i-1;

                            if(tmpPreviousOcc_Bw > 2*searchPower - leftPowerValue) {
                                leftDotIndex = calibrateLeftDotIndex(peakPos,searchPower,leftPowerValue,data,tmpPreviousOcc_Bw);
                            }

                            break;
                        }
                        else if(tmpCurrentOcc_Bw == 2*searchPower - leftPowerValue  ) {
                            rightDotIndex = i;
                            break;
                        }
                        else if(tmpPreviousOcc_Bw < 2*searchPower - leftPowerValue  && tmpCurrentOcc_Bw > 2*searchPower - leftPowerValue ) {
                            rightDotIndex = i;
                            leftDotIndex = calibrateLeftDotIndex(peakPos,searchPower,leftPowerValue,data,tmpCurrentOcc_Bw);
                            break;
                        }
                        if(i == num - 1) {
                            rightDotIndex = num - 1;
                            break;
                        }
                        tmpPreviousOcc_Bw = tmpCurrentOcc_Bw;
                    }
                }
                else if(leftPowerValue > searchPower && rightPowerValue <= searchPower) {
                    rightDotIndex = num-1;
                    //search left DotIndex
                    tmpPreviousOcc_Bw = pow(10, data[peakPos-1] / 10.)/1000;
                    tmpCurrentOcc_Bw = pow(10, data[peakPos-1] / 10.)/1000;

                    for(qint32 i = peakPos-2;i>=0;i--) {
                        tmpCurrentOcc_Bw += pow(10, data[i] / 10.)/1000;

                        if(tmpPreviousOcc_Bw >= 2*searchPower - rightPowerValue  ) {
                            leftDotIndex = i+1;

                            if(tmpPreviousOcc_Bw > 2*searchPower - rightPowerValue) {
                                rightDotIndex = calibrateRightDotIndex(peakPos, num, searchPower, rightPowerValue, data, tmpPreviousOcc_Bw);
                            }
                            break;
                        }
                        else if(tmpCurrentOcc_Bw == 2*searchPower - rightPowerValue  ) {
                            leftDotIndex = i;
                            break;
                        }
                        else if(tmpPreviousOcc_Bw < 2*searchPower - rightPowerValue  && tmpCurrentOcc_Bw > 2*searchPower - rightPowerValue ) {
                            leftDotIndex = i;
                           if(tmpCurrentOcc_Bw > 2*searchPower - rightPowerValue) {
                               rightDotIndex = calibrateRightDotIndex(peakPos, num, searchPower, rightPowerValue, data, tmpCurrentOcc_Bw);
                           }
                            break;
                        }
                        if(i == 0) {
                            leftDotIndex = 0;
                            break;
                        }
                        tmpPreviousOcc_Bw = tmpCurrentOcc_Bw;
                    }
                }
                else if(leftPowerValue > searchPower && rightPowerValue > searchPower) {

                    if(leftPowerValue > rightPowerValue) {//search left first ,then calibrate right
                        //search left DotIndex
                        tmpPreviousOcc_Bw = pow(10, data[peakPos-1] / 10.)/1000;
                        tmpCurrentOcc_Bw = pow(10, data[peakPos-1] / 10.)/1000;

                        for(qint32 i = peakPos-2;i>=0;i--) {
                            tmpCurrentOcc_Bw += pow(10, data[i] / 10.)/1000;
                            if(tmpPreviousOcc_Bw >= searchPower  ) {
                                leftDotIndex = i+1;
                                if(tmpPreviousOcc_Bw >= 2*searchPower) {
                                    rightDotIndex = peakPos;
                                    break;
                                }
                                leftPowerValue = tmpPreviousOcc_Bw;
                                break;
                            }
                            else if(tmpCurrentOcc_Bw == searchPower  ) {
                                leftDotIndex = i;
                                leftPowerValue = tmpCurrentOcc_Bw;
                                break;
                            }
                            else if(tmpPreviousOcc_Bw < searchPower  && tmpCurrentOcc_Bw > searchPower ) {
                                leftDotIndex = i;
                                if(tmpCurrentOcc_Bw >= 2*searchPower) {
                                    //190428
                                    //rightDotIndex = peakPos;
                                    leftDotIndex = i + 1;
                                    leftPowerValue = tmpPreviousOcc_Bw;
                                    break;
                                }
                                leftPowerValue = tmpCurrentOcc_Bw;
                                break;
                            }
                            tmpPreviousOcc_Bw = tmpCurrentOcc_Bw;
                        }


                        //search right DotIndex
                        tmpPreviousOcc_Bw = pow(10, data[peakPos+1] / 10.)/1000;
                        tmpCurrentOcc_Bw = pow(10, data[peakPos+1] / 10.)/1000;

                        for(qint32 i = peakPos+2;i<num;i++) {
                            if(rightDotIndex == peakPos) break;
                            tmpCurrentOcc_Bw += pow(10, data[i] / 10.)/1000;
                            if(tmpPreviousOcc_Bw >= 2*searchPower - leftPowerValue  ) {
                                rightDotIndex = i-1;
                                //rightPowerValue = tmpPreviousOcc_Bw;
                                /*if(tmpPreviousOcc_Bw > 2*searchPower - leftPowerValue) {
                                    leftDotIndex = calibrateLeftDotIndex(peakPos,searchPower,leftPowerValue,data,tmpPreviousOcc_Bw);
                                }*/
                                break;
                            }
                            else if(tmpCurrentOcc_Bw == 2*searchPower - leftPowerValue  ) {
                                rightDotIndex = i;
                               //rightPowerValue = tmpCurrentOcc_Bw;
                                break;
                            }
                            else if(tmpPreviousOcc_Bw < 2*searchPower - leftPowerValue  && tmpCurrentOcc_Bw > 2*searchPower - leftPowerValue ) {
                                rightDotIndex = i;
                                //rightPowerValue = tmpCurrentOcc_Bw;
                                //leftDotIndex = calibrateLeftDotIndex(peakPos,searchPower,leftPowerValue,data,tmpCurrentOcc_Bw);
                                break;
                            }
                            tmpPreviousOcc_Bw = tmpCurrentOcc_Bw;
                        }
                    }
                    else if(leftPowerValue <= rightPowerValue) {//search right first ,then calibrate left
                        //search right DotIndex
                        tmpPreviousOcc_Bw = pow(10, data[peakPos+1] / 10.)/1000;
                        tmpCurrentOcc_Bw = pow(10, data[peakPos+1] / 10.)/1000;

                        for(qint32 i = peakPos+2;i<num;i++) {
                            tmpCurrentOcc_Bw += pow(10, data[i] / 10.)/1000;
                            if(tmpPreviousOcc_Bw >= searchPower  ) {
                                rightDotIndex = i-1;
                                if(tmpPreviousOcc_Bw >= 2*searchPower) {
                                    leftDotIndex = peakPos;
                                    break;
                                }
                                rightPowerValue = tmpPreviousOcc_Bw;
                                break;
                            }
                            else if(tmpCurrentOcc_Bw == searchPower  ) {
                                rightDotIndex = i;
                                rightPowerValue = tmpCurrentOcc_Bw;
                                break;
                            }
                            else if(tmpPreviousOcc_Bw < searchPower  && tmpCurrentOcc_Bw > searchPower ) {
                                rightDotIndex = i;
                                if(tmpCurrentOcc_Bw >= 2*searchPower) {
                                    //190428
                                    //leftDotIndex = peakPos;
                                    rightDotIndex = i - 1;
                                    rightPowerValue = tmpPreviousOcc_Bw;
                                    break;
                                }
                                rightPowerValue = tmpCurrentOcc_Bw;
                                break;
                            }
                            tmpPreviousOcc_Bw = tmpCurrentOcc_Bw;
                        }

                        //search left DotIndex
                        tmpPreviousOcc_Bw = pow(10, data[peakPos-1] / 10.)/1000;
                        tmpCurrentOcc_Bw = pow(10, data[peakPos-1] / 10.)/1000;

                        for(qint32 i = peakPos-2;i>=0;i--) {
                            if(leftDotIndex == peakPos) break;
                            tmpCurrentOcc_Bw += pow(10, data[i] / 10.)/1000;
                            if(tmpPreviousOcc_Bw >= 2*searchPower - rightPowerValue) {
                                leftDotIndex = i+1;
                                //leftPowerValue = tmpPreviousOcc_Bw;
                                /*if(tmpPreviousOcc_Bw > 2*searchPower - rightPowerValue) {
                                    rightDotIndex = calibrateRightDotIndex(peakPos, num, searchPower, rightPowerValue, data, tmpPreviousOcc_Bw);
                                }*/
                                break;
                            }
                            else if(tmpCurrentOcc_Bw == 2*searchPower - rightPowerValue) {
                                leftDotIndex = i;
                                //leftPowerValue = tmpCurrentOcc_Bw;
                                break;
                            }
                            else if(tmpPreviousOcc_Bw < 2*searchPower - rightPowerValue  && tmpCurrentOcc_Bw > 2*searchPower - rightPowerValue ) {
                                leftDotIndex = i;
                                //leftPowerValue = tmpCurrentOcc_Bw;
                                //rightDotIndex = calibrateRightDotIndex(peakPos, num, searchPower, rightPowerValue, data, tmpCurrentOcc_Bw);
                                break;
                            }
                            tmpPreviousOcc_Bw = tmpCurrentOcc_Bw;
                        }
                    }
                }
            }
        }
#endif
    }
    else if(mode == SA_XDB) {
        qint32 leftPeakPos[num],rightPeakPos[num];
        memset(leftPeakPos,0,sizeof(qint32)*num);
        memset(rightPeakPos,0,sizeof(qint32)*num);
        qint32 leftPeakNum = 0;
        qint32 rightPeakNum = 0;
        qint32 tempPeakPos = 0;

        //***********************find left Peak Array**********************
        tempPeakPos = peakPos;
        while(1) {
            if(tempPeakPos <= 3) break;

            for (qint32 i = (tempPeakPos - 2) ; i > 1; i--) {
                currentVal = data[i];
                if (i == (tempPeakPos - 2)) {
                    peakVal = currentVal ;
                    leftPeakPos[leftPeakNum] = i;
                  } else if (peakVal < currentVal) {
                    beforeVal =  data[i - 1];
                    afterVal =  data[i + 1];
                    if (currentVal >= beforeVal && currentVal >= afterVal) {
                        leftPeakPos[leftPeakNum] = i;
                        peakVal = currentVal;
                    }
                  }
              }
            tempPeakPos = leftPeakPos[leftPeakNum];
            leftPeakNum++;
        }
        //*****************************************************************

        //***********************find right Peak Array*********************
        tempPeakPos = peakPos;
        while(1) {
            if(tempPeakPos >= num - 2) break;

            for (qint32 i = (tempPeakPos + 2) ; i < num; i++) {
                currentVal = data[i];
                if (i == (tempPeakPos + 2)) {
                    peakVal = currentVal ;
                    rightPeakPos[rightPeakNum] = i;
                  } else if (peakVal < currentVal) {
                    beforeVal =  data[i - 1];
                    afterVal  =  data[i + 1];
                    if (currentVal >= beforeVal && currentVal >= afterVal) {
                        rightPeakPos[rightPeakNum] = i;
                        peakVal = currentVal;
                    }
                  }
              }
            tempPeakPos = rightPeakPos[rightPeakNum];
            rightPeakNum++;
        }
        //*****************************************************************

        //*****************caculate left and right dot index***************
        qint32 pos = 0;
        qreal dCZ = 0.;//record the distinct between the current value and the next value
        peakVal = data[peakPos];
        qreal leftCZ[leftPeakNum],rightCZ[rightPeakNum];
        memset(leftCZ,0,sizeof(qreal)*leftPeakNum);
        memset(rightCZ,0,sizeof(qreal)*rightPeakNum);
        //******left*******
        for(qint32 i = leftPeakNum-1;i>=0;i--)
        {
            pos = leftPeakPos[i];
            currentVal  = data[pos];
            if(currentVal-peakVal - dValue == 0.)
            {
                leftDotIndex = pos;
                break;
            }
            else
            {
                dCZ = fabs(currentVal - peakVal - dValue);
                /*if(dCZ - XDB_PRICISION <= 0.)
                {
                    leftDotIndex = pos;
                    break;
                }*/
#if 0
                if(i == 0) leftDotIndex = 0;
#else
                leftCZ[i] = dCZ;
                if(i == 0)
                {
                    qreal tmpMinCZ = leftCZ[0];
                    for(qint32 j = 1;j < leftPeakNum;j++)
                    {
                        if(leftCZ[j] - tmpMinCZ <= 0.)
                        {
                            tmpMinCZ = leftCZ[j];
                            leftDotIndex = leftPeakPos[j];
                        }
                    }
                }
#endif
            }
        }
        //*****************

        //******right******
        for(qint32 i = rightPeakNum-1;i>=0;i--)
        {
            pos = rightPeakPos[i];
            currentVal  = data[pos];

            if(currentVal-peakVal - dValue == 0.)
            {
                rightDotIndex = pos;
                break;
            }
            else
            {
                dCZ = fabs(currentVal - peakVal - dValue);
                /*if(dCZ - XDB_PRICISION <= 0.)
                {
                    rightDotIndex = pos;
                    break;
                }*/
#if 0
                if(i == 0) rightDotIndex = num - 1;
#else
                rightCZ[i] = dCZ;
                if(i == 0)
                {
                    qreal tmpMinCZ = rightCZ[0];
                    for(qint32 j = 1;j < rightPeakNum;j++)
                    {
                        if(rightCZ[j] - tmpMinCZ <= 0.)
                        {
                            tmpMinCZ = rightCZ[j];
                            rightDotIndex = rightPeakPos[j];
                        }
                    }
                }
#endif
            }
        }
        //*****************
        //*****************************************************************
    }
    dBW = (rightDotIndex - leftDotIndex)*globalUserVariable->gStepFreq;
    //dTotalPower = globalUserVariable->wattsToDbmCalculatorFunc(dTotalPower);
    return dBW;
}
