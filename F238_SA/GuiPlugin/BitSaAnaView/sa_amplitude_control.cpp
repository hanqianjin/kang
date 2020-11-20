#include "sa_amplitude_control.h"
#include "sa_stdafx.h"



sa_Amplitude_Control::sa_Amplitude_Control(user_variable &m_user_variable, user_limit &m_user_limit)
{
    globalUserVariable = &m_user_variable;
    globalUserLimit    = &m_user_limit;
}
sa_Amplitude_Control::~sa_Amplitude_Control()
{
    //delete globalUserLimit;
    //delete globalUserVariable;
}
void sa_Amplitude_Control::AmplitudeAttenControl()
{
    if(globalUserVariable->gAtten == SA_AUTO)
    {
        if(globalUserVariable->gPreamp == SA_OFF)
        {
            if(globalUserVariable->gRefLevel-25.>0.)           globalUserVariable->gAttenValue = 40.;
            else if(globalUserVariable->gRefLevel-20.>0.)      globalUserVariable->gAttenValue = 35.;
            else if(globalUserVariable->gRefLevel-15.>0.)      globalUserVariable->gAttenValue = 30.;
            else if(globalUserVariable->gRefLevel-10.>0.)      globalUserVariable->gAttenValue = 25.;
            else if(globalUserVariable->gRefLevel-5.>0.)       globalUserVariable->gAttenValue = 20.;
            else if(globalUserVariable->gRefLevel>0.)          globalUserVariable->gAttenValue = 15.;
            else if(globalUserVariable->gRefLevel+5.>0.)       globalUserVariable->gAttenValue = 10.;
            else if(globalUserVariable->gRefLevel+10.>0.)      globalUserVariable->gAttenValue = 5.;

            if(globalUserVariable->gRefLevel+10.<=0.)     globalUserVariable->gAttenValue = 0.;
        }
        else
        {
            if(globalUserVariable->gRefLevel+5.>0.&&globalUserVariable->gRefLevel<=0) globalUserVariable->gAttenValue = 30.;
            else if(globalUserVariable->gRefLevel+10.>0.)                             globalUserVariable->gAttenValue = 25.;
            else if(globalUserVariable->gRefLevel+15.>0.)                             globalUserVariable->gAttenValue = 20.;
            else if(globalUserVariable->gRefLevel+20.>0.)                             globalUserVariable->gAttenValue = 15.;
            else if(globalUserVariable->gRefLevel+25.>0.)                             globalUserVariable->gAttenValue = 10.;
            else if(globalUserVariable->gRefLevel+30.>0.)                             globalUserVariable->gAttenValue = 5.;


            if(globalUserVariable->gRefLevel+30.<=0)                                  globalUserVariable->gAttenValue = 0.;
        }
    }
    else
    {
        if(globalUserVariable->gPreamp == SA_OFF)
        {
            if(globalUserVariable->gAttenValue - 50. > 0.)
                globalUserVariable->gAttenValue = 50.;
        }
        else
        {
            if(globalUserVariable->gAttenValue - 30. > 0.)
                globalUserVariable->gAttenValue = 30.;
        }
    }
}
void sa_Amplitude_Control::AutoAttenTrackControl()
{
    //********topLevel and lowLevel are used to draw limit
    quint32 uFlag = 0;
    //Johnson 1122 Auto atten track
    if(globalUserVariable->gAutoAttenTrack == SA_ON) {
        double AMax = searchMaxAmplitude();
        if(fabs(AMax - globalUserVariable->gRefLevel) - 10. >0.) {
            globalUserVariable->gRefLevel = AMax + 10.;

            //limit the rang of RefLevel and RefOffset
            if (SPEC_AMPTD_MIN > globalUserVariable->gRefLevel) globalUserVariable->gRefLevel = SPEC_AMPTD_MIN;
            else if(globalUserVariable->gRefLevel  > SPEC_AMPTD_MAX) globalUserVariable->gRefLevel = SPEC_AMPTD_MAX;

             if (SPEC_AMPTD_MIN <= globalUserVariable->gRefLevel && globalUserVariable->gRefLevel  <= SPEC_AMPTD_MAX)    {
                 if(globalUserVariable->gRefOffset < SPEC_AMPTD_MIN - globalUserVariable->gRefLevel)
                     globalUserVariable->gRefOffset = SPEC_AMPTD_MIN - globalUserVariable->gRefLevel;
                 else if( globalUserVariable->gRefOffset > SPEC_AMPTD_MAX - globalUserVariable->gRefLevel)
                     globalUserVariable->gRefOffset = SPEC_AMPTD_MAX - globalUserVariable->gRefLevel;
             }

            //**************other relative control****************
            globalUserVariable->topLevel = globalUserVariable->gRefLevel+globalUserVariable->gRefOffset;
            globalUserVariable->lowLevel = globalUserVariable->topLevel - GRID_NUM_Y_TICKS*globalUserVariable->gScaleDiv;

            if(globalUserVariable->gRefLevel>0.)
            {
              if(globalUserVariable->gPreamp == SA_ON)
              {
                  globalUserVariable->gPreamp = SA_OFF;
                  SA_sm_config_sweep->Preamp = globalUserVariable->gPreamp;
#if USABLE
                  SA_sm_config_sweep->uisPreampChangedItself = 0;
#endif
                  uFlag |= IXS_SA_Preamp;
              }
            }

            AmplitudeAttenControl();
            SA_sm_config_sweep->RefLevel = globalUserVariable->gRefLevel;
            uFlag |= IXS_SA_RefLevel;

            SA_sm_config_sweep->attenValue = globalUserVariable->gAttenValue;
            uFlag |= IXS_SA_AttenSelect;

            SA_Set_config_flag(IXT_SA_ConfigSweep,uFlag);
            //****************************************************
        }
    }
}
/**
 * @brief search the max Amplitude
 * @return Max Amplitude
 */
qreal sa_Amplitude_Control::searchMaxAmplitude()
{
    double AMax = globalUserVariable->gOriginalMeasureVal[0];
    for (int k = 1; k < globalUserVariable->gSweepTracePoint; k++) {
        if (AMax < globalUserVariable->gOriginalMeasureVal[k]) {
            AMax = globalUserVariable->gOriginalMeasureVal[k];
          }
      }
    return AMax;
}
/**
 * @brief search the Min Amplitude
 * @return Min Amplitude
 */
qreal sa_Amplitude_Control::searchMinAmplitude()
{
    double AMin = globalUserVariable->gOriginalMeasureVal[0];
    for (int k = 1; k < globalUserVariable->gSweepTracePoint; k++) {
        if (AMin > globalUserVariable->gOriginalMeasureVal[k]) {
            AMin = globalUserVariable->gOriginalMeasureVal[k];
          }
      }
    return AMin;
}
/**
 * @brief sa_Amplitude_Control::setRefLevelRelativePara
 * @param topLevel
 * @param lowLevel
 */
void sa_Amplitude_Control::setRefLevelRelativePara(qreal &topLevel,qreal &lowLevel)
{
    topLevel = globalUserVariable->gRefLevel+globalUserVariable->gRefOffset;
    lowLevel = topLevel - GRID_NUM_Y_TICKS*globalUserVariable->gScaleDiv;
}
/**
 * @brief sa_Amplitude_Control::setScalDivRelativePara
 * @param topLevel
 * @param lowLevel
 */
void sa_Amplitude_Control::setScalDivRelativePara(qreal &topLevel,qreal &lowLevel)
{
    topLevel = globalUserVariable->gRefLevel+globalUserVariable->gRefOffset;
    lowLevel = topLevel - GRID_NUM_Y_TICKS*globalUserVariable->gScaleDiv;
}
/**
 * @brief sa_Amplitude_Control::setAmptUnit
 * @param ampUnit
 */
void sa_Amplitude_Control::setAmptUnit(qint32 ampUnit)
{
    globalUserVariable->gAmptdUnit = ampUnit;
}
/**
 * @brief sa_Amplitude_Control::setRefOffsetRelativePara
 * @param topLevel
 * @param lowLevel
 */
void sa_Amplitude_Control::setRefOffsetRelativePara(qreal &topLevel,qreal &lowLevel)
{
    topLevel = globalUserVariable->gRefLevel+globalUserVariable->gRefOffset;
    lowLevel = topLevel - GRID_NUM_Y_TICKS*globalUserVariable->gScaleDiv;
}
