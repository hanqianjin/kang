#include "sa_parasaveload.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include "sa_stdafx.h"
#include <time.h>
#include <QTime>
#include "msgNoticeCode.h"
#define PADD 1

paraSaveLoad::paraSaveLoad(user_limit &m_user_limit, user_variable &m_user_variable)
{
    globalUserLimit    = &m_user_limit;
    globalUserVariable = &m_user_variable;

    //Init related variable
    bSpanModeParamNull                 = true;
    bChnlPowerModeParamNull            = true;
    bOccupiedModeParamNull             = true;
    bACPModeParamNull                  = true;
    bMultiACPModeParamNull             = true;
    bSpectrumEmissionMaskModeParamNull = true;
    bSpuriousEmissionMaskModeParamNull = true;
    bFieldStrengthModeParamNull        = true;
    bDemodulationModeParamNull         = true;

    //Init all struct
    paraInit_AllMode();
    paraInit_MeasureMode();

    //Init State and Data struct Johnson 190701
    paraInit_StateFile();
    paraInit_StateAndDataFile();
}
//****************************************************
//*************used to project initialize*************
//****************************************************
bool paraSaveLoad::setVariable(_FILE_SAVE_LOAD_VARIABLE_ *pVariable, uint workMode)
{
    return loadVariable(pVariable,workMode);
}

/**
  * @brief paraSaveLoad::preStateSave
  * @param itype
  */
 bool paraSaveLoad::preStateSave(qint32 itype)
 {
     //********Save preset status flag
     FILE *pFile;
     pFile = fopen("SA_state.pres","wb");
     globalUserVariable->startPreset = itype;
     StartStatusFlag.startMode   = globalUserVariable->startMode;
     StartStatusFlag.startPreset = globalUserVariable->startPreset;

     if(!pFile){
         qDebug()<<"Open file fail!";
         setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_PreStateFile_Write);
         errorOutput();

         return false;
     }

     fwrite(&StartStatusFlag,sizeof(_START_STATUS_FLAG_),1,pFile);
     fflush(pFile);
     fclose(pFile);
     qDebug()<<"Save status flag success!";
     return true;
 }

/**
 * @brief paraSaveLoad::allModeParaSave
 * @param itype 0 Preset Status,1 Last Status,2 User Status
 * @return true success,false fail
 */
bool paraSaveLoad::allModeParaSave(quint32 currentMode,qint32 itype)
{
    //********Save plugin parameters
    time_t timep;
    time(&timep);
    qDebug()<<"Start time is "<<asctime(gmtime(&timep));

    /*QTime current_time = QTime::currentTime();
    qint32 hour = current_time.hour();//当前的小时
    qint32 minute = current_time.minute();//当前的分
    qint32 second = current_time.second();//当前的秒
    qint32 msec = current_time.msec();//当前的毫秒
    qDebug()<<"Start time is "<<msec;*/

    if(itype == SA_PRESET_PARA) return false;

    FILE *pFile;
    if(itype == SA_PRESET_PARA)    pFile = fopen("SA_default.cond","wb");
    else if(itype == SA_LAST_PARA) pFile = fopen("SA_last.cond","wb");
    else if(itype == SA_USER_PARA) pFile = fopen("SA_user.cond","wb");

    //************local para copy to gAllMode_FileSaveLoadParam
    paraSave(currentMode);

    memcpy(&(gAllMode_FileSaveLoadParam.pSpanModeParam),&gSpanModeParam,sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&(gAllMode_FileSaveLoadParam.pChnlPowerModeParam),&gChnlPowerModeParam,sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&(gAllMode_FileSaveLoadParam.pOccupiedModeParam),&gOccupiedModeParam,sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&(gAllMode_FileSaveLoadParam.pACPModeParam),&gACPModeParam,sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&(gAllMode_FileSaveLoadParam.pMultiACPModeParam),&gMultiACPModeParam,sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&(gAllMode_FileSaveLoadParam.pSpectrumEmissionMaskModeParam),&gSpectrumEmissionMaskModeParam,sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&(gAllMode_FileSaveLoadParam.pSpuriousEmissionMaskModeParam),&gSpuriousEmissionMaskModeParam,sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&(gAllMode_FileSaveLoadParam.pFieldStrengthModeParam),&gFieldStrengthModeParam,sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&(gAllMode_FileSaveLoadParam.pDemodulationModeParam),&gDemodulationModeParam,sizeof(_FILE_SAVE_LOAD_VARIABLE_));

    gAllMode_FileSaveLoadParam.mSaveLoad_CurrentMode = globalUserVariable->currentMode;
    gAllMode_FileSaveLoadParam.gCenterFreq           = globalUserVariable->gCenterFreq;
    gAllMode_FileSaveLoadParam.mSaveLoad_MeasureMode = SA_sm_config_measure->MeasureMode;
    gAllMode_FileSaveLoadParam.FullStatus            = globalUserVariable->FullStatus;
    gAllMode_FileSaveLoadParam.leftHideChecked       = globalUserVariable->pbLeftHideChecked;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bACPModeParamNull                  = bACPModeParamNull;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bChnlPowerModeParamNull            = bChnlPowerModeParamNull;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bDemodulationModeParamNull         = bDemodulationModeParamNull;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bFieldStrengthModeParamNull        = bFieldStrengthModeParamNull;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bMultiACPModeParamNull             = bMultiACPModeParamNull;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bOccupiedModeParamNull             = bOccupiedModeParamNull;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bSpanModeParamNull                 = bSpanModeParamNull;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bSpectrumEmissionMaskModeParamNull = bSpectrumEmissionMaskModeParamNull;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bSpuriousEmissionMaskModeParamNull = bSpuriousEmissionMaskModeParamNull;

#if !RESERVE_0327
    gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gCFFreq = globalUserVariable->gCFFreq;
    gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gfreqOffset = globalUserVariable->gfreqOffset;
    gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gLastSpanFreq = globalUserVariable->gLastSpanFreq;
    gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gSpanFreq = globalUserVariable->gSpanFreq;
    gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gSpanMode = globalUserVariable->gSpanMode;
    gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gStepFreq = globalUserVariable->gStepFreq;
    gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gZeroSpanAction = globalUserVariable->gZeroSpanAction;

    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gAmptdUnit = globalUserVariable->gAmptdUnit;
    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gAtten = globalUserVariable->gAtten;
    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gAttenValue = globalUserVariable->gAttenValue;
    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gAutoAttenTrack = globalUserVariable->gAutoAttenTrack;
    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gPreamp = globalUserVariable->gPreamp;
    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gRefLevel = globalUserVariable->gRefLevel;
    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gRefOffset = globalUserVariable->gRefOffset;
    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gScaleDiv = globalUserVariable->gScaleDiv;

    gAllMode_FileSaveLoadParam.gConfig_BW.gAutoRbw = globalUserVariable->gAutoRbw;
    gAllMode_FileSaveLoadParam.gConfig_BW.gAutoVbw = globalUserVariable->gAutoVbw;
    gAllMode_FileSaveLoadParam.gConfig_BW.gIFMode = globalUserVariable->uIFMode;
    gAllMode_FileSaveLoadParam.gConfig_BW.gRbw = globalUserVariable->gRbw;
    gAllMode_FileSaveLoadParam.gConfig_BW.gVbw = globalUserVariable->gVbw;
    gAllMode_FileSaveLoadParam.gConfig_BW.gVbwtoRbw = globalUserVariable->gVbwtoRbw;

    memcpy(gAllMode_FileSaveLoadParam.gConfig_Trace.gAverageCount,globalUserVariable->gAverageCount,sizeof(qint32)*NUM_TRACE);
    gAllMode_FileSaveLoadParam.gConfig_Trace.gDetectorMode = globalUserVariable->gDetectorMode;
    gAllMode_FileSaveLoadParam.gConfig_Trace.gTmpDetectorMode = globalUserVariable->gTmpDetectorMode;
    memcpy(gAllMode_FileSaveLoadParam.gConfig_Trace.gTraceAverage,globalUserVariable->gTraceAverage,sizeof(qint32)*NUM_TRACE);
    gAllMode_FileSaveLoadParam.gConfig_Trace.gTraceSelect = globalUserVariable->gTraceSelect;
    memcpy(gAllMode_FileSaveLoadParam.gConfig_Trace.gTraceType,globalUserVariable->gTraceType,sizeof(qint32)*NUM_TRACE);
    memcpy(gAllMode_FileSaveLoadParam.gConfig_Trace.gTraceView,globalUserVariable->gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(gAllMode_FileSaveLoadParam.gConfig_Trace.gViewAction,globalUserVariable->gViewAction,sizeof(qint32)*NUM_TRACE);
#endif
    //****************

    if(!pFile){
        qDebug()<<"Open file fail!";
        if(itype == SA_PRESET_PARA)    setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_DefaultStateConfigFile_Write);
        else if(itype == SA_LAST_PARA) setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_LastStateConfigFile_Write);
        else if(itype == SA_USER_PARA) setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_UserStateConfigFile_Write);
        errorOutput();

        return false;
    }

    fwrite(&gAllMode_FileSaveLoadParam,sizeof(_ALLMODE_FILE_SAVE_LOAD_),1,pFile);
    fflush(pFile);
    fclose(pFile);
    qDebug()<<"Save variable success!";

    time(&timep);
    qDebug()<<"Stop time is "<<asctime(gmtime(&timep));

    /*current_time =QTime::currentTime();
    hour = current_time.hour();//当前的小时
    minute = current_time.minute();//当前的分
    second = current_time.second();//当前的秒
    msec = current_time.msec();//当前的毫秒
    qDebug()<<"Stop time is "<<msec;*/

    return true;
}

/**
 * @brief paraSaveLoad::allModeParaLoad
 * @param itype 0 Preset Status,1 Last Status,2 User Status
 * @return true success,false fail
 */
bool paraSaveLoad::allModeParaLoad(qint32 presetFlag,qint32 itype)
{
    FILE *pFile = NULL;
    qint64 retLong = 0;

    if(!presetFlag)
    {
        //preset status flag
        pFile = fopen("SA_state.pres","rb");
        if(!pFile){
            qDebug()<<"Open file fail!";
            setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_PreStateFile_Read);
            errorOutput();

            return false;
        }
        fseek(pFile,0,SEEK_END);
        retLong = ftell(pFile);
        if(!retLong || retLong != sizeof(_START_STATUS_FLAG_)){
            qDebug()<<"The file is null!";
            setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_PreStateFile_LengthMatch);
            errorOutput();

            fclose(pFile);
            return false;
        }
        fseek(pFile,0,SEEK_SET);
        fread(&StartStatusFlag,sizeof(_START_STATUS_FLAG_),1,pFile);
        fclose(pFile);
        qDebug()<<"Load status flag success!";
        globalUserVariable->startMode   = StartStatusFlag.startMode;
        globalUserVariable->startPreset = StartStatusFlag.startPreset;

        //judge if the preStart module is current module(currentModule index is SA_MODULE(0))
        if(SA_MODULE != globalUserVariable->startMode) sm_startflag->startedflag = START_FLAG;
    }


    if(!presetFlag)
    {
        //load plugin parameters
        if(globalUserVariable->startPreset == SA_PRESET_PARA)    pFile = fopen("SA_default.cond","rb");
        else if(globalUserVariable->startPreset == SA_LAST_PARA) pFile = fopen("SA_last.cond","rb");
        else if(globalUserVariable->startPreset == SA_USER_PARA) pFile = fopen("SA_user.cond","rb");
    }
    else
    {
        pFile = fopen("SA_default.cond","rb");
    }

    if(!pFile){
        qDebug()<<"Open file fail!";
        if(!presetFlag)
        {
            if(globalUserVariable->startPreset == SA_PRESET_PARA)    setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_DefaultStateConfigFile_Read);
            else if(globalUserVariable->startPreset == SA_LAST_PARA) setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_LastStateConfigFile_Read);
            else if(globalUserVariable->startPreset == SA_USER_PARA) setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_UserStateConfigFile_Read);
        }
        else
        {
            setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_DefaultStateConfigFile_Read);
        }
        errorOutput();

        return false;
    }
    fseek(pFile,0,SEEK_END);
    retLong = ftell(pFile);
    if(!retLong || retLong != sizeof(_ALLMODE_FILE_SAVE_LOAD_)){
        qDebug()<<"The file is null!";
        if(!presetFlag)
        {
            if(globalUserVariable->startPreset == SA_PRESET_PARA)    setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_DefaultStateConfigFile_LengthMatch);
            else if(globalUserVariable->startPreset == SA_LAST_PARA) setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_LastStateConfigFile_LengthMatch);
            else if(globalUserVariable->startPreset == SA_USER_PARA) setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_UserStateConfigFile_LengthMatch);
        }
        else
        {
            setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_DefaultStateConfigFile_LengthMatch);
        }
        errorOutput();

        fclose(pFile);
        return false;
    }
    fseek(pFile,0,SEEK_SET);
    fread(&gAllMode_FileSaveLoadParam,sizeof(_ALLMODE_FILE_SAVE_LOAD_),1,pFile);
    fclose(pFile);
    qDebug()<<"Load variable success!";

    globalUserVariable->currentMode       = gAllMode_FileSaveLoadParam.mSaveLoad_CurrentMode;
    globalUserVariable->gCenterFreq       = gAllMode_FileSaveLoadParam.gCenterFreq;
    SA_sm_config_measure->MeasureMode     = gAllMode_FileSaveLoadParam.mSaveLoad_MeasureMode;
    globalUserVariable->FullStatus        = gAllMode_FileSaveLoadParam.FullStatus;
    globalUserVariable->pbLeftHideChecked = gAllMode_FileSaveLoadParam.leftHideChecked;

    switch (globalUserVariable->currentMode) {
    case SA_SPAN_MODE:                   fileSaveLoadParaToglobalUserVariable(&gAllMode_FileSaveLoadParam.pSpanModeParam);                 break;
    case SA_CHNLPOWER_MEASURE_MODE:      fileSaveLoadParaToglobalUserVariable(&gAllMode_FileSaveLoadParam.pChnlPowerModeParam);            break;
    case SA_ACP_MEASURE_MODE:            fileSaveLoadParaToglobalUserVariable(&gAllMode_FileSaveLoadParam.pACPModeParam);                  break;
    case SA_OCCUPIED_BW_MEASURE_MODE:    fileSaveLoadParaToglobalUserVariable(&gAllMode_FileSaveLoadParam.pOccupiedModeParam);             break;
    case SA_SPECTRUM_EMISSION_MASK_MODE: fileSaveLoadParaToglobalUserVariable(&gAllMode_FileSaveLoadParam.pSpectrumEmissionMaskModeParam); break;
    case SA_MULTI_ACP_MODE:              fileSaveLoadParaToglobalUserVariable(&gAllMode_FileSaveLoadParam.pMultiACPModeParam);             break;
    case SA_SPURIOUS_EMISSION_MASK_MODE: fileSaveLoadParaToglobalUserVariable(&gAllMode_FileSaveLoadParam.pSpuriousEmissionMaskModeParam); break;
    case SA_FIELD_STRENGTH_MODE:         fileSaveLoadParaToglobalUserVariable(&gAllMode_FileSaveLoadParam.pFieldStrengthModeParam);        break;
    case SA_DEMODULATION_MODE:           fileSaveLoadParaToglobalUserVariable(&gAllMode_FileSaveLoadParam.pDemodulationModeParam);         break;
    default:                                                                                                                               break;
    }

    //*********gAllMode_FileSaveLoadParam to local para and set every mode's flag
    memcpy(&gSpanModeParam,&(gAllMode_FileSaveLoadParam.pSpanModeParam),sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&gChnlPowerModeParam,&(gAllMode_FileSaveLoadParam.pChnlPowerModeParam),sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&gOccupiedModeParam,&(gAllMode_FileSaveLoadParam.pOccupiedModeParam),sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&gACPModeParam,&(gAllMode_FileSaveLoadParam.pACPModeParam),sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&gMultiACPModeParam,&(gAllMode_FileSaveLoadParam.pMultiACPModeParam),sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&gSpectrumEmissionMaskModeParam,&(gAllMode_FileSaveLoadParam.pSpectrumEmissionMaskModeParam),sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&gSpuriousEmissionMaskModeParam,&(gAllMode_FileSaveLoadParam.pSpuriousEmissionMaskModeParam),sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&gFieldStrengthModeParam,&(gAllMode_FileSaveLoadParam.pFieldStrengthModeParam),sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    memcpy(&gDemodulationModeParam,&(gAllMode_FileSaveLoadParam.pDemodulationModeParam),sizeof(_FILE_SAVE_LOAD_VARIABLE_));

    bSpanModeParamNull                 = gAllMode_FileSaveLoadParam.pMeasurParaStatus.bSpanModeParamNull;
    bChnlPowerModeParamNull            = gAllMode_FileSaveLoadParam.pMeasurParaStatus.bChnlPowerModeParamNull;
    bOccupiedModeParamNull             = gAllMode_FileSaveLoadParam.pMeasurParaStatus.bOccupiedModeParamNull;
    bACPModeParamNull                  = gAllMode_FileSaveLoadParam.pMeasurParaStatus.bACPModeParamNull;
    bMultiACPModeParamNull             = gAllMode_FileSaveLoadParam.pMeasurParaStatus.bMultiACPModeParamNull;
    bSpectrumEmissionMaskModeParamNull = gAllMode_FileSaveLoadParam.pMeasurParaStatus.bSpectrumEmissionMaskModeParamNull;
    bSpuriousEmissionMaskModeParamNull = gAllMode_FileSaveLoadParam.pMeasurParaStatus.bSpuriousEmissionMaskModeParamNull;
    bFieldStrengthModeParamNull        = gAllMode_FileSaveLoadParam.pMeasurParaStatus.bFieldStrengthModeParamNull;
    bDemodulationModeParamNull         = gAllMode_FileSaveLoadParam.pMeasurParaStatus.bDemodulationModeParamNull;

#if !RESERVE_0327
    globalUserVariable->gCFFreq = gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gCFFreq;
    globalUserVariable->gfreqOffset = gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gfreqOffset;
    globalUserVariable->gLastSpanFreq = gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gLastSpanFreq;
    globalUserVariable->gSpanFreq = gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gSpanFreq;
    globalUserVariable->gSpanMode = gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gSpanMode;
    globalUserVariable->gStepFreq = gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gStepFreq;
    globalUserVariable->gZeroSpanAction = gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gZeroSpanAction;

    globalUserVariable->gAmptdUnit = gAllMode_FileSaveLoadParam.gConfig_Amplitude.gAmptdUnit;
    globalUserVariable->gAtten = gAllMode_FileSaveLoadParam.gConfig_Amplitude.gAtten;
    globalUserVariable->gAttenValue = gAllMode_FileSaveLoadParam.gConfig_Amplitude.gAttenValue;
    globalUserVariable->gAutoAttenTrack = gAllMode_FileSaveLoadParam.gConfig_Amplitude.gAutoAttenTrack;
    globalUserVariable->gPreamp = gAllMode_FileSaveLoadParam.gConfig_Amplitude.gPreamp;
    globalUserVariable->gRefLevel = gAllMode_FileSaveLoadParam.gConfig_Amplitude.gRefLevel;
    globalUserVariable->gRefOffset = gAllMode_FileSaveLoadParam.gConfig_Amplitude.gRefOffset;
    globalUserVariable->gScaleDiv = gAllMode_FileSaveLoadParam.gConfig_Amplitude.gScaleDiv;

    globalUserVariable->gAutoRbw = gAllMode_FileSaveLoadParam.gConfig_BW.gAutoRbw;
    globalUserVariable->gAutoVbw = gAllMode_FileSaveLoadParam.gConfig_BW.gAutoVbw;
    globalUserVariable->uIFMode = gAllMode_FileSaveLoadParam.gConfig_BW.gIFMode;
    globalUserVariable->gRbw = gAllMode_FileSaveLoadParam.gConfig_BW.gRbw;
    globalUserVariable->gVbw = gAllMode_FileSaveLoadParam.gConfig_BW.gVbw;
    globalUserVariable->gVbwtoRbw = gAllMode_FileSaveLoadParam.gConfig_BW.gVbwtoRbw;

    memcpy(globalUserVariable->gAverageCount,gAllMode_FileSaveLoadParam.gConfig_Trace.gAverageCount,sizeof(qint32)*NUM_TRACE);
    globalUserVariable->gDetectorMode = gAllMode_FileSaveLoadParam.gConfig_Trace.gDetectorMode;
    globalUserVariable->gTmpDetectorMode = gAllMode_FileSaveLoadParam.gConfig_Trace.gTmpDetectorMode;
    memcpy(globalUserVariable->gTraceAverage,gAllMode_FileSaveLoadParam.gConfig_Trace.gTraceAverage,sizeof(qint32)*NUM_TRACE);
    globalUserVariable->gTraceSelect = gAllMode_FileSaveLoadParam.gConfig_Trace.gTraceSelect;
    memcpy(globalUserVariable->gTraceType,gAllMode_FileSaveLoadParam.gConfig_Trace.gTraceType,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gTraceView,gAllMode_FileSaveLoadParam.gConfig_Trace.gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gViewAction,gAllMode_FileSaveLoadParam.gConfig_Trace.gViewAction,sizeof(qint32)*NUM_TRACE);
#endif
    //***************

    return true;
}
//**********************************************************************
//*********Johnson 0802*************************************************
//*************used to download variables of previouse mode*************
//**********************************************************************
bool paraSaveLoad::loadVariable(_FILE_SAVE_LOAD_VARIABLE_ *pVariable, uint workMode)
{
    //Write FilegPowersensorExtOffset
    /*FILE *pFile = fopen("variable.ini","w");//mode "w":first clear all the file content ,then write data to the file
    fwrite(pVariable,1,sizeof(_FILE_SAVE_LOAD_VARIABLE_),pFile);
    fflush(pFile);
    fclose(pFile);*/
    FILE *pFile;
    if(workMode == SA_SPAN_MODE)                        pFile = fopen("SpanMode_Variable.ini","r");
    else if(workMode == SA_CHNLPOWER_MEASURE_MODE)      pFile = fopen("ChnalPower_MeasureMode_Variable.ini","r");
    else if(workMode == SA_ACP_MEASURE_MODE)            pFile = fopen("ACP_MeasureMode_Variable.ini","r");
    else if(workMode == SA_OCCUPIED_BW_MEASURE_MODE)    pFile = fopen("OccupiedBW_MeasureMode_Variable.ini","r");
    else if(workMode == SA_SPECTRUM_EMISSION_MASK_MODE) pFile = fopen("SpectrumEmissionMaskMode_Variable.ini","r");
    else if(workMode == SA_MULTI_ACP_MODE)              pFile = fopen("MultiACPMode_Variable.ini","r");
    else if(workMode == SA_SPURIOUS_EMISSION_MASK_MODE) pFile = fopen("SpuriousEmissionMask_Variable.ini","r");
    else if(workMode == SA_FIELD_STRENGTH_MODE)         pFile = fopen("FieldStrengthMode_Variable.ini","r");

    if(!pFile){
        qDebug()<<"Open file fail!";

        if(workMode != SA_SPAN_MODE) {
            globalUserVariable->gSpanFreq = 50000000LL;
            globalUserVariable->adjustFreqBySpan(globalUserVariable->gSpanFreq);
            globalUserVariable->stepFreqCalculatorFunc();
            globalUserVariable->markerPositionReCalculatorFunc();
        }
        return false;
    }
    fseek(pFile,0,SEEK_END);
    qint64 reLong = ftell(pFile);
    if(!reLong || reLong != sizeof(_FILE_SAVE_LOAD_VARIABLE_)){
        qDebug()<<"The file is null!";
        fclose(pFile);
        return false;
    }
    fseek(pFile,0,SEEK_SET);
    //fread(pVariable,1,sizeof(_FILE_SAVE_LOAD_VARIABLE_),pFile);
    fread(pVariable,sizeof(_FILE_SAVE_LOAD_VARIABLE_),1,pFile);
    fclose(pFile);
    qDebug()<<"Load variable success!";

    fileSaveLoadParaToglobalUserVariable(pVariable);

    return true;
}
//****************************************************************
//*********Johnson 0802*******************************************
//*************used to save variables of current mode*************
//****************************************************************
bool paraSaveLoad::saveVariable(_FILE_SAVE_LOAD_VARIABLE_ *pVariable, uint workMode)
{
    QDir dir(QString("."));
    QString path = dir.absolutePath();
    QString savePath;
    if(workMode == SA_SPAN_MODE)                        savePath = QString("%1%2").arg(path).arg("/SpanMode_Variable.ini");
    else if(workMode == SA_CHNLPOWER_MEASURE_MODE)      savePath = QString("%1%2").arg(path).arg("/ChnalPower_MeasureMode_Variable.ini");
    else if(workMode == SA_ACP_MEASURE_MODE)            savePath = QString("%1%2").arg(path).arg("/ACP_MeasureMode_Variable.ini");
    else if(workMode == SA_OCCUPIED_BW_MEASURE_MODE)    savePath = QString("%1%2").arg(path).arg("/OccupiedBW_MeasureMode_Variable.ini");
    else if(workMode == SA_SPECTRUM_EMISSION_MASK_MODE) savePath = QString("%1%2").arg(path).arg("/SpectrumEmissionMaskMode_Variable.ini");
    else if(workMode == SA_MULTI_ACP_MODE)              savePath = QString("%1%2").arg(path).arg("/MultiACPMode_Variable.ini");
    else if(workMode == SA_SPURIOUS_EMISSION_MASK_MODE) savePath = QString("%1%2").arg(path).arg("/SpuriousEmissionMask_Variable.ini");
    else if(workMode == SA_FIELD_STRENGTH_MODE)         savePath = QString("%1%2").arg(path).arg("/FieldStrengthMode_Variable.ini");

    globalUserVariableTofileSaveLoadPara(pVariable);

    QFile f(savePath);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Truncate)){   //QIODevice::Truncate   open the file and clear its content
        qDebug()<<"save variable fail!";
        return false;
    }
    f.write((char *)pVariable,sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    f.close();
    qDebug()<<"save variable success!";

    //******Read File
    /*f.open(QIODevice::ReadOnly);
    f.read((char *)&pVariable,sizeof(_FILE_SAVE_LOAD_VARIABLE_));
    f.close();*/

    return true;
}

/**
 * @brief paraSaveLoad::paraInit_StateFile
 * @return
 * @date 190701
 * @author Johnson
 */
void paraSaveLoad::paraInit_StateFile()
{
    measureStateTofileSaveLoadPara(&gSpanModeState);
    measureStateTofileSaveLoadPara(&gChnlPowerModeState);
    measureStateTofileSaveLoadPara(&gOccupiedModeState);
    measureStateTofileSaveLoadPara(&gACPModeState);
    measureStateTofileSaveLoadPara(&gMultiACPModeState);
    measureStateTofileSaveLoadPara(&gSpectrumEmissionMaskModeState);
    measureStateTofileSaveLoadPara(&gSpuriousEmissionMaskModeState);
    measureStateTofileSaveLoadPara(&gFieldStrengthModeState);
    measureStateTofileSaveLoadPara(&gDemodulationModeState);

    measureStateTofileSaveLoadPara(&gAllMode_State.pSpanModeParam);
    measureStateTofileSaveLoadPara(&gAllMode_State.pChnlPowerModeParam);
    measureStateTofileSaveLoadPara(&gAllMode_State.pOccupiedModeParam);
    measureStateTofileSaveLoadPara(&gAllMode_State.pACPModeParam);
    measureStateTofileSaveLoadPara(&gAllMode_State.pMultiACPModeParam);
    measureStateTofileSaveLoadPara(&gAllMode_State.pSpectrumEmissionMaskModeParam);
    measureStateTofileSaveLoadPara(&gAllMode_State.pSpuriousEmissionMaskModeParam);
    measureStateTofileSaveLoadPara(&gAllMode_State.pFieldStrengthModeParam);
    measureStateTofileSaveLoadPara(&gAllMode_State.pDemodulationModeParam);
    gAllMode_State.mSaveLoad_CurrentMode = globalUserVariable->currentMode;
    gAllMode_State.gCenterFreq           = globalUserVariable->gCenterFreq;
    gAllMode_State.gConfig_ShareMem.uAllSweepCompleteFlag = SA_sm_config_sweep->uAllSweepCompleteFlag;
    gAllMode_State.gConfig_ShareMem.uIFMode = globalUserVariable->uIFMode;
#if !RESERVE_0327
    gAllMode_State.gConfig_FreqSpan.gCFFreq = globalUserVariable->gCFFreq;
    gAllMode_State.gConfig_FreqSpan.gfreqOffset = globalUserVariable->gfreqOffset;
    gAllMode_State.gConfig_FreqSpan.gLastSpanFreq = globalUserVariable->gLastSpanFreq;
    gAllMode_State.gConfig_FreqSpan.gSpanFreq = globalUserVariable->gSpanFreq;
    gAllMode_State.gConfig_FreqSpan.gSpanMode = globalUserVariable->gSpanMode;
    gAllMode_State.gConfig_FreqSpan.gStepFreq = globalUserVariable->gStepFreq;
    gAllMode_State.gConfig_FreqSpan.gZeroSpanAction = globalUserVariable->gZeroSpanAction;

    gAllMode_State.gConfig_Amplitude.gAmptdUnit = globalUserVariable->gAmptdUnit;
    gAllMode_State.gConfig_Amplitude.gAtten = globalUserVariable->gAtten;
    gAllMode_State.gConfig_Amplitude.gAttenValue = globalUserVariable->gAttenValue;
    gAllMode_State.gConfig_Amplitude.gAutoAttenTrack = globalUserVariable->gAutoAttenTrack;
    gAllMode_State.gConfig_Amplitude.gPreamp = globalUserVariable->gPreamp;
    gAllMode_State.gConfig_Amplitude.gRefLevel = globalUserVariable->gRefLevel;
    gAllMode_State.gConfig_Amplitude.gRefOffset = globalUserVariable->gRefOffset;
    gAllMode_State.gConfig_Amplitude.gScaleDiv = globalUserVariable->gScaleDiv;

    gAllMode_State.gConfig_BW.gAutoRbw = globalUserVariable->gAutoRbw;
    gAllMode_State.gConfig_BW.gAutoVbw = globalUserVariable->gAutoVbw;
    gAllMode_State.gConfig_BW.gIFMode = globalUserVariable->uIFMode;
    gAllMode_State.gConfig_BW.gRbw = globalUserVariable->gRbw;
    gAllMode_State.gConfig_BW.gVbw = globalUserVariable->gVbw;
    gAllMode_State.gConfig_BW.gVbwtoRbw = globalUserVariable->gVbwtoRbw;

    memcpy(gAllMode_State.gConfig_Trace.gAverageCount,globalUserVariable->gAverageCount,sizeof(qint32)*NUM_TRACE);
    gAllMode_State.gConfig_Trace.gDetectorMode = globalUserVariable->gDetectorMode;
    gAllMode_State.gConfig_Trace.gTmpDetectorMode = globalUserVariable->gTmpDetectorMode;
    memcpy(gAllMode_State.gConfig_Trace.gTraceAverage,globalUserVariable->gTraceAverage,sizeof(qint32)*NUM_TRACE);
    gAllMode_State.gConfig_Trace.gTraceSelect = globalUserVariable->gTraceSelect;
    memcpy(gAllMode_State.gConfig_Trace.gTraceType,globalUserVariable->gTraceType,sizeof(qint32)*NUM_TRACE);
    memcpy(gAllMode_State.gConfig_Trace.gTraceView,globalUserVariable->gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(gAllMode_State.gConfig_Trace.gViewAction,globalUserVariable->gViewAction,sizeof(qint32)*NUM_TRACE);
#endif
#if USABLE
    gAllMode_State.gConfig_ShareMem.uMsCompleteFlag = SA_sm_config_sweep->uMsCompleteFlag;
#endif
    gAllMode_State.gConfig_ShareMem.uSweepCompleteFlag = SA_sm_config_sweep->uSweepCompleteFlag;
}

/**
 * @brief paraSaveLoad::paraInit_StateAndDataFile
 * @return
 * @date 190701
 * @author Jhonson
 */
bool paraSaveLoad::paraInit_StateAndDataFile()
{
    StataAndDataTofileSaveLoadPara(&gSpanModeState_MsData);
    StataAndDataTofileSaveLoadPara(&gChnlPowerModeState_MsData);
    StataAndDataTofileSaveLoadPara(&gOccupiedModeState_MsData);
    StataAndDataTofileSaveLoadPara(&gACPModeState_MsData);
    StataAndDataTofileSaveLoadPara(&gMultiACPModeState_MsData);
    StataAndDataTofileSaveLoadPara(&gSpectrumEmissionMaskModeState_MsData);
    StataAndDataTofileSaveLoadPara(&gSpuriousEmissionMaskModeState_MsData);
    StataAndDataTofileSaveLoadPara(&gFieldStrengthModeState_MsData);
    StataAndDataTofileSaveLoadPara(&gDemodulationModeState_MsData);

    StataAndDataTofileSaveLoadPara(&gAllModeState_MsData.pSpanModeParam);
    StataAndDataTofileSaveLoadPara(&gAllModeState_MsData.pChnlPowerModeParam);
    StataAndDataTofileSaveLoadPara(&gAllModeState_MsData.pOccupiedModeParam);
    StataAndDataTofileSaveLoadPara(&gAllModeState_MsData.pACPModeParam);
    StataAndDataTofileSaveLoadPara(&gAllModeState_MsData.pMultiACPModeParam);
    StataAndDataTofileSaveLoadPara(&gAllModeState_MsData.pSpectrumEmissionMaskModeParam);
    StataAndDataTofileSaveLoadPara(&gAllModeState_MsData.pSpuriousEmissionMaskModeParam);
    StataAndDataTofileSaveLoadPara(&gAllModeState_MsData.pFieldStrengthModeParam);
    StataAndDataTofileSaveLoadPara(&gAllModeState_MsData.pDemodulationModeParam);
    gAllModeState_MsData.mSaveLoad_CurrentMode = globalUserVariable->currentMode;
    gAllModeState_MsData.gCenterFreq           = globalUserVariable->gCenterFreq;
    gAllModeState_MsData.gConfig_ShareMem.uAllSweepCompleteFlag = SA_sm_config_sweep->uAllSweepCompleteFlag;
    gAllModeState_MsData.gConfig_ShareMem.uIFMode = globalUserVariable->uIFMode;
#if !RESERVE_0327
    gAllModeState_MsData.gConfig_FreqSpan.gCFFreq = globalUserVariable->gCFFreq;
    gAllModeState_MsData.gConfig_FreqSpan.gfreqOffset = globalUserVariable->gfreqOffset;
    gAllModeState_MsData.gConfig_FreqSpan.gLastSpanFreq = globalUserVariable->gLastSpanFreq;
    gAllModeState_MsData.gConfig_FreqSpan.gSpanFreq = globalUserVariable->gSpanFreq;
    gAllModeState_MsData.gConfig_FreqSpan.gSpanMode = globalUserVariable->gSpanMode;
    gAllModeState_MsData.gConfig_FreqSpan.gStepFreq = globalUserVariable->gStepFreq;
    gAllModeState_MsData.gConfig_FreqSpan.gZeroSpanAction = globalUserVariable->gZeroSpanAction;

    gAllModeState_MsData.gConfig_Amplitude.gAmptdUnit = globalUserVariable->gAmptdUnit;
    gAllModeState_MsData.gConfig_Amplitude.gAtten = globalUserVariable->gAtten;
    gAllModeState_MsData.gConfig_Amplitude.gAttenValue = globalUserVariable->gAttenValue;
    gAllModeState_MsData.gConfig_Amplitude.gAutoAttenTrack = globalUserVariable->gAutoAttenTrack;
    gAllModeState_MsData.gConfig_Amplitude.gPreamp = globalUserVariable->gPreamp;
    gAllModeState_MsData.gConfig_Amplitude.gRefLevel = globalUserVariable->gRefLevel;
    gAllModeState_MsData.gConfig_Amplitude.gRefOffset = globalUserVariable->gRefOffset;
    gAllModeState_MsData.gConfig_Amplitude.gScaleDiv = globalUserVariable->gScaleDiv;

    gAllModeState_MsData.gConfig_BW.gAutoRbw = globalUserVariable->gAutoRbw;
    gAllModeState_MsData.gConfig_BW.gAutoVbw = globalUserVariable->gAutoVbw;
    gAllModeState_MsData.gConfig_BW.gIFMode = globalUserVariable->uIFMode;
    gAllModeState_MsData.gConfig_BW.gRbw = globalUserVariable->gRbw;
    gAllModeState_MsData.gConfig_BW.gVbw = globalUserVariable->gVbw;
    gAllModeState_MsData.gConfig_BW.gVbwtoRbw = globalUserVariable->gVbwtoRbw;

    memcpy(gAllModeState_MsData.gConfig_Trace.gAverageCount,globalUserVariable->gAverageCount,sizeof(qint32)*NUM_TRACE);
    gAllModeState_MsData.gConfig_Trace.gDetectorMode = globalUserVariable->gDetectorMode;
    gAllModeState_MsData.gConfig_Trace.gTmpDetectorMode = globalUserVariable->gTmpDetectorMode;
    memcpy(gAllModeState_MsData.gConfig_Trace.gTraceAverage,globalUserVariable->gTraceAverage,sizeof(qint32)*NUM_TRACE);
    gAllModeState_MsData.gConfig_Trace.gTraceSelect = globalUserVariable->gTraceSelect;
    memcpy(gAllModeState_MsData.gConfig_Trace.gTraceType,globalUserVariable->gTraceType,sizeof(qint32)*NUM_TRACE);
    memcpy(gAllModeState_MsData.gConfig_Trace.gTraceView,globalUserVariable->gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(gAllModeState_MsData.gConfig_Trace.gViewAction,globalUserVariable->gViewAction,sizeof(qint32)*NUM_TRACE);
#endif
#if USABLE
    gAllModeState_MsData.gConfig_ShareMem.uMsCompleteFlag = SA_sm_config_sweep->uMsCompleteFlag;
#endif
    gAllModeState_MsData.gConfig_ShareMem.uSweepCompleteFlag = SA_sm_config_sweep->uSweepCompleteFlag;

    return 1;
}

/**
 * @brief paraSaveLoad::paraInit
 * @param pVariable
 */
void paraSaveLoad::paraInit_AllMode()
{

    globalUserVariableTofileSaveLoadPara(&(gAllMode_FileSaveLoadParam.pSpanModeParam));
    globalUserVariableTofileSaveLoadPara(&(gAllMode_FileSaveLoadParam.pChnlPowerModeParam));
    globalUserVariableTofileSaveLoadPara(&(gAllMode_FileSaveLoadParam.pOccupiedModeParam));
    globalUserVariableTofileSaveLoadPara(&(gAllMode_FileSaveLoadParam.pACPModeParam));
    globalUserVariableTofileSaveLoadPara(&(gAllMode_FileSaveLoadParam.pMultiACPModeParam));
    globalUserVariableTofileSaveLoadPara(&(gAllMode_FileSaveLoadParam.pSpectrumEmissionMaskModeParam));
    globalUserVariableTofileSaveLoadPara(&(gAllMode_FileSaveLoadParam.pSpuriousEmissionMaskModeParam));
    globalUserVariableTofileSaveLoadPara(&(gAllMode_FileSaveLoadParam.pFieldStrengthModeParam));
    globalUserVariableTofileSaveLoadPara(&(gAllMode_FileSaveLoadParam.pDemodulationModeParam));

    gAllMode_FileSaveLoadParam.FullStatus = globalUserVariable->FullStatus;
    gAllMode_FileSaveLoadParam.gCenterFreq = globalUserVariable->gCenterFreq;
    gAllMode_FileSaveLoadParam.leftHideChecked = globalUserVariable->pbLeftHideChecked;
    gAllMode_FileSaveLoadParam.mSaveLoad_CurrentMode = globalUserVariable->currentMode;
    gAllMode_FileSaveLoadParam.mSaveLoad_MeasureMode = SA_sm_config_measure->MeasureMode;

#if !RESERVE_0327
    gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gCFFreq = globalUserVariable->gCFFreq;
    gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gfreqOffset = globalUserVariable->gfreqOffset;
    gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gLastSpanFreq = globalUserVariable->gLastSpanFreq;
    gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gSpanFreq = globalUserVariable->gSpanFreq;
    gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gSpanMode = globalUserVariable->gSpanMode;
    gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gStepFreq = globalUserVariable->gStepFreq;
    gAllMode_FileSaveLoadParam.gConfig_FreqSpan.gZeroSpanAction = globalUserVariable->gZeroSpanAction;

    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gAmptdUnit = globalUserVariable->gAmptdUnit;
    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gAtten = globalUserVariable->gAtten;
    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gAttenValue = globalUserVariable->gAttenValue;
    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gAutoAttenTrack = globalUserVariable->gAutoAttenTrack;
    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gPreamp = globalUserVariable->gPreamp;
    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gRefLevel = globalUserVariable->gRefLevel;
    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gRefOffset = globalUserVariable->gRefOffset;
    gAllMode_FileSaveLoadParam.gConfig_Amplitude.gScaleDiv = globalUserVariable->gScaleDiv;

    gAllMode_FileSaveLoadParam.gConfig_BW.gAutoRbw = globalUserVariable->gAutoRbw;
    gAllMode_FileSaveLoadParam.gConfig_BW.gAutoVbw = globalUserVariable->gAutoVbw;
    gAllMode_FileSaveLoadParam.gConfig_BW.gIFMode = globalUserVariable->uIFMode;
    gAllMode_FileSaveLoadParam.gConfig_BW.gRbw = globalUserVariable->gRbw;
    gAllMode_FileSaveLoadParam.gConfig_BW.gVbw = globalUserVariable->gVbw;
    gAllMode_FileSaveLoadParam.gConfig_BW.gVbwtoRbw = globalUserVariable->gVbwtoRbw;

    memcpy(gAllMode_FileSaveLoadParam.gConfig_Trace.gAverageCount,globalUserVariable->gAverageCount,sizeof(qint32)*NUM_TRACE);
    gAllMode_FileSaveLoadParam.gConfig_Trace.gDetectorMode = globalUserVariable->gDetectorMode;
    gAllMode_FileSaveLoadParam.gConfig_Trace.gTmpDetectorMode = globalUserVariable->gTmpDetectorMode;
    memcpy(gAllMode_FileSaveLoadParam.gConfig_Trace.gTraceAverage,globalUserVariable->gTraceAverage,sizeof(qint32)*NUM_TRACE);
    gAllMode_FileSaveLoadParam.gConfig_Trace.gTraceSelect = globalUserVariable->gTraceSelect;
    memcpy(gAllMode_FileSaveLoadParam.gConfig_Trace.gTraceType,globalUserVariable->gTraceType,sizeof(qint32)*NUM_TRACE);
    memcpy(gAllMode_FileSaveLoadParam.gConfig_Trace.gTraceView,globalUserVariable->gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(gAllMode_FileSaveLoadParam.gConfig_Trace.gViewAction,globalUserVariable->gViewAction,sizeof(qint32)*NUM_TRACE);
#endif

    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bACPModeParamNull                  = true;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bChnlPowerModeParamNull            = true;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bDemodulationModeParamNull         = true;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bFieldStrengthModeParamNull        = true;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bMultiACPModeParamNull             = true;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bOccupiedModeParamNull             = true;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bSpanModeParamNull                 = true;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bSpectrumEmissionMaskModeParamNull = true;
    gAllMode_FileSaveLoadParam.pMeasurParaStatus.bSpuriousEmissionMaskModeParamNull = true;
}

/**
 * @brief paraSaveLoad::paraInit_MeasureMode
 * @param pVariable
 */
void paraSaveLoad::paraInit_MeasureMode()
{
    //Init FILE_SAVE_LOAD_VARIABLE
    globalUserVariableTofileSaveLoadPara(&gSpanModeParam);
    globalUserVariableTofileSaveLoadPara(&gChnlPowerModeParam);
    globalUserVariableTofileSaveLoadPara(&gOccupiedModeParam);
    globalUserVariableTofileSaveLoadPara(&gACPModeParam);
    globalUserVariableTofileSaveLoadPara(&gMultiACPModeParam);
    globalUserVariableTofileSaveLoadPara(&gSpectrumEmissionMaskModeParam);
    globalUserVariableTofileSaveLoadPara(&gSpuriousEmissionMaskModeParam);
    globalUserVariableTofileSaveLoadPara(&gFieldStrengthModeParam);
    globalUserVariableTofileSaveLoadPara(&gDemodulationModeParam);
}

/**
 * @brief paraSaveLoad::paraSave
 * @param pVariable
 */
void paraSaveLoad::paraSave(quint32 currentMode)
{
    switch(currentMode)
    {
    case SA_SPAN_MODE:
        globalUserVariableTofileSaveLoadPara(&gSpanModeParam);
        bSpanModeParamNull = false;
        measureStateTofileSaveLoadPara(&gSpanModeState);
        StataAndDataTofileSaveLoadPara(&gSpanModeState_MsData);
        break;
    case SA_CHNLPOWER_MEASURE_MODE:
        globalUserVariableTofileSaveLoadPara(&gChnlPowerModeParam);
        bChnlPowerModeParamNull = false;
        measureStateTofileSaveLoadPara(&gChnlPowerModeState);
        StataAndDataTofileSaveLoadPara(&gChnlPowerModeState_MsData);
        break;
    case SA_OCCUPIED_BW_MEASURE_MODE:
        globalUserVariableTofileSaveLoadPara(&gOccupiedModeParam);
        bOccupiedModeParamNull  = false;
        measureStateTofileSaveLoadPara(&gOccupiedModeState);
        StataAndDataTofileSaveLoadPara(&gOccupiedModeState_MsData);
        break;
    case SA_SPECTRUM_EMISSION_MASK_MODE:
        globalUserVariableTofileSaveLoadPara(&gSpectrumEmissionMaskModeParam);
        bSpectrumEmissionMaskModeParamNull = false;
        measureStateTofileSaveLoadPara(&gSpectrumEmissionMaskModeState);
        StataAndDataTofileSaveLoadPara(&gSpectrumEmissionMaskModeState_MsData);
        break;
    case SA_ACP_MEASURE_MODE:
        globalUserVariableTofileSaveLoadPara(&gACPModeParam);
        bACPModeParamNull = false;
        measureStateTofileSaveLoadPara(&gACPModeState);
        StataAndDataTofileSaveLoadPara(&gACPModeState_MsData);
        break;
    case SA_MULTI_ACP_MODE:
        globalUserVariableTofileSaveLoadPara(&gMultiACPModeParam);
        bMultiACPModeParamNull = false;
        measureStateTofileSaveLoadPara(&gMultiACPModeState);
        StataAndDataTofileSaveLoadPara(&gMultiACPModeState_MsData);
        break;
    case SA_SPURIOUS_EMISSION_MASK_MODE:
        globalUserVariableTofileSaveLoadPara(&gSpuriousEmissionMaskModeParam);
        bSpuriousEmissionMaskModeParamNull = false;
        measureStateTofileSaveLoadPara(&gSpuriousEmissionMaskModeState);
        StataAndDataTofileSaveLoadPara(&gSpuriousEmissionMaskModeState_MsData);
        break;
    case SA_FIELD_STRENGTH_MODE:
        globalUserVariableTofileSaveLoadPara(&gFieldStrengthModeParam);
        bFieldStrengthModeParamNull = false;
        measureStateTofileSaveLoadPara(&gFieldStrengthModeState);
        StataAndDataTofileSaveLoadPara(&gFieldStrengthModeState_MsData);
        break;
    case SA_DEMODULATION_MODE:
        globalUserVariableTofileSaveLoadPara(&gDemodulationModeParam);
        bDemodulationModeParamNull = false;
        measureStateTofileSaveLoadPara(&gDemodulationModeState);
        StataAndDataTofileSaveLoadPara(&gDemodulationModeState_MsData);
        break;
    default: break;
    }
}

/**
 * @brief paraSaveLoad::paraLoad
 * @param pVariable
 */
void paraSaveLoad::paraLoad(quint32 currentMode)
{
    switch(currentMode)
    {
    case SA_SPAN_MODE:                   fileSaveLoadParaToglobalUserVariable(&gSpanModeParam);                 break;
    case SA_OCCUPIED_BW_MEASURE_MODE:    fileSaveLoadParaToglobalUserVariable(&gOccupiedModeParam);             break;
    case SA_CHNLPOWER_MEASURE_MODE:      fileSaveLoadParaToglobalUserVariable(&gChnlPowerModeParam);            break;
    case SA_SPECTRUM_EMISSION_MASK_MODE: fileSaveLoadParaToglobalUserVariable(&gSpectrumEmissionMaskModeParam); break;
    case SA_ACP_MEASURE_MODE:            fileSaveLoadParaToglobalUserVariable(&gACPModeParam);                  break;
    case SA_MULTI_ACP_MODE:              fileSaveLoadParaToglobalUserVariable(&gMultiACPModeParam);             break;
    case SA_SPURIOUS_EMISSION_MASK_MODE: fileSaveLoadParaToglobalUserVariable(&gSpuriousEmissionMaskModeParam); break;
    case SA_FIELD_STRENGTH_MODE:         fileSaveLoadParaToglobalUserVariable(&gFieldStrengthModeParam);        break;
    case SA_DEMODULATION_MODE:           fileSaveLoadParaToglobalUserVariable(&gDemodulationModeParam);         break;
    default: break;
    }
}
/**
 * @brief paraSaveLoad::getParaStatus
 * @param currentMode
 * @return
 */
bool paraSaveLoad::getParaStatus(quint32 currentMode)
{
    bool retStatus = true;
    switch(currentMode)
    {
    case SA_SPAN_MODE:                   retStatus = bSpanModeParamNull;                 break;
    case SA_CHNLPOWER_MEASURE_MODE:      retStatus = bChnlPowerModeParamNull;            break;
    case SA_OCCUPIED_BW_MEASURE_MODE:    retStatus = bOccupiedModeParamNull ;            break;
    case SA_SPECTRUM_EMISSION_MASK_MODE: retStatus = bSpectrumEmissionMaskModeParamNull; break;
    case SA_ACP_MEASURE_MODE:            retStatus = bACPModeParamNull;                  break;
    case SA_MULTI_ACP_MODE:              retStatus = bMultiACPModeParamNull;             break;
    case SA_SPURIOUS_EMISSION_MASK_MODE: retStatus = bSpuriousEmissionMaskModeParamNull; break;
    case SA_FIELD_STRENGTH_MODE:         retStatus = bFieldStrengthModeParamNull;        break;
    case SA_DEMODULATION_MODE:           retStatus = bDemodulationModeParamNull;         break;
    default: break;
    }

    return retStatus;
}

//Johnson 0802
void paraSaveLoad::fileSaveLoadParaToglobalUserVariable(_FILE_SAVE_LOAD_VARIABLE_ *pVariable)
{
    globalUserVariable->ReadParamFromFile = 1;
    globalUserVariable->gSpecEMMaskType = pVariable->gConfig_Measure.gSpecEMMaskType;
    globalUserVariable->gSpecEMRefRbw = pVariable->gConfig_Measure.gSpecEMRefRbw;
    globalUserVariable->gSpecEMRefChBw = pVariable->gConfig_Measure.gSpecEMRefChBw;
    globalUserVariable->gSpecEMBsPower = pVariable->gConfig_Measure.gSpecEMBsPower;
    //********Measure
    //globalUserVariable->gDemodulationType = pVariable->gConfig_Measure.gDemodulationType;
    globalUserVariable->gChannelBandwidth = pVariable->gConfig_Measure.gChannelBandwidth;
    globalUserVariable->gChannelSpacing   = pVariable->gConfig_Measure.gChannelSpacing;
    globalUserVariable->gOccupied_BW      = pVariable->gConfig_Measure.gOccupiedBW;
    globalUserVariable->gXdB              = pVariable->gConfig_Measure.XdB;

    globalUserVariable->gHighestCHFreq   = pVariable->gConfig_Measure.gHighestCHFreq;
    globalUserVariable->gLowestCHFreq    = pVariable->gConfig_Measure.gLowestCHFreq;
    globalUserVariable->gMultiACPSpacing = pVariable->gConfig_Measure.gMultiACPSpacing;
    globalUserVariable->gMainIntegBW     = pVariable->gConfig_Measure.gMainIntegBW;
    globalUserVariable->gADJIntegBW      = pVariable->gConfig_Measure.gADJIntegBW;
    globalUserVariable->gALTIntegBW      = pVariable->gConfig_Measure.gALTIntegBW;

    memcpy(globalUserVariable->gSpurEMPara,pVariable->gConfig_Measure.gSpurEMPara,sizeof(__SPUR_EM__) * SPUR_EM_DATE_MAX);
    memcpy(globalUserVariable->gSpurEMViewStatus,pVariable->gConfig_Measure.gSpurEMViewStatus,sizeof(qint32) * SA_SPUREM_RANGE_CNT);
    globalUserVariable->gSpurEMAveType    = pVariable->gConfig_Measure.gSpurEMAveType;
    globalUserVariable->gSpurEMReportType = pVariable->gConfig_Measure.gSpurEMReportType;
    globalUserVariable->gMeasureStatus = pVariable->gConfig_Measure.gMeasureStatus;

    memcpy(globalUserVariable->gSpurEMSpur,pVariable->gConfig_Measure.gSpurEMSpur,sizeof(__SPUR_POINT__) * SA_SPUREM_RANGE_CNT*SA_SPUREM_SPUR_CNT);
    memcpy(globalUserVariable->gSpurEMSpurCnt,pVariable->gConfig_Measure.gSpurEMSpurCnt,sizeof(qint32) * SA_SPUREM_RANGE_CNT);

    globalUserVariable->gSpurEMTotalSpurCnt = pVariable->gConfig_Measure.gSpurEMTotalSpurCnt;
    globalUserVariable->gSpurEMCurRangeIndex = pVariable->gConfig_Measure.gSpurEMCurRangeIndex;
    globalUserVariable->gSpurEMCurDrawRangeIndex = pVariable->gConfig_Measure.gSpurEMCurDrawRangeIndex;
    globalUserVariable->gSpurEMCurSpurIndex = pVariable->gConfig_Measure.gSpurEMCurSpurIndex;

    globalUserVariable->gSpecEMDisplay    = pVariable->gConfig_Measure.gSpecEMDisplay;
    globalUserVariable->gSpecEMRefType    = pVariable->gConfig_Measure.gSpecEMRefType;
    memcpy(globalUserVariable->gSpecEMData,pVariable->gConfig_Measure.gSpecEMData,sizeof(__SPEC_EM__) * SA_SPECEM_FREQ_CNT);
    memcpy(globalUserVariable->gSpecEMViewStatus,pVariable->gConfig_Measure.gSpecEMViewStatus,sizeof(qint32) * SA_SPECEM_FREQ_CNT);

#if RESERVE_0327
    //********Freq Span
    /*globalUserVariable->gStartFreq      = pVariable->gConfig_FreqSpan.gStartFreq;
    globalUserVariable->gStopFreq         = pVariable->gConfig_FreqSpan.gStopFreq;
    globalUserVariable->gCenterFreq       = pVariable->gConfig_FreqSpan.gCenterFreq;*/
    globalUserVariable->gStepFreq         = pVariable->gConfig_FreqSpan.gStepFreq;
    globalUserVariable->gfreqOffset       = pVariable->gConfig_FreqSpan.gfreqOffset;

    globalUserVariable->gSpanFreq         = pVariable->gConfig_FreqSpan.gSpanFreq;
    globalUserVariable->gLastSpanFreq     = pVariable->gConfig_FreqSpan.gLastSpanFreq;
    globalUserVariable->gZeroSpanAction   = pVariable->gConfig_FreqSpan.gZeroSpanAction;
    globalUserVariable->gCFFreq           = pVariable->gConfig_FreqSpan.gCFFreq;
    globalUserVariable->gSpanMode         = pVariable->gConfig_FreqSpan.gSpanMode;

    /*
    globalUserVariable->gspanChangebyFreq = pVariable->gConfig_FreqSpan.gspanChangebyFreq;
    globalUserVariable->gbitsspan         = pVariable->gConfig_FreqSpan.gbitsspan;
    globalUserVariable->gbithalfsspan     = pVariable->gConfig_FreqSpan.gbithalfsspan;*/

    //*******SA_BW
    globalUserVariable->gVbwtoRbw         = pVariable->gConfig_BW.gVbwtoRbw;
    //globalUserVariable->gAutoVbwtoRbw     = pVariable->gConfig_BW.gAutoVbwtoRbw;
    //globalUserVariable->grbwChangedbyFreq = pVariable->gConfig_BW.grbwChangedbyFreq;

    globalUserVariable->gAutoRbw          = pVariable->gConfig_BW.gAutoRbw;
    globalUserVariable->gAutoVbw          = pVariable->gConfig_BW.gAutoVbw;
    globalUserVariable->gRbw              = pVariable->gConfig_BW.gRbw;
    globalUserVariable->gVbw              = pVariable->gConfig_BW.gVbw;
    globalUserVariable->uIFMode           = pVariable->gConfig_BW.gIFMode;

    //*******Amplitude
    globalUserVariable->gRefLevel         = pVariable->gConfig_Amplitude.gRefLevel;
    globalUserVariable->gRefOffset        = pVariable->gConfig_Amplitude.gRefOffset;
    globalUserVariable->gScaleDiv         = pVariable->gConfig_Amplitude.gScaleDiv;
    globalUserVariable->gAmptdUnit        = pVariable->gConfig_Amplitude.gAmptdUnit;
    globalUserVariable->gAtten            = pVariable->gConfig_Amplitude.gAtten;
    globalUserVariable->gPreamp           = pVariable->gConfig_Amplitude.gPreamp;
    globalUserVariable->gAttenValue       = pVariable->gConfig_Amplitude.gAttenValue;
    globalUserVariable->gAutoAttenTrack   = pVariable->gConfig_Amplitude.gAutoAttenTrack;

    //*******Trace
    memcpy(globalUserVariable->gTraceView,pVariable->gConfig_Trace.gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gViewAction,pVariable->gConfig_Trace.gViewAction,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gTraceType,pVariable->gConfig_Trace.gTraceType,sizeof(qint32)*NUM_TRACE);
    //memcpy(globalUserVariable->gTraceAverage,pVariable->gConfig_Trace.gTraceAverage,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gAverageCount,pVariable->gConfig_Trace.gAverageCount,sizeof(qint32)*NUM_TRACE);
//    for(qint32 i = 0;i<NUM_TRACE;i++){
//        memcpy(globalUserVariable->gTraceMeasureVal[i],pVariable->gConfig_Trace.gTraceMeasureVal[i],sizeof(qreal)*NUM_SWEEP_POINT);
//    }
    globalUserVariable->gTraceSelect      = pVariable->gConfig_Trace.gTraceSelect;
    globalUserVariable->gDetectorMode     = pVariable->gConfig_Trace.gDetectorMode;
    globalUserVariable->gTmpDetectorMode  = pVariable->gConfig_Trace.gTmpDetectorMode;
    //memcpy(globalUserVariable->gTmpDetectorMode,pVariable->gConfig_Trace.gTmpDetectorMode,sizeof(quint32)*MARKER_TOTAL_CNT);
#endif

    //*******Sweep
    globalUserVariable->gSweepType        = pVariable->gConfig_Sweep.gSweepType;
    globalUserVariable->gsweepAuto        = pVariable->gConfig_Sweep.gsweepAuto;
    globalUserVariable->gAutoSweepTime    = pVariable->gConfig_Sweep.gAutoSweepTime;
    globalUserVariable->gSweepTime        = pVariable->gConfig_Sweep.gSweepTime;
    globalUserVariable->gZeroSpanTime     = pVariable->gConfig_Sweep.gZeroSpanTime;
#if 0
    globalUserVariable->gSweepSpeed       = pVariable->gConfig_Sweep.gSweepSpeed;
#endif
    SA_sm_config_sweep->sweepMode         = pVariable->gConfig_Sweep.gSweepmode;
    globalUserVariable->ganamode          = pVariable->gConfig_Sweep.gSweepmode;
    globalUserVariable->gAutoDotSweepTime = pVariable->gConfig_Sweep.gAutoDotSweepTime;
    globalUserVariable->gDotSweepTime     = pVariable->gConfig_Sweep.gDotSweepTime;
    globalUserVariable->gFixDotSweepTime  = pVariable->gConfig_Sweep.gFixDotSweepTime;

#if 1
    //********Gate Sweep
#if 0
    globalUserVariable->gLvlEdgSelect = pVariable->gConfig_Gate_Sweep.gLvlEdgSelect;
    globalUserVariable->gDrCtrlSweepMode = pVariable->gConfig_Gate_Sweep.gDrCtrlSweepMode;
    globalUserVariable->gPrdTrgSynchroSrc = pVariable->gConfig_Gate_Sweep.gPrdTrgSynchroSrc;
    globalUserVariable->gPrdTrgSrcDelay = pVariable->gConfig_Gate_Sweep.gPrdTrgSrcDelay;
    globalUserVariable->gPrdTrigPrvntStatus = pVariable->gConfig_Gate_Sweep.gPrdTrigPrvntStatus;
    globalUserVariable->gPrdTrigPrvntTimes = pVariable->gConfig_Gate_Sweep.gPrdTrigPrvntTimes;
    globalUserVariable->gGateViewStartTime = pVariable->gConfig_Gate_Sweep.gGateViewStartTime;
    globalUserVariable->gGateSweepSpanChange = pVariable->gConfig_Gate_Sweep.gGateSweepSpanChange;
#endif
    globalUserVariable->gDrCtrlSource = pVariable->gConfig_Gate_Sweep.gDrCtrlSource;
    globalUserVariable->gLvlEdgMode   = pVariable->gConfig_Gate_Sweep.gLvlEdgMode;
    globalUserVariable->gDrCtrlSwitch = pVariable->gConfig_Gate_Sweep.gDrCtrlSwitch;
    globalUserVariable->gEdgTrigDely = pVariable->gConfig_Gate_Sweep.gEdgTrigDely;
    globalUserVariable->gEdgTrigDoorWdth = pVariable->gConfig_Gate_Sweep.gEdgTrigDoorWdth;
    globalUserVariable->gEdgTrigPrvntStatus = pVariable->gConfig_Gate_Sweep.gEdgTrigPrvntStatus;
    globalUserVariable->gEdgTrigPrvntTimes = pVariable->gConfig_Gate_Sweep.gEdgTrigPrvntTimes;
    globalUserVariable->gRFBurstTrigLevel = pVariable->gConfig_Gate_Sweep.gRFBurstTrigLevel;
    globalUserVariable->gPrdTrgPeriod = pVariable->gConfig_Gate_Sweep.gPrdTrgPeriod;
    globalUserVariable->gDrCtrlRbw = pVariable->gConfig_Gate_Sweep.gDrCtrlRbw;
    globalUserVariable->gGateViewStatus = pVariable->gConfig_Gate_Sweep.gGateViewStatus;
#endif

    //*******Trigger
    globalUserVariable->gTriggerMode      = pVariable->gConfig_Trigger.gTriggerMode;
    globalUserVariable->gTriggerPerTimer  = pVariable->gConfig_Trigger.gTriggerPerTimer;
    memcpy(globalUserVariable->gTriggerLevel,pVariable->gConfig_Trigger.gTriggerLevel,sizeof(qreal) * TRIGGER_SOURCE_CNT);
    memcpy(globalUserVariable->gTriggerSlope,pVariable->gConfig_Trigger.gTriggerSlope,sizeof(qint32) * TRIGGER_SOURCE_CNT);
    memcpy(globalUserVariable->gTriggerDelayStatus,pVariable->gConfig_Trigger.gTriggerDelayStatus,sizeof(qint32) * TRIGGER_SOURCE_CNT);
    memcpy(globalUserVariable->gTriggerDelayValue,pVariable->gConfig_Trigger.gTriggerDelayValue,sizeof(qreal) * TRIGGER_SOURCE_CNT);
    globalUserVariable->calData           = pVariable->gConfig_Trigger.gCalData;

    //*******Marker
    globalUserVariable->gPeakTrack        = pVariable->gConfig_Marker.gPeakTrack;
    globalUserVariable->gMarkerSelect     = pVariable->gConfig_Marker.gMarkerSelect;
    globalUserVariable->gMarkerDisplay    = pVariable->gConfig_Marker.gMarkerDisplay;
    memcpy(globalUserVariable->gMarkerView,pVariable->gConfig_Marker.gMarkerView,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerType,pVariable->gConfig_Marker.gMarkerType,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerRefFreq,pVariable->gConfig_Marker.gMarkerRefFreq,sizeof(quint64)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerRefPos,pVariable->gConfig_Marker.gMarkerRefPos,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerDeltaFreq,pVariable->gConfig_Marker.gMarkerDeltaFreq,sizeof(quint64)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerDeltaPos,pVariable->gConfig_Marker.gMarkerDeltaPos,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerNoise,pVariable->gConfig_Marker.gMarkerNoise,sizeof(qint32)*MARKER_TOTAL_CNT);
    globalUserVariable->gMarkerFreqCount = pVariable->gConfig_Marker.gMarkerFreqCount;
    memcpy(globalUserVariable->gMarkerTmpRefAmpt,pVariable->gConfig_Marker.gMarkerTmpRefAmpt,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerMarkerTmpRefPos,pVariable->gConfig_Marker.gMarkerMarkerTmpRefPos,sizeof(qreal)*MARKER_TOTAL_CNT);
#if PADD
    memcpy(globalUserVariable->gMarkerRefTime,pVariable->gConfig_Marker.gMarkerRefTime,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerDeltaTime,pVariable->gConfig_Marker.gMarkerDeltaTime,sizeof(qreal)*MARKER_TOTAL_CNT);
#endif
    //*******Peak


    //*******Limit
    for(qint32 i = 0;i<LIMIT_SELECTSUM;i++){
        globalUserLimit->gLimitLine[i]        = pVariable->gConfig_Limit.gLimitLine[i];
        globalUserLimit->gLimitEdge[i]        = pVariable->gConfig_Limit.gLimitEdge[i];
        globalUserLimit->gLimitEdgeValue[i]   = pVariable->gConfig_Limit.gLimitEdgeValue[i];
        globalUserLimit->gLatestLimitType[i]  = pVariable->gConfig_Limit.gLatestLimitType[i];
        globalUserLimit->gTotalDot[i]         = pVariable->gConfig_Limit.gTotalDot[i];

        /*globalUserLimit->gLatestLimitTestResult[i]      = pVariable->gConfig_Limit.gLatestLimitTestResult[i];
        globalUserLimit->gLatestLimitEdgeResult[i]      = pVariable->gConfig_Limit.gLatestLimitEdgeResult[i];

        memcpy(globalUserLimit->gXIndex[i],pVariable->gConfig_Limit.gXIndex[i],sizeof(qint32)*pVariable->gConfig_Limit.gTotalDot[i]);
        memcpy(globalUserLimit->gXAxis[i],pVariable->gConfig_Limit.gXAxis[i],sizeof(qint32)*pVariable->gConfig_Limit.gTotalDot[i]);
        memcpy(globalUserLimit->gYAxis[i],pVariable->gConfig_Limit.gYAxis[i],sizeof(qint32)*pVariable->gConfig_Limit.gTotalDot[i]);
        memcpy(globalUserLimit->gEdgeYAxis[i],pVariable->gConfig_Limit.gEdgeYAxis[i],sizeof(qint32)*pVariable->gConfig_Limit.gTotalDot[i]);*/
        memcpy(globalUserLimit->gFreq[i],pVariable->gConfig_Limit.gFreq[i],sizeof(qreal)*pVariable->gConfig_Limit.gTotalDot[i]);
        memcpy(globalUserLimit->gAmplitude[i],pVariable->gConfig_Limit.gAmplitude[i],sizeof(qreal)*pVariable->gConfig_Limit.gTotalDot[i]);

        //memcpy(globalUserLimit->gLatestLimitDrawPoint[i],pVariable->gConfig_Limit.gLatestLimitDrawPoint[i],sizeof(qint32)*NUM_SWEEP_POINT);
        //memcpy(globalUserLimit->gLatestLimitEdgeDrawPoint[i],pVariable->gConfig_Limit.gLatestLimitEdgeDrawPoint[i],sizeof(qint32)*NUM_SWEEP_POINT);
    }
    globalUserLimit->gLimitTest = pVariable->gConfig_Limit.gLimitTest;
    /*memcpy(globalUserLimit->gLatestLimitUpperDrawPoint,pVariable->gConfig_Limit.gLatestLimitUpperDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);
    memcpy(globalUserLimit->gLatestLimitLowerDrawPoint,pVariable->gConfig_Limit.gLatestLimitLowerDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);
    memcpy(globalUserLimit->gLatestLimitUpperEdgeDrawPoint,pVariable->gConfig_Limit.gLatestLimitUpperEdgeDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);
    memcpy(globalUserLimit->gLatestLimitLowerEdgeDrawPoint,pVariable->gConfig_Limit.gLatestLimitLowerEdgeDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);*/

    globalUserLimit->gLimitSelect = pVariable->gConfig_Limit.gLimitSelect;

#ifdef SAMPLE_LIMIT
    //*******Upper & Lower Limit
    globalUserLimit->gUpperLimit  =  pVariable->gConfig_Limit.gUpperLimitAmpt;
    globalUserLimit->gLowerLimit  =  pVariable->gConfig_Limit.gLowerLimitAmpt;
    globalUserLimit->gUpperLimitStatus = pVariable->gConfig_Limit.gUpperLimitStatus;
    globalUserLimit->gLowerLimitStatus = pVariable->gConfig_Limit.gLowerLimitStatus;
    globalUserLimit->gATLdBcLimit = pVariable->gConfig_Limit.gAtlLimitdBc;
    globalUserLimit->gATLdBcLimitStatus = pVariable->gConfig_Limit.gAtlLimitStatus;
#endif
    //*******Power Sensor
//    globalUserVariable->gMenu                  = pVariable->gConfig_PowerSensor.gMenu;
//    globalUserVariable->gPowersensorFreq       = pVariable->gConfig_PowerSensor.gPowersensorFreq;
//    globalUserVariable->gPowersensorExtOffset  = pVariable->gConfig_PowerSensor.gPowersensorExtOffset;

    //*******Preset


    //*******System



#if GUIDRAW_CONFIG
    //******GUI Draw Set
    SA_guiDrawSet.gridHorStep      = pVariable->gConfig_GuiDrawSet.gridHorStep;
    SA_guiDrawSet.gridVerStep      = pVariable->gConfig_GuiDrawSet.gridVerStep;
    SA_guiDrawSet.limitLineOnCount = pVariable->gConfig_GuiDrawSet.limitLineOnCount;
    SA_guiDrawSet.markerOnCount    = pVariable->gConfig_GuiDrawSet.markerOnCount;
    SA_guiDrawSet.peakPos          = pVariable->gConfig_GuiDrawSet.peakPos;
#endif

    //*******Ext Para
    globalUserVariable->SecondaryAction = pVariable->gConfig_Ext.SecondaryAction;

    //*******Current Work State
    globalUserVariable->gCurrentWorkState = pVariable->gCurrentWorkState;
}
void paraSaveLoad::globalUserVariableTofileSaveLoadPara(_FILE_SAVE_LOAD_VARIABLE_ *pVariable)
{
    pVariable->gConfig_Measure.gSpecEMMaskType = globalUserVariable->gSpecEMMaskType;
    pVariable->gConfig_Measure.gSpecEMRefRbw = globalUserVariable->gSpecEMRefRbw;
    pVariable->gConfig_Measure.gSpecEMRefChBw = globalUserVariable->gSpecEMRefChBw;
    pVariable->gConfig_Measure.gSpecEMBsPower = globalUserVariable->gSpecEMBsPower;
    //********Measure
    //pVariable->gConfig_Measure.gDemodulationType  = globalUserVariable->gDemodulationType;
    pVariable->gConfig_Measure.gChannelBandwidth  = globalUserVariable->gChannelBandwidth;
    pVariable->gConfig_Measure.gChannelSpacing    = globalUserVariable->gChannelSpacing;
    pVariable->gConfig_Measure.gOccupiedBW        = globalUserVariable->gOccupied_BW;
    pVariable->gConfig_Measure.XdB                = globalUserVariable->gXdB;

    pVariable->gConfig_Measure.gHighestCHFreq   = globalUserVariable->gHighestCHFreq;
    pVariable->gConfig_Measure.gLowestCHFreq    = globalUserVariable->gLowestCHFreq;
    pVariable->gConfig_Measure.gMultiACPSpacing = globalUserVariable->gMultiACPSpacing;
    pVariable->gConfig_Measure.gMainIntegBW     = globalUserVariable->gMainIntegBW;
    pVariable->gConfig_Measure.gADJIntegBW      = globalUserVariable->gADJIntegBW;
    pVariable->gConfig_Measure.gALTIntegBW      = globalUserVariable->gALTIntegBW;

    memcpy(pVariable->gConfig_Measure.gSpurEMPara,globalUserVariable->gSpurEMPara,sizeof(__SPUR_EM__) * SPUR_EM_DATE_MAX);
    memcpy(pVariable->gConfig_Measure.gSpurEMViewStatus,globalUserVariable->gSpurEMViewStatus,sizeof(qint32) * SA_SPUREM_RANGE_CNT);
    pVariable->gConfig_Measure.gSpurEMAveType    = globalUserVariable->gSpurEMAveType;
    pVariable->gConfig_Measure.gSpurEMReportType = globalUserVariable->gSpurEMReportType;
    pVariable->gConfig_Measure.gMeasureStatus = globalUserVariable->gMeasureStatus;

    memcpy(pVariable->gConfig_Measure.gSpurEMSpur,globalUserVariable->gSpurEMSpur,sizeof(__SPUR_POINT__) * SA_SPUREM_RANGE_CNT*SA_SPUREM_SPUR_CNT);
    memcpy(pVariable->gConfig_Measure.gSpurEMSpurCnt,globalUserVariable->gSpurEMSpurCnt,sizeof(qint32) * SA_SPUREM_RANGE_CNT);
    pVariable->gConfig_Measure.gSpurEMTotalSpurCnt = globalUserVariable->gSpurEMTotalSpurCnt;
    pVariable->gConfig_Measure.gSpurEMCurRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    pVariable->gConfig_Measure.gSpurEMCurDrawRangeIndex = globalUserVariable->gSpurEMCurDrawRangeIndex;
    pVariable->gConfig_Measure.gSpurEMCurSpurIndex = globalUserVariable->gSpurEMCurSpurIndex;


    pVariable->gConfig_Measure.gSpecEMDisplay    = globalUserVariable->gSpecEMDisplay;
    pVariable->gConfig_Measure.gSpecEMRefType    = globalUserVariable->gSpecEMRefType;
    memcpy(pVariable->gConfig_Measure.gSpecEMData,globalUserVariable->gSpecEMData,sizeof(__SPEC_EM__) * SA_SPECEM_FREQ_CNT);
    memcpy(pVariable->gConfig_Measure.gSpecEMViewStatus,globalUserVariable->gSpecEMViewStatus,sizeof(qint32) * SA_SPECEM_FREQ_CNT);
#if RESERVE_0327
    //********Freq Span
    /*pVariable->gConfig_FreqSpan.gStartFreq      = globalUserVariable->gStartFreq;
    pVariable->gConfig_FreqSpan.gStopFreq         = globalUserVariable->gStopFreq;
    pVariable->gConfig_FreqSpan.gCenterFreq       = globalUserVariable->gCenterFreq;*/
    pVariable->gConfig_FreqSpan.gStepFreq         = globalUserVariable->gStepFreq;
    pVariable->gConfig_FreqSpan.gfreqOffset       = globalUserVariable->gfreqOffset;

    pVariable->gConfig_FreqSpan.gSpanFreq         = globalUserVariable->gSpanFreq;
    pVariable->gConfig_FreqSpan.gLastSpanFreq     = globalUserVariable->gLastSpanFreq;
    pVariable->gConfig_FreqSpan.gCFFreq           = globalUserVariable->gCFFreq;
    pVariable->gConfig_FreqSpan.gSpanMode         = globalUserVariable->gSpanMode;
    pVariable->gConfig_FreqSpan.gZeroSpanAction   = globalUserVariable->gZeroSpanAction;

    /*
    pVariable->gConfig_FreqSpan.gspanChangebyFreq = globalUserVariable->gspanChangebyFreq;
    pVariable->gConfig_FreqSpan.gbitsspan         = globalUserVariable->gbitsspan;
    pVariable->gConfig_FreqSpan.gbithalfsspan     = globalUserVariable->gbithalfsspan;*/

    //*******SA_BW
    pVariable->gConfig_BW.gVbwtoRbw         = globalUserVariable->gVbwtoRbw;
    //pVariable->gConfig_BW.gAutoVbwtoRbw     = globalUserVariable->gAutoVbwtoRbw;
    //pVariable->gConfig_BW.grbwChangedbyFreq = globalUserVariable->grbwChangedbyFreq;

    pVariable->gConfig_BW.gAutoRbw          = globalUserVariable->gAutoRbw;
    pVariable->gConfig_BW.gAutoVbw          = globalUserVariable->gAutoVbw;
    pVariable->gConfig_BW.gRbw              = globalUserVariable->gRbw;
    pVariable->gConfig_BW.gVbw              = globalUserVariable->gVbw;
    pVariable->gConfig_BW.gIFMode           = globalUserVariable->uIFMode;

    //*******Amplitude
    pVariable->gConfig_Amplitude.gRefLevel         = globalUserVariable->gRefLevel;
    pVariable->gConfig_Amplitude.gRefOffset        = globalUserVariable->gRefOffset;
    pVariable->gConfig_Amplitude.gScaleDiv         = globalUserVariable->gScaleDiv;
    pVariable->gConfig_Amplitude.gAmptdUnit        = globalUserVariable->gAmptdUnit;
    pVariable->gConfig_Amplitude.gAtten            = globalUserVariable->gAtten;
    pVariable->gConfig_Amplitude.gPreamp           = globalUserVariable->gPreamp;
    pVariable->gConfig_Amplitude.gAttenValue       = globalUserVariable->gAttenValue;
    pVariable->gConfig_Amplitude.gAutoAttenTrack   = globalUserVariable->gAutoAttenTrack;

    //*******Trace
    memcpy(pVariable->gConfig_Trace.gTraceView,globalUserVariable->gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(pVariable->gConfig_Trace.gViewAction,globalUserVariable->gViewAction,sizeof(qint32)*NUM_TRACE);
    memcpy(pVariable->gConfig_Trace.gTraceType,globalUserVariable->gTraceType,sizeof(qint32)*NUM_TRACE);
    //memcpy(pVariable->gConfig_Trace.gTraceAverage,globalUserVariable->gTraceAverage,sizeof(qint32)*NUM_TRACE);
    memcpy(pVariable->gConfig_Trace.gAverageCount,globalUserVariable->gAverageCount,sizeof(qint32)*NUM_TRACE);
//    for(qint32 i = 0;i<NUM_TRACE;i++){
//        memcpy(pVariable->gConfig_Trace.gTraceMeasureVal[i],globalUserVariable->gTraceMeasureVal[i],sizeof(qreal)*NUM_SWEEP_POINT);
//    }
    pVariable->gConfig_Trace.gTraceSelect      = globalUserVariable->gTraceSelect;
    pVariable->gConfig_Trace.gDetectorMode     = globalUserVariable->gDetectorMode;
    pVariable->gConfig_Trace.gTmpDetectorMode  = globalUserVariable->gTmpDetectorMode;
    //memcpy(pVariable->gConfig_Trace.gTmpDetectorMode,globalUserVariable->gTmpDetectorMode,sizeof(quint32)*MARKER_TOTAL_CNT);
#endif

    //*******Sweep
    pVariable->gConfig_Sweep.gSweepType        = globalUserVariable->gSweepType;
    pVariable->gConfig_Sweep.gsweepAuto        = globalUserVariable->gsweepAuto;
    pVariable->gConfig_Sweep.gAutoSweepTime    = globalUserVariable->gAutoSweepTime;
    pVariable->gConfig_Sweep.gSweepTime        = globalUserVariable->gSweepTime;
    pVariable->gConfig_Sweep.gZeroSpanTime     = globalUserVariable->gZeroSpanTime;
#if 0
    pVariable->gConfig_Sweep.gSweepSpeed       = globalUserVariable->gSweepSpeed;
#endif
    //Tony remote
    pVariable->gConfig_Sweep.gSweepmode        = SA_sm_config_sweep->sweepMode;
    pVariable->gConfig_Sweep.gAutoDotSweepTime = globalUserVariable->gAutoDotSweepTime;
    pVariable->gConfig_Sweep.gDotSweepTime     = globalUserVariable->gDotSweepTime;
    pVariable->gConfig_Sweep.gFixDotSweepTime  = globalUserVariable->gFixDotSweepTime;

#if 1
    //********Gate Sweep
#if 0
    pVariable->gConfig_Gate_Sweep.gLvlEdgSelect        = globalUserVariable->gLvlEdgSelect;
    pVariable->gConfig_Gate_Sweep.gDrCtrlSweepMode        = globalUserVariable->gDrCtrlSweepMode;
    pVariable->gConfig_Gate_Sweep.gPrdTrgSynchroSrc     = globalUserVariable->gPrdTrgSynchroSrc;
    pVariable->gConfig_Gate_Sweep.gPrdTrgSrcDelay        = globalUserVariable->gPrdTrgSrcDelay;
    pVariable->gConfig_Gate_Sweep.gPrdTrigPrvntStatus     = globalUserVariable->gPrdTrigPrvntStatus;
    pVariable->gConfig_Gate_Sweep.gPrdTrigPrvntTimes       = globalUserVariable->gPrdTrigPrvntTimes;
    pVariable->gConfig_Gate_Sweep.gGateViewStartTime     = globalUserVariable->gGateViewStartTime;
    pVariable->gConfig_Gate_Sweep.gGateSweepSpanChange = globalUserVariable->gGateSweepSpanChange;
#endif
    pVariable->gConfig_Gate_Sweep.gDrCtrlSource        = globalUserVariable->gDrCtrlSource;
    pVariable->gConfig_Gate_Sweep.gLvlEdgMode    = globalUserVariable->gLvlEdgMode;
    pVariable->gConfig_Gate_Sweep.gDrCtrlSwitch       = globalUserVariable->gDrCtrlSwitch;
    pVariable->gConfig_Gate_Sweep.gEdgTrigDely        = globalUserVariable->gEdgTrigDely;
    pVariable->gConfig_Gate_Sweep.gEdgTrigDoorWdth = globalUserVariable->gEdgTrigDoorWdth;
    pVariable->gConfig_Gate_Sweep.gEdgTrigPrvntStatus     = globalUserVariable->gEdgTrigPrvntStatus;
    pVariable->gConfig_Gate_Sweep.gEdgTrigPrvntTimes        = globalUserVariable->gEdgTrigPrvntTimes;
    pVariable->gConfig_Gate_Sweep.gRFBurstTrigLevel        = globalUserVariable->gRFBurstTrigLevel;
    pVariable->gConfig_Gate_Sweep.gPrdTrgPeriod    = globalUserVariable->gPrdTrgPeriod;
    pVariable->gConfig_Gate_Sweep.gDrCtrlRbw        = globalUserVariable->gDrCtrlRbw;
    pVariable->gConfig_Gate_Sweep.gGateViewStatus     = globalUserVariable->gGateViewStatus;
#endif

    //*******Trigger
    pVariable->gConfig_Trigger.gTriggerMode    = globalUserVariable->gTriggerMode;
    pVariable->gConfig_Trigger.gTriggerPerTimer = globalUserVariable->gTriggerPerTimer;
    memcpy(pVariable->gConfig_Trigger.gTriggerLevel,globalUserVariable->gTriggerLevel,sizeof(qreal) * TRIGGER_SOURCE_CNT);
    memcpy(pVariable->gConfig_Trigger.gTriggerSlope,globalUserVariable->gTriggerSlope,sizeof(qint32) * TRIGGER_SOURCE_CNT);
    memcpy(pVariable->gConfig_Trigger.gTriggerDelayStatus,globalUserVariable->gTriggerDelayStatus,sizeof(qint32) * TRIGGER_SOURCE_CNT);
    memcpy(pVariable->gConfig_Trigger.gTriggerDelayValue,globalUserVariable->gTriggerDelayValue,sizeof(qreal) * TRIGGER_SOURCE_CNT);
    pVariable->gConfig_Trigger.gCalData        = globalUserVariable->calData;

    //*******Marker
    pVariable->gConfig_Marker.gPeakTrack        = globalUserVariable->gPeakTrack;
    pVariable->gConfig_Marker.gMarkerSelect     = globalUserVariable->gMarkerSelect;
    pVariable->gConfig_Marker.gMarkerDisplay    = globalUserVariable->gMarkerDisplay;
    memcpy(pVariable->gConfig_Marker.gMarkerView,globalUserVariable->gMarkerView,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerType,globalUserVariable->gMarkerType,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerRefFreq,globalUserVariable->gMarkerRefFreq,sizeof(quint64)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerRefPos,globalUserVariable->gMarkerRefPos,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerDeltaFreq,globalUserVariable->gMarkerDeltaFreq,sizeof(quint64)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerDeltaPos,globalUserVariable->gMarkerDeltaPos,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerNoise,globalUserVariable->gMarkerNoise,sizeof(qint32)*MARKER_TOTAL_CNT);
    pVariable->gConfig_Marker.gMarkerFreqCount = globalUserVariable->gMarkerFreqCount;
    memcpy(pVariable->gConfig_Marker.gMarkerTmpRefAmpt,globalUserVariable->gMarkerTmpRefAmpt,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerMarkerTmpRefPos,globalUserVariable->gMarkerMarkerTmpRefPos,sizeof(qreal)*MARKER_TOTAL_CNT);
#if PADD
    memcpy(pVariable->gConfig_Marker.gMarkerRefTime,globalUserVariable->gMarkerRefTime,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerDeltaTime,globalUserVariable->gMarkerDeltaTime,sizeof(qreal)*MARKER_TOTAL_CNT);
#endif
    //*******Peak


    //*******Limit
    for(qint32 i = 0;i<LIMIT_SELECTSUM;i++){
        pVariable->gConfig_Limit.gLimitLine[i]        = globalUserLimit->gLimitLine[i];
        pVariable->gConfig_Limit.gLimitEdge[i]        = globalUserLimit->gLimitEdge[i];
        pVariable->gConfig_Limit.gLimitEdgeValue[i]   = globalUserLimit->gLimitEdgeValue[i];
        pVariable->gConfig_Limit.gLatestLimitType[i]  = globalUserLimit->gLatestLimitType[i];
        pVariable->gConfig_Limit.gTotalDot[i]         = globalUserLimit->gTotalDot[i];

        /*pVariable->gConfig_Limit.gLatestLimitTestResult[i]      = globalUserLimit->gLatestLimitTestResult[i];
        pVariable->gConfig_Limit.gLatestLimitEdgeResult[i]      = globalUserLimit->gLatestLimitEdgeResult[i];

        memcpy(pVariable->gConfig_Limit.gXIndex[i],globalUserLimit->gXIndex[i],sizeof(qint32)*globalUserLimit->gTotalDot[i]);
        memcpy(pVariable->gConfig_Limit.gXAxis[i],globalUserLimit->gXAxis[i],sizeof(qint32)*globalUserLimit->gTotalDot[i]);
        memcpy(pVariable->gConfig_Limit.gYAxis[i],globalUserLimit->gYAxis[i],sizeof(qint32)*globalUserLimit->gTotalDot[i]);
        memcpy(pVariable->gConfig_Limit.gEdgeYAxis[i],globalUserLimit->gEdgeYAxis[i],sizeof(qint32)*globalUserLimit->gTotalDot[i]);*/
        memcpy(pVariable->gConfig_Limit.gFreq[i],globalUserLimit->gFreq[i],sizeof(qreal)*globalUserLimit->gTotalDot[i]);
        memcpy(pVariable->gConfig_Limit.gAmplitude[i],globalUserLimit->gAmplitude[i],sizeof(qreal)*globalUserLimit->gTotalDot[i]);


        //memcpy(pVariable->gConfig_Limit.gLatestLimitDrawPoint[i],globalUserLimit->gLatestLimitDrawPoint[i],sizeof(qint32)*NUM_SWEEP_POINT);
        //memcpy(pVariable->gConfig_Limit.gLatestLimitEdgeDrawPoint[i],globalUserLimit->gLatestLimitEdgeDrawPoint[i],sizeof(qint32)*NUM_SWEEP_POINT);
    }
    pVariable->gConfig_Limit.gLimitTest = globalUserLimit->gLimitTest;
    /*memcpy(pVariable->gConfig_Limit.gLatestLimitUpperDrawPoint,globalUserLimit->gLatestLimitUpperDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);
    memcpy(pVariable->gConfig_Limit.gLatestLimitLowerDrawPoint,globalUserLimit->gLatestLimitLowerDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);
    memcpy(pVariable->gConfig_Limit.gLatestLimitUpperEdgeDrawPoint,globalUserLimit->gLatestLimitUpperEdgeDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);
    memcpy(pVariable->gConfig_Limit.gLatestLimitLowerEdgeDrawPoint,globalUserLimit->gLatestLimitLowerEdgeDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);*/

    pVariable->gConfig_Limit.gLimitSelect                = globalUserLimit->gLimitSelect;

#ifdef SAMPLE_LIMIT
    //*******Upper & Lower Limit
    pVariable->gConfig_Limit.gUpperLimitAmpt                = globalUserLimit->gUpperLimit;
    pVariable->gConfig_Limit.gLowerLimitAmpt                = globalUserLimit->gLowerLimit;
    pVariable->gConfig_Limit.gUpperLimitStatus              = globalUserLimit->gUpperLimitStatus;
    pVariable->gConfig_Limit.gLowerLimitStatus              = globalUserLimit->gLowerLimitStatus;
    pVariable->gConfig_Limit.gAtlLimitdBc                   = globalUserLimit->gATLdBcLimit;
    pVariable->gConfig_Limit.gAtlLimitStatus                = globalUserLimit->gATLdBcLimitStatus;
#endif
    //*******Power Sensor
//    pVariable->gConfig_PowerSensor.gMenu                  = globalUserVariable->gMenu;
//    pVariable->gConfig_PowerSensor.gPowersensorFreq       = globalUserVariable->gPowersensorFreq;
//    pVariable->gConfig_PowerSensor.gPowersensorExtOffset  = globalUserVariable->gPowersensorExtOffset;

    //*******Preset


    //*******System

#if GUIDRAW_CONFIG
    //******GUI Draw Set
    pVariable->gConfig_GuiDrawSet.gridHorStep          = SA_guiDrawSet.gridHorStep;
    pVariable->gConfig_GuiDrawSet.gridVerStep          = SA_guiDrawSet.gridVerStep;
    pVariable->gConfig_GuiDrawSet.limitLineOnCount     = SA_guiDrawSet.limitLineOnCount;
    pVariable->gConfig_GuiDrawSet.markerOnCount        = SA_guiDrawSet.markerOnCount;
    pVariable->gConfig_GuiDrawSet.peakPos              = SA_guiDrawSet.peakPos;
#endif

    //*******Ext Para
    pVariable->gConfig_Ext.SecondaryAction             = globalUserVariable->SecondaryAction;

    //*******Current Work State
    pVariable->gCurrentWorkState                       = globalUserVariable->gCurrentWorkState;
}

void paraSaveLoad::fileSaveLoadParaTomeasureState(_CONFIG_STATE_ *pVariable)
{
    globalUserVariable->gSpecEMMaskType = pVariable->gConfig_Measure.gSpecEMMaskType;
    globalUserVariable->gSpecEMRefRbw = pVariable->gConfig_Measure.gSpecEMRefRbw;
    globalUserVariable->gSpecEMRefChBw = pVariable->gConfig_Measure.gSpecEMRefChBw;
    globalUserVariable->gSpecEMBsPower = pVariable->gConfig_Measure.gSpecEMBsPower;
    //********Measure
    //globalUserVariable->gDemodulationType = pVariable->gConfig_Measure.gDemodulationType;
    globalUserVariable->gChannelBandwidth = pVariable->gConfig_Measure.gChannelBandwidth;
    globalUserVariable->gChannelSpacing   = pVariable->gConfig_Measure.gChannelSpacing;
    globalUserVariable->gOccupied_BW      = pVariable->gConfig_Measure.gOccupiedBW;
    globalUserVariable->gXdB              = pVariable->gConfig_Measure.XdB;

    globalUserVariable->gHighestCHFreq   = pVariable->gConfig_Measure.gHighestCHFreq;
    globalUserVariable->gLowestCHFreq    = pVariable->gConfig_Measure.gLowestCHFreq;
    globalUserVariable->gMultiACPSpacing = pVariable->gConfig_Measure.gMultiACPSpacing;
    globalUserVariable->gMainIntegBW     = pVariable->gConfig_Measure.gMainIntegBW;
    globalUserVariable->gADJIntegBW      = pVariable->gConfig_Measure.gADJIntegBW;
    globalUserVariable->gALTIntegBW      = pVariable->gConfig_Measure.gALTIntegBW;

    memcpy(globalUserVariable->gSpurEMPara,pVariable->gConfig_Measure.gSpurEMPara,sizeof(__SPUR_EM__) * SPUR_EM_DATE_MAX);
    memcpy(globalUserVariable->gSpurEMViewStatus,pVariable->gConfig_Measure.gSpurEMViewStatus,sizeof(qint32) * SA_SPUREM_RANGE_CNT);
    globalUserVariable->gSpurEMAveType    = pVariable->gConfig_Measure.gSpurEMAveType;
    globalUserVariable->gSpurEMReportType = pVariable->gConfig_Measure.gSpurEMReportType;
    globalUserVariable->gMeasureStatus = pVariable->gConfig_Measure.gMeasureStatus;

    globalUserVariable->gSpecEMDisplay    = pVariable->gConfig_Measure.gSpecEMDisplay;
    globalUserVariable->gSpecEMRefType    = pVariable->gConfig_Measure.gSpecEMRefType;
    memcpy(globalUserVariable->gSpecEMData,pVariable->gConfig_Measure.gSpecEMData,sizeof(__SPEC_EM__) * SA_SPECEM_FREQ_CNT);
    memcpy(globalUserVariable->gSpecEMViewStatus,pVariable->gConfig_Measure.gSpecEMViewStatus,sizeof(qint32) * SA_SPECEM_FREQ_CNT);
#if RESERVE_0327
    //********Freq Span
    /*globalUserVariable->gStartFreq      = pVariable->gConfig_FreqSpan.gStartFreq;
    globalUserVariable->gStopFreq         = pVariable->gConfig_FreqSpan.gStopFreq;
    globalUserVariable->gCenterFreq       = pVariable->gConfig_FreqSpan.gCenterFreq;*/
    globalUserVariable->gStepFreq         = pVariable->gConfig_FreqSpan.gStepFreq;
    globalUserVariable->gfreqOffset       = pVariable->gConfig_FreqSpan.gfreqOffset;

    globalUserVariable->gSpanFreq         = pVariable->gConfig_FreqSpan.gSpanFreq;
    globalUserVariable->gLastSpanFreq     = pVariable->gConfig_FreqSpan.gLastSpanFreq;
    globalUserVariable->gZeroSpanAction   = pVariable->gConfig_FreqSpan.gZeroSpanAction;
    globalUserVariable->gCFFreq           = pVariable->gConfig_FreqSpan.gCFFreq;
    globalUserVariable->gSpanMode         = pVariable->gConfig_FreqSpan.gSpanMode;

    /*
    globalUserVariable->gspanChangebyFreq = pVariable->gConfig_FreqSpan.gspanChangebyFreq;
    globalUserVariable->gbitsspan         = pVariable->gConfig_FreqSpan.gbitsspan;
    globalUserVariable->gbithalfsspan     = pVariable->gConfig_FreqSpan.gbithalfsspan;*/

    //*******SA_BW
    globalUserVariable->gVbwtoRbw         = pVariable->gConfig_BW.gVbwtoRbw;
    //globalUserVariable->gAutoVbwtoRbw     = pVariable->gConfig_BW.gAutoVbwtoRbw;
    //globalUserVariable->grbwChangedbyFreq = pVariable->gConfig_BW.grbwChangedbyFreq;

    globalUserVariable->gAutoRbw          = pVariable->gConfig_BW.gAutoRbw;
    globalUserVariable->gAutoVbw          = pVariable->gConfig_BW.gAutoVbw;
    globalUserVariable->gRbw              = pVariable->gConfig_BW.gRbw;
    globalUserVariable->gVbw              = pVariable->gConfig_BW.gVbw;
    globalUserVariable->uIFMode            = pVariable->gConfig_BW.gIFMode;

    //*******Amplitude
    globalUserVariable->gRefLevel         = pVariable->gConfig_Amplitude.gRefLevel;
    globalUserVariable->gRefOffset        = pVariable->gConfig_Amplitude.gRefOffset;
    globalUserVariable->gScaleDiv         = pVariable->gConfig_Amplitude.gScaleDiv;
    globalUserVariable->gAmptdUnit        = pVariable->gConfig_Amplitude.gAmptdUnit;
    globalUserVariable->gAtten            = pVariable->gConfig_Amplitude.gAtten;
    globalUserVariable->gPreamp           = pVariable->gConfig_Amplitude.gPreamp;
    globalUserVariable->gAttenValue       = pVariable->gConfig_Amplitude.gAttenValue;
    globalUserVariable->gAutoAttenTrack   = pVariable->gConfig_Amplitude.gAutoAttenTrack;

    //*******Trace
    memcpy(globalUserVariable->gTraceView,pVariable->gConfig_Trace.gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gViewAction,pVariable->gConfig_Trace.gViewAction,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gTraceType,pVariable->gConfig_Trace.gTraceType,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gTraceAverage,pVariable->gConfig_Trace.gTraceAverage,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gAverageCount,pVariable->gConfig_Trace.gAverageCount,sizeof(qint32)*NUM_TRACE);
//    for(qint32 i = 0;i<NUM_TRACE;i++){
//        memcpy(globalUserVariable->gTraceMeasureVal[i],pVariable->gConfig_Trace.gTraceMeasureVal[i],sizeof(qreal)*NUM_SWEEP_POINT);
//    }
    globalUserVariable->gTraceSelect      = pVariable->gConfig_Trace.gTraceSelect;
    globalUserVariable->gDetectorMode     = pVariable->gConfig_Trace.gDetectorMode;
    globalUserVariable->gTmpDetectorMode  = pVariable->gConfig_Trace.gTmpDetectorMode;
    //memcpy(globalUserVariable->gTmpDetectorMode,pVariable->gConfig_Trace.gTmpDetectorMode,sizeof(quint32)*MARKER_TOTAL_CNT);
#endif

    //*******Sweep
    globalUserVariable->gSweepType        = pVariable->gConfig_Sweep.gSweepType;
    globalUserVariable->gsweepAuto        = pVariable->gConfig_Sweep.gsweepAuto;
    globalUserVariable->gAutoSweepTime    = pVariable->gConfig_Sweep.gAutoSweepTime;
    globalUserVariable->gSweepTime        = pVariable->gConfig_Sweep.gSweepTime;
    globalUserVariable->gZeroSpanTime     = pVariable->gConfig_Sweep.gZeroSpanTime;
#if 0
    globalUserVariable->gSweepSpeed       = pVariable->gConfig_Sweep.gSweepSpeed;
#endif
    SA_sm_config_sweep->sweepMode         = pVariable->gConfig_Sweep.gSweepmode;
    globalUserVariable->ganamode          = pVariable->gConfig_Sweep.gSweepmode;
    globalUserVariable->gAutoDotSweepTime = pVariable->gConfig_Sweep.gAutoDotSweepTime;
    globalUserVariable->gDotSweepTime     = pVariable->gConfig_Sweep.gDotSweepTime;
    globalUserVariable->gFixDotSweepTime  = pVariable->gConfig_Sweep.gFixDotSweepTime;

#if 1
    //********Gate Sweep
#if 0
    globalUserVariable->gLvlEdgSelect = pVariable->gConfig_Gate_Sweep.gLvlEdgSelect;
    globalUserVariable->gDrCtrlSweepMode = pVariable->gConfig_Gate_Sweep.gDrCtrlSweepMode;
    globalUserVariable->gPrdTrgSynchroSrc = pVariable->gConfig_Gate_Sweep.gPrdTrgSynchroSrc;
    globalUserVariable->gPrdTrgSrcDelay = pVariable->gConfig_Gate_Sweep.gPrdTrgSrcDelay;
    globalUserVariable->gPrdTrigPrvntStatus = pVariable->gConfig_Gate_Sweep.gPrdTrigPrvntStatus;
    globalUserVariable->gPrdTrigPrvntTimes = pVariable->gConfig_Gate_Sweep.gPrdTrigPrvntTimes;
    globalUserVariable->gGateViewStartTime = pVariable->gConfig_Gate_Sweep.gGateViewStartTime;
    globalUserVariable->gGateSweepSpanChange = pVariable->gConfig_Gate_Sweep.gGateSweepSpanChange;
#endif
    globalUserVariable->gDrCtrlSource = pVariable->gConfig_Gate_Sweep.gDrCtrlSource;
    globalUserVariable->gLvlEdgMode   = pVariable->gConfig_Gate_Sweep.gLvlEdgMode;
    globalUserVariable->gDrCtrlSwitch = pVariable->gConfig_Gate_Sweep.gDrCtrlSwitch;
    globalUserVariable->gEdgTrigDely = pVariable->gConfig_Gate_Sweep.gEdgTrigDely;
    globalUserVariable->gEdgTrigDoorWdth = pVariable->gConfig_Gate_Sweep.gEdgTrigDoorWdth;
    globalUserVariable->gEdgTrigPrvntStatus = pVariable->gConfig_Gate_Sweep.gEdgTrigPrvntStatus;
    globalUserVariable->gEdgTrigPrvntTimes = pVariable->gConfig_Gate_Sweep.gEdgTrigPrvntTimes;
    globalUserVariable->gRFBurstTrigLevel = pVariable->gConfig_Gate_Sweep.gRFBurstTrigLevel;
    globalUserVariable->gPrdTrgPeriod = pVariable->gConfig_Gate_Sweep.gPrdTrgPeriod;
    globalUserVariable->gDrCtrlRbw = pVariable->gConfig_Gate_Sweep.gDrCtrlRbw;
    globalUserVariable->gGateViewStatus = pVariable->gConfig_Gate_Sweep.gGateViewStatus;
#endif

    //*******Trigger
    globalUserVariable->gTriggerMode      = pVariable->gConfig_Trigger.gTriggerMode;
    globalUserVariable->gTriggerPerTimer  = pVariable->gConfig_Trigger.gTriggerPerTimer;
    memcpy(globalUserVariable->gTriggerLevel,pVariable->gConfig_Trigger.gTriggerLevel,sizeof(qreal) * TRIGGER_SOURCE_CNT);
    memcpy(globalUserVariable->gTriggerSlope,pVariable->gConfig_Trigger.gTriggerSlope,sizeof(qint32) * TRIGGER_SOURCE_CNT);
    memcpy(globalUserVariable->gTriggerDelayStatus,pVariable->gConfig_Trigger.gTriggerDelayStatus,sizeof(qint32) * TRIGGER_SOURCE_CNT);
    memcpy(globalUserVariable->gTriggerDelayValue,pVariable->gConfig_Trigger.gTriggerDelayValue,sizeof(qreal) * TRIGGER_SOURCE_CNT);
    globalUserVariable->calData           = pVariable->gConfig_Trigger.gCalData;

    //*******Marker
    globalUserVariable->gPeakTrack        = pVariable->gConfig_Marker.gPeakTrack;
    globalUserVariable->gMarkerSelect     = pVariable->gConfig_Marker.gMarkerSelect;
    globalUserVariable->gMarkerDisplay    = pVariable->gConfig_Marker.gMarkerDisplay;
    memcpy(globalUserVariable->gMarkerView,pVariable->gConfig_Marker.gMarkerView,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerType,pVariable->gConfig_Marker.gMarkerType,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerRefFreq,pVariable->gConfig_Marker.gMarkerRefFreq,sizeof(quint64)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerRefPos,pVariable->gConfig_Marker.gMarkerRefPos,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerDeltaFreq,pVariable->gConfig_Marker.gMarkerDeltaFreq,sizeof(quint64)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerDeltaPos,pVariable->gConfig_Marker.gMarkerDeltaPos,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerNoise,pVariable->gConfig_Marker.gMarkerNoise,sizeof(qint32)*MARKER_TOTAL_CNT);
    globalUserVariable->gMarkerFreqCount = pVariable->gConfig_Marker.gMarkerFreqCount;
    memcpy(globalUserVariable->gMarkerTmpRefAmpt,pVariable->gConfig_Marker.gMarkerTmpRefAmpt,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerMarkerTmpRefPos,pVariable->gConfig_Marker.gMarkerMarkerTmpRefPos,sizeof(qreal)*MARKER_TOTAL_CNT);
#if PADD
    memcpy(globalUserVariable->gMarkerRefTime,pVariable->gConfig_Marker.gMarkerRefTime,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerDeltaTime,pVariable->gConfig_Marker.gMarkerDeltaTime,sizeof(qreal)*MARKER_TOTAL_CNT);
#endif
    //*******Peak


    //*******Limit
    for(qint32 i = 0;i<LIMIT_SELECTSUM;i++){
        globalUserLimit->gLimitLine[i]        = pVariable->gConfig_Limit.gLimitLine[i];
        globalUserLimit->gLimitEdge[i]        = pVariable->gConfig_Limit.gLimitEdge[i];
        globalUserLimit->gLimitEdgeValue[i]   = pVariable->gConfig_Limit.gLimitEdgeValue[i];
        globalUserLimit->gLatestLimitType[i]  = pVariable->gConfig_Limit.gLatestLimitType[i];
        globalUserLimit->gTotalDot[i]         = pVariable->gConfig_Limit.gTotalDot[i];

        memcpy(globalUserLimit->gXIndex[i],pVariable->gConfig_Limit.gXIndex[i],sizeof(qint32)*pVariable->gConfig_Limit.gTotalDot[i]);
        memcpy(globalUserLimit->gEdgeYAxis[i],pVariable->gConfig_Limit.gEdgeYAxis[i],sizeof(qint32)*pVariable->gConfig_Limit.gTotalDot[i]);
        memcpy(globalUserLimit->gFreq[i],pVariable->gConfig_Limit.gFreq[i],sizeof(qreal)*pVariable->gConfig_Limit.gTotalDot[i]);
        memcpy(globalUserLimit->gAmplitude[i],pVariable->gConfig_Limit.gAmplitude[i],sizeof(qreal)*pVariable->gConfig_Limit.gTotalDot[i]);

    }
    globalUserLimit->gLimitTest = pVariable->gConfig_Limit.gLimitTest;

    globalUserLimit->gLimitSelect = pVariable->gConfig_Limit.gLimitSelect;

#ifdef SAMPLE_LIMIT
    //*******Upper & Lower Limit
    globalUserLimit->gUpperLimit  =  pVariable->gConfig_Limit.gUpperLimitAmpt;
    globalUserLimit->gLowerLimit  =  pVariable->gConfig_Limit.gLowerLimitAmpt;
    globalUserLimit->gUpperLimitStatus = pVariable->gConfig_Limit.gUpperLimitStatus;
    globalUserLimit->gLowerLimitStatus = pVariable->gConfig_Limit.gLowerLimitStatus;
    globalUserLimit->gATLdBcLimit = pVariable->gConfig_Limit.gAtlLimitdBc;
    globalUserLimit->gATLdBcLimitStatus = pVariable->gConfig_Limit.gAtlLimitStatus;
#endif
    //*******Power Sensor
//    globalUserVariable->gMenu                  = pVariable->gConfig_PowerSensor.gMenu;
//    globalUserVariable->gPowersensorFreq       = pVariable->gConfig_PowerSensor.gPowersensorFreq;
//    globalUserVariable->gPowersensorExtOffset  = pVariable->gConfig_PowerSensor.gPowersensorExtOffset;

    //*******Preset


    //*******System


#if GUIDRAW_CONFIG
    //******GUI Draw Set
    SA_guiDrawSet.gridHorStep      = pVariable->gConfig_GuiDrawSet.gridHorStep;
    SA_guiDrawSet.gridVerStep      = pVariable->gConfig_GuiDrawSet.gridVerStep;
    SA_guiDrawSet.limitLineOnCount = pVariable->gConfig_GuiDrawSet.limitLineOnCount;
    SA_guiDrawSet.markerOnCount    = pVariable->gConfig_GuiDrawSet.markerOnCount;
    SA_guiDrawSet.peakPos          = pVariable->gConfig_GuiDrawSet.peakPos;
#endif

    //*******Ext Para
    globalUserVariable->SecondaryAction = pVariable->gConfig_Ext.SecondaryAction;

    //*******Current Work State
    globalUserVariable->gCurrentWorkState = pVariable->gCurrentWorkState;
}
void paraSaveLoad::measureStateTofileSaveLoadPara(_CONFIG_STATE_ *pVariable)
{
    pVariable->gConfig_Measure.gSpecEMMaskType = globalUserVariable->gSpecEMMaskType;
    pVariable->gConfig_Measure.gSpecEMRefRbw = globalUserVariable->gSpecEMRefRbw;
    pVariable->gConfig_Measure.gSpecEMRefChBw = globalUserVariable->gSpecEMRefChBw;
    pVariable->gConfig_Measure.gSpecEMBsPower = globalUserVariable->gSpecEMBsPower;
    //********Measure
    //pVariable->gConfig_Measure.gDemodulationType  = globalUserVariable->gDemodulationType;
    pVariable->gConfig_Measure.gChannelBandwidth  = globalUserVariable->gChannelBandwidth;
    pVariable->gConfig_Measure.gChannelSpacing    = globalUserVariable->gChannelSpacing;
    pVariable->gConfig_Measure.gOccupiedBW        = globalUserVariable->gOccupied_BW;
    pVariable->gConfig_Measure.XdB                = globalUserVariable->gXdB;

    pVariable->gConfig_Measure.gHighestCHFreq   = globalUserVariable->gHighestCHFreq;
    pVariable->gConfig_Measure.gLowestCHFreq    = globalUserVariable->gLowestCHFreq;
    pVariable->gConfig_Measure.gMultiACPSpacing = globalUserVariable->gMultiACPSpacing;
    pVariable->gConfig_Measure.gMainIntegBW     = globalUserVariable->gMainIntegBW;
    pVariable->gConfig_Measure.gADJIntegBW      = globalUserVariable->gADJIntegBW;
    pVariable->gConfig_Measure.gALTIntegBW      = globalUserVariable->gALTIntegBW;

    memcpy(pVariable->gConfig_Measure.gSpurEMPara,globalUserVariable->gSpurEMPara,sizeof(__SPUR_EM__) * SPUR_EM_DATE_MAX);
    memcpy(pVariable->gConfig_Measure.gSpurEMViewStatus,globalUserVariable->gSpurEMViewStatus,sizeof(qint32) * SA_SPUREM_RANGE_CNT);
    pVariable->gConfig_Measure.gSpurEMAveType    = globalUserVariable->gSpurEMAveType;
    pVariable->gConfig_Measure.gSpurEMReportType = globalUserVariable->gSpurEMReportType;
    pVariable->gConfig_Measure.gSpecEMDisplay    = globalUserVariable->gSpecEMDisplay;
    pVariable->gConfig_Measure.gSpecEMRefType    = globalUserVariable->gSpecEMRefType;
    memcpy(pVariable->gConfig_Measure.gSpecEMData,globalUserVariable->gSpecEMData,sizeof(__SPEC_EM__) * SA_SPECEM_FREQ_CNT);
    memcpy(pVariable->gConfig_Measure.gSpecEMViewStatus,globalUserVariable->gSpecEMViewStatus,sizeof(qint32) * SA_SPECEM_FREQ_CNT);

    pVariable->gConfig_Measure.gMeasureStatus = globalUserVariable->gMeasureStatus;
#if RESERVE_0327
    //********Freq Span
    /*pVariable->gConfig_FreqSpan.gStartFreq      = globalUserVariable->gStartFreq;
    pVariable->gConfig_FreqSpan.gStopFreq         = globalUserVariable->gStopFreq;
    pVariable->gConfig_FreqSpan.gCenterFreq       = globalUserVariable->gCenterFreq;*/
    pVariable->gConfig_FreqSpan.gStepFreq         = globalUserVariable->gStepFreq;
    pVariable->gConfig_FreqSpan.gfreqOffset       = globalUserVariable->gfreqOffset;

    pVariable->gConfig_FreqSpan.gSpanFreq         = globalUserVariable->gSpanFreq;
    pVariable->gConfig_FreqSpan.gLastSpanFreq     = globalUserVariable->gLastSpanFreq;
    pVariable->gConfig_FreqSpan.gCFFreq           = globalUserVariable->gCFFreq;
    pVariable->gConfig_FreqSpan.gSpanMode         = globalUserVariable->gSpanMode;
    pVariable->gConfig_FreqSpan.gZeroSpanAction   = globalUserVariable->gZeroSpanAction;

    /*
    pVariable->gConfig_FreqSpan.gspanChangebyFreq = globalUserVariable->gspanChangebyFreq;
    pVariable->gConfig_FreqSpan.gbitsspan         = globalUserVariable->gbitsspan;
    pVariable->gConfig_FreqSpan.gbithalfsspan     = globalUserVariable->gbithalfsspan;*/

    //*******SA_BW
    pVariable->gConfig_BW.gVbwtoRbw         = globalUserVariable->gVbwtoRbw;
    //pVariable->gConfig_BW.gAutoVbwtoRbw     = globalUserVariable->gAutoVbwtoRbw;
    //pVariable->gConfig_BW.grbwChangedbyFreq = globalUserVariable->grbwChangedbyFreq;

    pVariable->gConfig_BW.gAutoRbw          = globalUserVariable->gAutoRbw;
    pVariable->gConfig_BW.gAutoVbw          = globalUserVariable->gAutoVbw;
    pVariable->gConfig_BW.gRbw              = globalUserVariable->gRbw;
    pVariable->gConfig_BW.gVbw              = globalUserVariable->gVbw;
    pVariable->gConfig_BW.gIFMode           = globalUserVariable->uIFMode;

    //*******Amplitude
    pVariable->gConfig_Amplitude.gRefLevel         = globalUserVariable->gRefLevel;
    pVariable->gConfig_Amplitude.gRefOffset        = globalUserVariable->gRefOffset;
    pVariable->gConfig_Amplitude.gScaleDiv         = globalUserVariable->gScaleDiv;
    pVariable->gConfig_Amplitude.gAmptdUnit        = globalUserVariable->gAmptdUnit;
    pVariable->gConfig_Amplitude.gAtten            = globalUserVariable->gAtten;
    pVariable->gConfig_Amplitude.gPreamp           = globalUserVariable->gPreamp;
    pVariable->gConfig_Amplitude.gAttenValue       = globalUserVariable->gAttenValue;
    pVariable->gConfig_Amplitude.gAutoAttenTrack   = globalUserVariable->gAutoAttenTrack;

    //*******Trace
    memcpy(pVariable->gConfig_Trace.gTraceView,globalUserVariable->gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(pVariable->gConfig_Trace.gViewAction,globalUserVariable->gViewAction,sizeof(qint32)*NUM_TRACE);
    memcpy(pVariable->gConfig_Trace.gTraceType,globalUserVariable->gTraceType,sizeof(qint32)*NUM_TRACE);
    memcpy(pVariable->gConfig_Trace.gTraceAverage,globalUserVariable->gTraceAverage,sizeof(qint32)*NUM_TRACE);
    memcpy(pVariable->gConfig_Trace.gAverageCount,globalUserVariable->gAverageCount,sizeof(qint32)*NUM_TRACE);
//    for(qint32 i = 0;i<NUM_TRACE;i++){
//        memcpy(pVariable->gConfig_Trace.gTraceMeasureVal[i],globalUserVariable->gTraceMeasureVal[i],sizeof(qreal)*NUM_SWEEP_POINT);
//    }
    pVariable->gConfig_Trace.gTraceSelect      = globalUserVariable->gTraceSelect;
    pVariable->gConfig_Trace.gDetectorMode     = globalUserVariable->gDetectorMode;
    pVariable->gConfig_Trace.gTmpDetectorMode  = globalUserVariable->gTmpDetectorMode;
#endif

    //*******Sweep
    pVariable->gConfig_Sweep.gSweepType        = globalUserVariable->gSweepType;
    pVariable->gConfig_Sweep.gsweepAuto        = globalUserVariable->gsweepAuto;
    pVariable->gConfig_Sweep.gAutoSweepTime    = globalUserVariable->gAutoSweepTime;
    pVariable->gConfig_Sweep.gSweepTime        = globalUserVariable->gSweepTime;
    pVariable->gConfig_Sweep.gZeroSpanTime     = globalUserVariable->gZeroSpanTime;
#if 0
    pVariable->gConfig_Sweep.gSweepSpeed       = globalUserVariable->gSweepSpeed;
#endif
    pVariable->gConfig_Sweep.gSweepmode        = SA_sm_config_sweep->sweepMode;
    pVariable->gConfig_Sweep.gAutoDotSweepTime = globalUserVariable->gAutoDotSweepTime;
    pVariable->gConfig_Sweep.gDotSweepTime     = globalUserVariable->gDotSweepTime;
    pVariable->gConfig_Sweep.gFixDotSweepTime  = globalUserVariable->gFixDotSweepTime;

#if 1
    //********Gate Sweep
#if 0
    pVariable->gConfig_Gate_Sweep.gLvlEdgSelect        = globalUserVariable->gLvlEdgSelect;
    pVariable->gConfig_Gate_Sweep.gDrCtrlSweepMode        = globalUserVariable->gDrCtrlSweepMode;
    pVariable->gConfig_Gate_Sweep.gPrdTrgSynchroSrc     = globalUserVariable->gPrdTrgSynchroSrc;
    pVariable->gConfig_Gate_Sweep.gPrdTrgSrcDelay        = globalUserVariable->gPrdTrgSrcDelay;
    pVariable->gConfig_Gate_Sweep.gPrdTrigPrvntStatus     = globalUserVariable->gPrdTrigPrvntStatus;
    pVariable->gConfig_Gate_Sweep.gPrdTrigPrvntTimes       = globalUserVariable->gPrdTrigPrvntTimes;
    pVariable->gConfig_Gate_Sweep.gGateViewStartTime     = globalUserVariable->gGateViewStartTime;
    pVariable->gConfig_Gate_Sweep.gGateSweepSpanChange = globalUserVariable->gGateSweepSpanChange;
#endif
    pVariable->gConfig_Gate_Sweep.gDrCtrlSource        = globalUserVariable->gDrCtrlSource;
    pVariable->gConfig_Gate_Sweep.gLvlEdgMode    = globalUserVariable->gLvlEdgMode;
    pVariable->gConfig_Gate_Sweep.gDrCtrlSwitch       = globalUserVariable->gDrCtrlSwitch;
    pVariable->gConfig_Gate_Sweep.gEdgTrigDely        = globalUserVariable->gEdgTrigDely;
    pVariable->gConfig_Gate_Sweep.gEdgTrigDoorWdth = globalUserVariable->gEdgTrigDoorWdth;
    pVariable->gConfig_Gate_Sweep.gEdgTrigPrvntStatus     = globalUserVariable->gEdgTrigPrvntStatus;
    pVariable->gConfig_Gate_Sweep.gEdgTrigPrvntTimes        = globalUserVariable->gEdgTrigPrvntTimes;
    pVariable->gConfig_Gate_Sweep.gRFBurstTrigLevel        = globalUserVariable->gRFBurstTrigLevel;
    pVariable->gConfig_Gate_Sweep.gPrdTrgPeriod    = globalUserVariable->gPrdTrgPeriod;
    pVariable->gConfig_Gate_Sweep.gDrCtrlRbw        = globalUserVariable->gDrCtrlRbw;
    pVariable->gConfig_Gate_Sweep.gGateViewStatus     = globalUserVariable->gGateViewStatus;
#endif

    //*******Trigger
    pVariable->gConfig_Trigger.gTriggerMode     = globalUserVariable->gTriggerMode;
    pVariable->gConfig_Trigger.gTriggerPerTimer = globalUserVariable->gTriggerPerTimer;
    memcpy(pVariable->gConfig_Trigger.gTriggerLevel,globalUserVariable->gTriggerLevel,sizeof(qreal) * TRIGGER_SOURCE_CNT);
    memcpy(pVariable->gConfig_Trigger.gTriggerSlope,globalUserVariable->gTriggerSlope,sizeof(qint32) * TRIGGER_SOURCE_CNT);
    memcpy(pVariable->gConfig_Trigger.gTriggerDelayStatus,globalUserVariable->gTriggerDelayStatus,sizeof(qint32) * TRIGGER_SOURCE_CNT);
    memcpy(pVariable->gConfig_Trigger.gTriggerDelayValue,globalUserVariable->gTriggerDelayValue,sizeof(qreal) * TRIGGER_SOURCE_CNT);
    pVariable->gConfig_Trigger.gCalData         = globalUserVariable->calData;

    //*******Marker
    pVariable->gConfig_Marker.gPeakTrack        = globalUserVariable->gPeakTrack;
    pVariable->gConfig_Marker.gMarkerSelect     = globalUserVariable->gMarkerSelect;
    pVariable->gConfig_Marker.gMarkerDisplay    = globalUserVariable->gMarkerDisplay;
    memcpy(pVariable->gConfig_Marker.gMarkerView,globalUserVariable->gMarkerView,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerType,globalUserVariable->gMarkerType,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerRefFreq,globalUserVariable->gMarkerRefFreq,sizeof(quint64)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerRefPos,globalUserVariable->gMarkerRefPos,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerDeltaFreq,globalUserVariable->gMarkerDeltaFreq,sizeof(quint64)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerDeltaPos,globalUserVariable->gMarkerDeltaPos,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerNoise,globalUserVariable->gMarkerNoise,sizeof(qint32)*MARKER_TOTAL_CNT);
    pVariable->gConfig_Marker.gMarkerFreqCount = globalUserVariable->gMarkerFreqCount;
    memcpy(pVariable->gConfig_Marker.gMarkerTmpRefAmpt,globalUserVariable->gMarkerTmpRefAmpt,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerMarkerTmpRefPos,globalUserVariable->gMarkerMarkerTmpRefPos,sizeof(qreal)*MARKER_TOTAL_CNT);
#if PADD
    memcpy(pVariable->gConfig_Marker.gMarkerRefTime,globalUserVariable->gMarkerRefTime,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerDeltaTime,globalUserVariable->gMarkerDeltaTime,sizeof(qreal)*MARKER_TOTAL_CNT);
#endif
    //*******Peak


    //*******Limit
    for(qint32 i = 0;i<LIMIT_SELECTSUM;i++){
        pVariable->gConfig_Limit.gLimitLine[i]        = globalUserLimit->gLimitLine[i];
        pVariable->gConfig_Limit.gLimitEdge[i]        = globalUserLimit->gLimitEdge[i];
        pVariable->gConfig_Limit.gLimitEdgeValue[i]   = globalUserLimit->gLimitEdgeValue[i];
        pVariable->gConfig_Limit.gLatestLimitType[i]  = globalUserLimit->gLatestLimitType[i];
        pVariable->gConfig_Limit.gTotalDot[i]         = globalUserLimit->gTotalDot[i];

        memcpy(pVariable->gConfig_Limit.gXIndex[i],globalUserLimit->gXIndex[i],sizeof(qint32)*globalUserLimit->gTotalDot[i]);
        memcpy(pVariable->gConfig_Limit.gEdgeYAxis[i],globalUserLimit->gEdgeYAxis[i],sizeof(qint32)*globalUserLimit->gTotalDot[i]);
        memcpy(pVariable->gConfig_Limit.gFreq[i],globalUserLimit->gFreq[i],sizeof(qreal)*globalUserLimit->gTotalDot[i]);
        memcpy(pVariable->gConfig_Limit.gAmplitude[i],globalUserLimit->gAmplitude[i],sizeof(qreal)*globalUserLimit->gTotalDot[i]);
    }
    pVariable->gConfig_Limit.gLimitTest = globalUserLimit->gLimitTest;

    pVariable->gConfig_Limit.gLimitSelect                = globalUserLimit->gLimitSelect;

#ifdef SAMPLE_LIMIT
    //*******Upper & Lower Limit
    pVariable->gConfig_Limit.gUpperLimitAmpt                = globalUserLimit->gUpperLimit;
    pVariable->gConfig_Limit.gLowerLimitAmpt                = globalUserLimit->gLowerLimit;
    pVariable->gConfig_Limit.gUpperLimitStatus                = globalUserLimit->gUpperLimitStatus;
    pVariable->gConfig_Limit.gLowerLimitStatus                = globalUserLimit->gLowerLimitStatus;
    pVariable->gConfig_Limit.gAtlLimitdBc                   = globalUserLimit->gATLdBcLimit;
    pVariable->gConfig_Limit.gAtlLimitStatus                = globalUserLimit->gATLdBcLimitStatus;
#endif
    //*******Power Sensor
//    pVariable->gConfig_PowerSensor.gMenu                  = globalUserVariable->gMenu;
//    pVariable->gConfig_PowerSensor.gPowersensorFreq       = globalUserVariable->gPowersensorFreq;
//    pVariable->gConfig_PowerSensor.gPowersensorExtOffset  = globalUserVariable->gPowersensorExtOffset;

    //*******Preset


    //*******System

#if GUIDRAW_CONFIG
    //******GUI Draw Set
    pVariable->gConfig_GuiDrawSet.gridHorStep          = SA_guiDrawSet.gridHorStep;
    pVariable->gConfig_GuiDrawSet.gridVerStep          = SA_guiDrawSet.gridVerStep;
    pVariable->gConfig_GuiDrawSet.limitLineOnCount     = SA_guiDrawSet.limitLineOnCount;
    pVariable->gConfig_GuiDrawSet.markerOnCount        = SA_guiDrawSet.markerOnCount;
    pVariable->gConfig_GuiDrawSet.peakPos              = SA_guiDrawSet.peakPos;
#endif

    //*******Ext Para
    pVariable->gConfig_Ext.SecondaryAction             = globalUserVariable->SecondaryAction;

    //*******Current Work State
    pVariable->gCurrentWorkState                       = globalUserVariable->gCurrentWorkState;
}

void paraSaveLoad::fileSaveLoadParaToStataAndData(_CONFIG_STATE_MSDATA_ *pVariable)
{
    globalUserVariable->gSpecEMMaskType = pVariable->gConfig_Measure.gSpecEMMaskType;
    globalUserVariable->gSpecEMRefRbw = pVariable->gConfig_Measure.gSpecEMRefRbw;
    globalUserVariable->gSpecEMRefChBw = pVariable->gConfig_Measure.gSpecEMRefChBw;
    globalUserVariable->gSpecEMBsPower = pVariable->gConfig_Measure.gSpecEMBsPower;
    //********Measure
    //globalUserVariable->gDemodulationType = pVariable->gConfig_Measure.gDemodulationType;
    globalUserVariable->gChannelBandwidth = pVariable->gConfig_Measure.gChannelBandwidth;
    globalUserVariable->gChannelSpacing   = pVariable->gConfig_Measure.gChannelSpacing;
    globalUserVariable->gOccupied_BW      = pVariable->gConfig_Measure.gOccupiedBW;
    globalUserVariable->gXdB              = pVariable->gConfig_Measure.XdB;

    globalUserVariable->gHighestCHFreq   = pVariable->gConfig_Measure.gHighestCHFreq;
    globalUserVariable->gLowestCHFreq    = pVariable->gConfig_Measure.gLowestCHFreq;
    globalUserVariable->gMultiACPSpacing = pVariable->gConfig_Measure.gMultiACPSpacing;
    globalUserVariable->gMainIntegBW     = pVariable->gConfig_Measure.gMainIntegBW;
    globalUserVariable->gADJIntegBW      = pVariable->gConfig_Measure.gADJIntegBW;
    globalUserVariable->gALTIntegBW      = pVariable->gConfig_Measure.gALTIntegBW;

    memcpy(globalUserVariable->gSpurEMPara,pVariable->gConfig_Measure.gSpurEMPara,sizeof(__SPUR_EM__) * SPUR_EM_DATE_MAX);
    memcpy(globalUserVariable->gSpurEMViewStatus,pVariable->gConfig_Measure.gSpurEMViewStatus,sizeof(qint32) * SA_SPUREM_RANGE_CNT);
    globalUserVariable->gSpurEMAveType    = pVariable->gConfig_Measure.gSpurEMAveType;
    globalUserVariable->gSpurEMReportType = pVariable->gConfig_Measure.gSpurEMReportType;
    globalUserVariable->gMeasureStatus = pVariable->gConfig_Measure.gMeasureStatus;

    memcpy(globalUserVariable->gSpurEMSpur,pVariable->gConfig_Measure.gSpurEMSpur,sizeof(__SPUR_POINT__) * SA_SPUREM_RANGE_CNT*SA_SPUREM_SPUR_CNT);
    memcpy(globalUserVariable->gSpurEMSpurCnt,pVariable->gConfig_Measure.gSpurEMSpurCnt,sizeof(qint32) * SA_SPUREM_RANGE_CNT);
    globalUserVariable->gSpurEMTotalSpurCnt = pVariable->gConfig_Measure.gSpurEMTotalSpurCnt;
    globalUserVariable->gSpurEMCurRangeIndex = pVariable->gConfig_Measure.gSpurEMCurRangeIndex;
    globalUserVariable->gSpurEMCurDrawRangeIndex = pVariable->gConfig_Measure.gSpurEMCurDrawRangeIndex;
    globalUserVariable->gSpurEMCurSpurIndex = pVariable->gConfig_Measure.gSpurEMCurSpurIndex;


    globalUserVariable->gSpecEMDisplay    = pVariable->gConfig_Measure.gSpecEMDisplay;
    globalUserVariable->gSpecEMRefType    = pVariable->gConfig_Measure.gSpecEMRefType;
    memcpy(globalUserVariable->gSpecEMData,pVariable->gConfig_Measure.gSpecEMData,sizeof(__SPEC_EM__) * SA_SPECEM_FREQ_CNT);
    memcpy(globalUserVariable->gSpecEMViewStatus,pVariable->gConfig_Measure.gSpecEMViewStatus,sizeof(qint32) * SA_SPECEM_FREQ_CNT);
#if RESERVE_0327
    //********Freq Span
    /*globalUserVariable->gStartFreq      = pVariable->gConfig_FreqSpan.gStartFreq;
    globalUserVariable->gStopFreq         = pVariable->gConfig_FreqSpan.gStopFreq;
    globalUserVariable->gCenterFreq       = pVariable->gConfig_FreqSpan.gCenterFreq;*/
    globalUserVariable->gStepFreq         = pVariable->gConfig_FreqSpan.gStepFreq;
    globalUserVariable->gfreqOffset       = pVariable->gConfig_FreqSpan.gfreqOffset;

    globalUserVariable->gSpanFreq         = pVariable->gConfig_FreqSpan.gSpanFreq;
    globalUserVariable->gLastSpanFreq     = pVariable->gConfig_FreqSpan.gLastSpanFreq;
    globalUserVariable->gZeroSpanAction   = pVariable->gConfig_FreqSpan.gZeroSpanAction;
    globalUserVariable->gCFFreq           = pVariable->gConfig_FreqSpan.gCFFreq;
    globalUserVariable->gSpanMode         = pVariable->gConfig_FreqSpan.gSpanMode;

    /*
    globalUserVariable->gspanChangebyFreq = pVariable->gConfig_FreqSpan.gspanChangebyFreq;
    globalUserVariable->gbitsspan         = pVariable->gConfig_FreqSpan.gbitsspan;
    globalUserVariable->gbithalfsspan     = pVariable->gConfig_FreqSpan.gbithalfsspan;*/

    //*******SA_BW
    globalUserVariable->gVbwtoRbw         = pVariable->gConfig_BW.gVbwtoRbw;
    //globalUserVariable->gAutoVbwtoRbw     = pVariable->gConfig_BW.gAutoVbwtoRbw;
    //globalUserVariable->grbwChangedbyFreq = pVariable->gConfig_BW.grbwChangedbyFreq;

    globalUserVariable->gAutoRbw          = pVariable->gConfig_BW.gAutoRbw;
    globalUserVariable->gAutoVbw          = pVariable->gConfig_BW.gAutoVbw;
    globalUserVariable->gRbw              = pVariable->gConfig_BW.gRbw;
    globalUserVariable->gVbw              = pVariable->gConfig_BW.gVbw;
    globalUserVariable->uIFMode            = pVariable->gConfig_BW.gIFMode;

    //*******Amplitude
    globalUserVariable->gRefLevel         = pVariable->gConfig_Amplitude.gRefLevel;
    globalUserVariable->gRefOffset        = pVariable->gConfig_Amplitude.gRefOffset;
    globalUserVariable->gScaleDiv         = pVariable->gConfig_Amplitude.gScaleDiv;
    globalUserVariable->gAmptdUnit        = pVariable->gConfig_Amplitude.gAmptdUnit;
    globalUserVariable->gAtten            = pVariable->gConfig_Amplitude.gAtten;
    globalUserVariable->gPreamp           = pVariable->gConfig_Amplitude.gPreamp;
    globalUserVariable->gAttenValue       = pVariable->gConfig_Amplitude.gAttenValue;
    globalUserVariable->gAutoAttenTrack   = pVariable->gConfig_Amplitude.gAutoAttenTrack;

    //*******Trace
    memcpy(globalUserVariable->gTraceView,pVariable->gConfig_Trace.gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gViewAction,pVariable->gConfig_Trace.gViewAction,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gTraceType,pVariable->gConfig_Trace.gTraceType,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gTraceAverage,pVariable->gConfig_Trace.gTraceAverage,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gAverageCount,pVariable->gConfig_Trace.gAverageCount,sizeof(qint32)*NUM_TRACE);
    for(qint32 i = 0;i<NUM_TRACE;i++){
        memcpy(globalUserVariable->gTraceMeasureVal[i],pVariable->gConfig_Trace_Data.gTraceMeasureVal[i],sizeof(qreal)*NUM_SWEEP_POINT);
    }
    globalUserVariable->gTraceSelect      = pVariable->gConfig_Trace.gTraceSelect;
    globalUserVariable->gDetectorMode     = pVariable->gConfig_Trace.gDetectorMode;
    globalUserVariable->gTmpDetectorMode  = pVariable->gConfig_Trace.gTmpDetectorMode;
#endif

    //*******Sweep
    globalUserVariable->gSweepType        = pVariable->gConfig_Sweep.gSweepType;
    globalUserVariable->gsweepAuto        = pVariable->gConfig_Sweep.gsweepAuto;
    globalUserVariable->gAutoSweepTime    = pVariable->gConfig_Sweep.gAutoSweepTime;
    globalUserVariable->gSweepTime        = pVariable->gConfig_Sweep.gSweepTime;
    globalUserVariable->gZeroSpanTime     = pVariable->gConfig_Sweep.gZeroSpanTime;
#if 0
    globalUserVariable->gSweepSpeed       = pVariable->gConfig_Sweep.gSweepSpeed;
#endif
    SA_sm_config_sweep->sweepMode         = pVariable->gConfig_Sweep.gSweepmode;
    globalUserVariable->ganamode          = pVariable->gConfig_Sweep.gSweepmode;
    globalUserVariable->gAutoDotSweepTime = pVariable->gConfig_Sweep.gAutoDotSweepTime;
    globalUserVariable->gDotSweepTime     = pVariable->gConfig_Sweep.gDotSweepTime;
    globalUserVariable->gFixDotSweepTime  = pVariable->gConfig_Sweep.gFixDotSweepTime;

#if 1
    //********Gate Sweep
#if 0
    globalUserVariable->gLvlEdgSelect = pVariable->gConfig_Gate_Sweep.gLvlEdgSelect;
    globalUserVariable->gDrCtrlSweepMode = pVariable->gConfig_Gate_Sweep.gDrCtrlSweepMode;
    globalUserVariable->gPrdTrgSynchroSrc = pVariable->gConfig_Gate_Sweep.gPrdTrgSynchroSrc;
    globalUserVariable->gPrdTrgSrcDelay = pVariable->gConfig_Gate_Sweep.gPrdTrgSrcDelay;
    globalUserVariable->gPrdTrigPrvntStatus = pVariable->gConfig_Gate_Sweep.gPrdTrigPrvntStatus;
    globalUserVariable->gPrdTrigPrvntTimes = pVariable->gConfig_Gate_Sweep.gPrdTrigPrvntTimes;
    globalUserVariable->gGateViewStartTime = pVariable->gConfig_Gate_Sweep.gGateViewStartTime;
    globalUserVariable->gGateSweepSpanChange = pVariable->gConfig_Gate_Sweep.gGateSweepSpanChange;
#endif
    globalUserVariable->gDrCtrlSource = pVariable->gConfig_Gate_Sweep.gDrCtrlSource;
    globalUserVariable->gLvlEdgMode   = pVariable->gConfig_Gate_Sweep.gLvlEdgMode;
    globalUserVariable->gDrCtrlSwitch = pVariable->gConfig_Gate_Sweep.gDrCtrlSwitch;
    globalUserVariable->gEdgTrigDely = pVariable->gConfig_Gate_Sweep.gEdgTrigDely;
    globalUserVariable->gEdgTrigDoorWdth = pVariable->gConfig_Gate_Sweep.gEdgTrigDoorWdth;
    globalUserVariable->gEdgTrigPrvntStatus = pVariable->gConfig_Gate_Sweep.gEdgTrigPrvntStatus;
    globalUserVariable->gEdgTrigPrvntTimes = pVariable->gConfig_Gate_Sweep.gEdgTrigPrvntTimes;
    globalUserVariable->gRFBurstTrigLevel = pVariable->gConfig_Gate_Sweep.gRFBurstTrigLevel;
    globalUserVariable->gPrdTrgPeriod = pVariable->gConfig_Gate_Sweep.gPrdTrgPeriod;
    globalUserVariable->gDrCtrlRbw = pVariable->gConfig_Gate_Sweep.gDrCtrlRbw;
    globalUserVariable->gGateViewStatus = pVariable->gConfig_Gate_Sweep.gGateViewStatus;
#endif

    //*******Trigger
    globalUserVariable->gTriggerMode      = pVariable->gConfig_Trigger.gTriggerMode;
    globalUserVariable->gTriggerPerTimer  = pVariable->gConfig_Trigger.gTriggerPerTimer;
    memcpy(globalUserVariable->gTriggerLevel,pVariable->gConfig_Trigger.gTriggerLevel,sizeof(qreal) * TRIGGER_SOURCE_CNT);
    memcpy(globalUserVariable->gTriggerSlope,pVariable->gConfig_Trigger.gTriggerSlope,sizeof(qint32) * TRIGGER_SOURCE_CNT);
    memcpy(globalUserVariable->gTriggerDelayStatus,pVariable->gConfig_Trigger.gTriggerDelayStatus,sizeof(qint32) * TRIGGER_SOURCE_CNT);
    memcpy(globalUserVariable->gTriggerDelayValue,pVariable->gConfig_Trigger.gTriggerDelayValue,sizeof(qreal) * TRIGGER_SOURCE_CNT);
    globalUserVariable->calData           = pVariable->gConfig_Trigger.gCalData;

    //*******Marker
    globalUserVariable->gPeakTrack        = pVariable->gConfig_Marker.gPeakTrack;
    globalUserVariable->gMarkerSelect     = pVariable->gConfig_Marker.gMarkerSelect;
    globalUserVariable->gMarkerDisplay    = pVariable->gConfig_Marker.gMarkerDisplay;
    memcpy(globalUserVariable->gMarkerView,pVariable->gConfig_Marker.gMarkerView,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerType,pVariable->gConfig_Marker.gMarkerType,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerRefFreq,pVariable->gConfig_Marker.gMarkerRefFreq,sizeof(quint64)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerRefPos,pVariable->gConfig_Marker.gMarkerRefPos,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerDeltaFreq,pVariable->gConfig_Marker.gMarkerDeltaFreq,sizeof(quint64)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerDeltaPos,pVariable->gConfig_Marker.gMarkerDeltaPos,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerNoise,pVariable->gConfig_Marker.gMarkerNoise,sizeof(qint32)*MARKER_TOTAL_CNT);
    globalUserVariable->gMarkerFreqCount = pVariable->gConfig_Marker.gMarkerFreqCount;
    memcpy(globalUserVariable->gMarkerTmpRefAmpt,pVariable->gConfig_Marker.gMarkerTmpRefAmpt,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerMarkerTmpRefPos,pVariable->gConfig_Marker.gMarkerMarkerTmpRefPos,sizeof(qreal)*MARKER_TOTAL_CNT);
#if PADD
    memcpy(globalUserVariable->gMarkerRefTime,pVariable->gConfig_Marker.gMarkerRefTime,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerDeltaTime,pVariable->gConfig_Marker.gMarkerDeltaTime,sizeof(qreal)*MARKER_TOTAL_CNT);
#endif
    //*******Peak


    //*******Limit
    for(qint32 i = 0;i<LIMIT_SELECTSUM;i++){
        globalUserLimit->gLimitLine[i]        = pVariable->gConfig_Limit.gLimitLine[i];
        globalUserLimit->gLimitEdge[i]        = pVariable->gConfig_Limit.gLimitEdge[i];
        globalUserLimit->gLimitEdgeValue[i]   = pVariable->gConfig_Limit.gLimitEdgeValue[i];
        globalUserLimit->gLatestLimitType[i]  = pVariable->gConfig_Limit.gLatestLimitType[i];
        globalUserLimit->gTotalDot[i]         = pVariable->gConfig_Limit.gTotalDot[i];

        globalUserLimit->gLatestLimitTestResult[i]      = pVariable->gConfig_Limit_Data.gLatestLimitTestResult[i];
        globalUserLimit->gLatestLimitEdgeResult[i]      = pVariable->gConfig_Limit_Data.gLatestLimitEdgeResult[i];

        memcpy(globalUserLimit->gXIndex[i],pVariable->gConfig_Limit.gXIndex[i],sizeof(qint32)*pVariable->gConfig_Limit.gTotalDot[i]);
        memcpy(globalUserLimit->gXAxis[i],pVariable->gConfig_Limit_Data.gXAxis[i],sizeof(qint32)*pVariable->gConfig_Limit.gTotalDot[i]);
        memcpy(globalUserLimit->gYAxis[i],pVariable->gConfig_Limit_Data.gYAxis[i],sizeof(qint32)*pVariable->gConfig_Limit.gTotalDot[i]);
        memcpy(globalUserLimit->gEdgeYAxis[i],pVariable->gConfig_Limit.gEdgeYAxis[i],sizeof(qint32)*pVariable->gConfig_Limit.gTotalDot[i]);
        memcpy(globalUserLimit->gFreq[i],pVariable->gConfig_Limit.gFreq[i],sizeof(qreal)*pVariable->gConfig_Limit.gTotalDot[i]);
        memcpy(globalUserLimit->gAmplitude[i],pVariable->gConfig_Limit.gAmplitude[i],sizeof(qreal)*pVariable->gConfig_Limit.gTotalDot[i]);

        memcpy(globalUserLimit->gLatestLimitDrawPoint[i],pVariable->gConfig_Limit_Data.gLatestLimitDrawPoint[i],sizeof(qint32)*NUM_SWEEP_POINT);
        memcpy(globalUserLimit->gLatestLimitEdgeDrawPoint[i],pVariable->gConfig_Limit_Data.gLatestLimitEdgeDrawPoint[i],sizeof(qint32)*NUM_SWEEP_POINT);
    }
    globalUserLimit->gLimitTest = pVariable->gConfig_Limit.gLimitTest;
    memcpy(globalUserLimit->gLatestLimitUpperDrawPoint,pVariable->gConfig_Limit_Data.gLatestLimitUpperDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);
    memcpy(globalUserLimit->gLatestLimitLowerDrawPoint,pVariable->gConfig_Limit_Data.gLatestLimitLowerDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);
    memcpy(globalUserLimit->gLatestLimitUpperEdgeDrawPoint,pVariable->gConfig_Limit_Data.gLatestLimitUpperEdgeDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);
    memcpy(globalUserLimit->gLatestLimitLowerEdgeDrawPoint,pVariable->gConfig_Limit_Data.gLatestLimitLowerEdgeDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);

    globalUserLimit->gLimitSelect = pVariable->gConfig_Limit.gLimitSelect;

#ifdef SAMPLE_LIMIT
    //*******Upper & Lower Limit
    globalUserLimit->gUpperLimit  =  pVariable->gConfig_Limit.gUpperLimitAmpt;
    globalUserLimit->gLowerLimit  =  pVariable->gConfig_Limit.gLowerLimitAmpt;
    globalUserLimit->gUpperLimit  =  pVariable->gConfig_Limit.gUpperLimitAmpt;
    globalUserLimit->gLowerLimit  =  pVariable->gConfig_Limit.gLowerLimitAmpt;
    globalUserLimit->gUpperLimitStatus = pVariable->gConfig_Limit.gUpperLimitStatus;
    globalUserLimit->gLowerLimitStatus = pVariable->gConfig_Limit.gLowerLimitStatus;
    globalUserLimit->gATLdBcLimit = pVariable->gConfig_Limit.gAtlLimitdBc;
    globalUserLimit->gATLdBcLimitStatus = pVariable->gConfig_Limit.gAtlLimitStatus;


#endif
    //*******Power Sensor
//    globalUserVariable->gMenu                  = pVariable->gConfig_PowerSensor.gMenu;
//    globalUserVariable->gPowersensorFreq       = pVariable->gConfig_PowerSensor.gPowersensorFreq;
//    globalUserVariable->gPowersensorExtOffset  = pVariable->gConfig_PowerSensor.gPowersensorExtOffset;

    //*******Preset


    //*******System


#if GUIDRAW_CONFIG
    //******GUI Draw Set
    SA_guiDrawSet.gridHorStep      = pVariable->gConfig_GuiDrawSet.gridHorStep;
    SA_guiDrawSet.gridVerStep      = pVariable->gConfig_GuiDrawSet.gridVerStep;
    SA_guiDrawSet.limitLineOnCount = pVariable->gConfig_GuiDrawSet.limitLineOnCount;
    SA_guiDrawSet.markerOnCount    = pVariable->gConfig_GuiDrawSet.markerOnCount;
    SA_guiDrawSet.peakPos          = pVariable->gConfig_GuiDrawSet.peakPos;
#endif

    //*******Ext Para
    globalUserVariable->SecondaryAction = pVariable->gConfig_Ext.SecondaryAction;

    //*******Current Work State
    globalUserVariable->gCurrentWorkState = pVariable->gCurrentWorkState;
    //Marker Data
    memcpy(globalUserVariable->gMarkerRefAmpt,pVariable->gConfig_Marker_Data.gMarkerRefAmpt,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerDeltaAmpt,pVariable->gConfig_Marker_Data.gMarkerDeltaAmpt,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerTmpRefAmpt,pVariable->gConfig_Marker_Data.gMarkerTmpRefAmpt,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerMarkerTmpRefPos,pVariable->gConfig_Marker_Data.gMarkerMarkerTmpRefPos,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(globalUserVariable->gMarkerNoiseValue,pVariable->gConfig_Marker_Data.gMarkerNoiseValue,sizeof(qreal)*MARKER_TOTAL_CNT);

}
void paraSaveLoad::StataAndDataTofileSaveLoadPara(_CONFIG_STATE_MSDATA_ *pVariable)
{
    pVariable->gConfig_Measure.gSpecEMMaskType = globalUserVariable->gSpecEMMaskType;
    pVariable->gConfig_Measure.gSpecEMRefRbw = globalUserVariable->gSpecEMRefRbw;
    pVariable->gConfig_Measure.gSpecEMRefChBw = globalUserVariable->gSpecEMRefChBw;
    pVariable->gConfig_Measure.gSpecEMBsPower = globalUserVariable->gSpecEMBsPower;
    //********Measure
    //pVariable->gConfig_Measure.gDemodulationType  = globalUserVariable->gDemodulationType;
    pVariable->gConfig_Measure.gChannelBandwidth  = globalUserVariable->gChannelBandwidth;
    pVariable->gConfig_Measure.gChannelSpacing    = globalUserVariable->gChannelSpacing;
    pVariable->gConfig_Measure.gOccupiedBW        = globalUserVariable->gOccupied_BW;
    pVariable->gConfig_Measure.XdB                = globalUserVariable->gXdB;

    pVariable->gConfig_Measure.gHighestCHFreq   = globalUserVariable->gHighestCHFreq;
    pVariable->gConfig_Measure.gLowestCHFreq    = globalUserVariable->gLowestCHFreq;
    pVariable->gConfig_Measure.gMultiACPSpacing = globalUserVariable->gMultiACPSpacing;
    pVariable->gConfig_Measure.gMainIntegBW     = globalUserVariable->gMainIntegBW;
    pVariable->gConfig_Measure.gADJIntegBW      = globalUserVariable->gADJIntegBW;
    pVariable->gConfig_Measure.gALTIntegBW      = globalUserVariable->gALTIntegBW;

    memcpy(pVariable->gConfig_Measure.gSpurEMPara,globalUserVariable->gSpurEMPara,sizeof(__SPUR_EM__) * SPUR_EM_DATE_MAX);
    memcpy(pVariable->gConfig_Measure.gSpurEMViewStatus,globalUserVariable->gSpurEMViewStatus,sizeof(qint32) * SA_SPUREM_RANGE_CNT);
    pVariable->gConfig_Measure.gSpurEMAveType    = globalUserVariable->gSpurEMAveType;
    pVariable->gConfig_Measure.gSpurEMReportType = globalUserVariable->gSpurEMReportType;
    pVariable->gConfig_Measure.gMeasureStatus = globalUserVariable->gMeasureStatus;

    memcpy(pVariable->gConfig_Measure.gSpurEMSpur,globalUserVariable->gSpurEMSpur,sizeof(__SPUR_POINT__) * SA_SPUREM_RANGE_CNT*SA_SPUREM_SPUR_CNT);
    memcpy(pVariable->gConfig_Measure.gSpurEMSpurCnt,globalUserVariable->gSpurEMSpurCnt,sizeof(qint32) * SA_SPUREM_RANGE_CNT);
    pVariable->gConfig_Measure.gSpurEMTotalSpurCnt = globalUserVariable->gSpurEMTotalSpurCnt;
    pVariable->gConfig_Measure.gSpurEMCurRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    pVariable->gConfig_Measure.gSpurEMCurDrawRangeIndex = globalUserVariable->gSpurEMCurDrawRangeIndex;
    pVariable->gConfig_Measure.gSpurEMCurSpurIndex = globalUserVariable->gSpurEMCurSpurIndex;

    pVariable->gConfig_Measure.gSpecEMDisplay    = globalUserVariable->gSpecEMDisplay;
    pVariable->gConfig_Measure.gSpecEMRefType    = globalUserVariable->gSpecEMRefType;
    memcpy(pVariable->gConfig_Measure.gSpecEMData,globalUserVariable->gSpecEMData,sizeof(__SPEC_EM__) * SA_SPECEM_FREQ_CNT);
    memcpy(pVariable->gConfig_Measure.gSpecEMViewStatus,globalUserVariable->gSpecEMViewStatus,sizeof(qint32) * SA_SPECEM_FREQ_CNT);
#if RESERVE_0327
    //********Freq Span
    /*pVariable->gConfig_FreqSpan.gStartFreq      = globalUserVariable->gStartFreq;
    pVariable->gConfig_FreqSpan.gStopFreq         = globalUserVariable->gStopFreq;
    pVariable->gConfig_FreqSpan.gCenterFreq       = globalUserVariable->gCenterFreq;*/
    pVariable->gConfig_FreqSpan.gStepFreq         = globalUserVariable->gStepFreq;
    pVariable->gConfig_FreqSpan.gfreqOffset       = globalUserVariable->gfreqOffset;

    pVariable->gConfig_FreqSpan.gSpanFreq         = globalUserVariable->gSpanFreq;
    pVariable->gConfig_FreqSpan.gLastSpanFreq     = globalUserVariable->gLastSpanFreq;
    pVariable->gConfig_FreqSpan.gCFFreq           = globalUserVariable->gCFFreq;
    pVariable->gConfig_FreqSpan.gSpanMode         = globalUserVariable->gSpanMode;
    pVariable->gConfig_FreqSpan.gZeroSpanAction   = globalUserVariable->gZeroSpanAction;

    /*
    pVariable->gConfig_FreqSpan.gspanChangebyFreq = globalUserVariable->gspanChangebyFreq;
    pVariable->gConfig_FreqSpan.gbitsspan         = globalUserVariable->gbitsspan;
    pVariable->gConfig_FreqSpan.gbithalfsspan     = globalUserVariable->gbithalfsspan;*/

    //*******SA_BW
    pVariable->gConfig_BW.gVbwtoRbw         = globalUserVariable->gVbwtoRbw;
    //pVariable->gConfig_BW.gAutoVbwtoRbw     = globalUserVariable->gAutoVbwtoRbw;
    //pVariable->gConfig_BW.grbwChangedbyFreq = globalUserVariable->grbwChangedbyFreq;

    pVariable->gConfig_BW.gAutoRbw          = globalUserVariable->gAutoRbw;
    pVariable->gConfig_BW.gAutoVbw          = globalUserVariable->gAutoVbw;
    pVariable->gConfig_BW.gRbw              = globalUserVariable->gRbw;
    pVariable->gConfig_BW.gVbw              = globalUserVariable->gVbw;
    pVariable->gConfig_BW.gIFMode           = globalUserVariable->uIFMode;

    //*******Amplitude
    pVariable->gConfig_Amplitude.gRefLevel         = globalUserVariable->gRefLevel;
    pVariable->gConfig_Amplitude.gRefOffset        = globalUserVariable->gRefOffset;
    pVariable->gConfig_Amplitude.gScaleDiv         = globalUserVariable->gScaleDiv;
    pVariable->gConfig_Amplitude.gAmptdUnit        = globalUserVariable->gAmptdUnit;
    pVariable->gConfig_Amplitude.gAtten            = globalUserVariable->gAtten;
    pVariable->gConfig_Amplitude.gPreamp           = globalUserVariable->gPreamp;
    pVariable->gConfig_Amplitude.gAttenValue       = globalUserVariable->gAttenValue;
    pVariable->gConfig_Amplitude.gAutoAttenTrack   = globalUserVariable->gAutoAttenTrack;

    //*******Trace
    memcpy(pVariable->gConfig_Trace.gTraceView,globalUserVariable->gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(pVariable->gConfig_Trace.gViewAction,globalUserVariable->gViewAction,sizeof(qint32)*NUM_TRACE);
    memcpy(pVariable->gConfig_Trace.gTraceType,globalUserVariable->gTraceType,sizeof(qint32)*NUM_TRACE);
    memcpy(pVariable->gConfig_Trace.gTraceAverage,globalUserVariable->gTraceAverage,sizeof(qint32)*NUM_TRACE);
    memcpy(pVariable->gConfig_Trace.gAverageCount,globalUserVariable->gAverageCount,sizeof(qint32)*NUM_TRACE);
    for(qint32 i = 0;i<NUM_TRACE;i++){
        memcpy(pVariable->gConfig_Trace_Data.gTraceMeasureVal[i],globalUserVariable->gTraceMeasureVal[i],sizeof(qreal)*NUM_SWEEP_POINT);
    }
    pVariable->gConfig_Trace.gTraceSelect      = globalUserVariable->gTraceSelect;
    pVariable->gConfig_Trace.gDetectorMode     = globalUserVariable->gDetectorMode;
    pVariable->gConfig_Trace.gTmpDetectorMode  = globalUserVariable->gTmpDetectorMode;
#endif

    //*******Sweep
    pVariable->gConfig_Sweep.gSweepType        = globalUserVariable->gSweepType;
    pVariable->gConfig_Sweep.gsweepAuto        = globalUserVariable->gsweepAuto;
    pVariable->gConfig_Sweep.gAutoSweepTime    = globalUserVariable->gAutoSweepTime;
    pVariable->gConfig_Sweep.gSweepTime        = globalUserVariable->gSweepTime;
    pVariable->gConfig_Sweep.gZeroSpanTime     = globalUserVariable->gZeroSpanTime;
#if 0
    pVariable->gConfig_Sweep.gSweepSpeed       = globalUserVariable->gSweepSpeed;
#endif
    pVariable->gConfig_Sweep.gSweepmode        = SA_sm_config_sweep->sweepMode;
    pVariable->gConfig_Sweep.gAutoDotSweepTime = globalUserVariable->gAutoDotSweepTime;
    pVariable->gConfig_Sweep.gDotSweepTime     = globalUserVariable->gDotSweepTime;
    pVariable->gConfig_Sweep.gFixDotSweepTime  = globalUserVariable->gFixDotSweepTime;

#if 1
    //********Gate Sweep
#if 0
    pVariable->gConfig_Gate_Sweep.gLvlEdgSelect        = globalUserVariable->gLvlEdgSelect;
    pVariable->gConfig_Gate_Sweep.gDrCtrlSweepMode        = globalUserVariable->gDrCtrlSweepMode;
    pVariable->gConfig_Gate_Sweep.gPrdTrgSynchroSrc     = globalUserVariable->gPrdTrgSynchroSrc;
    pVariable->gConfig_Gate_Sweep.gPrdTrgSrcDelay        = globalUserVariable->gPrdTrgSrcDelay;
    pVariable->gConfig_Gate_Sweep.gPrdTrigPrvntStatus     = globalUserVariable->gPrdTrigPrvntStatus;
    pVariable->gConfig_Gate_Sweep.gPrdTrigPrvntTimes       = globalUserVariable->gPrdTrigPrvntTimes;
    pVariable->gConfig_Gate_Sweep.gGateViewStartTime     = globalUserVariable->gGateViewStartTime;
    pVariable->gConfig_Gate_Sweep.gGateSweepSpanChange = globalUserVariable->gGateSweepSpanChange;
#endif
    pVariable->gConfig_Gate_Sweep.gDrCtrlSource        = globalUserVariable->gDrCtrlSource;
    pVariable->gConfig_Gate_Sweep.gLvlEdgMode    = globalUserVariable->gLvlEdgMode;
    pVariable->gConfig_Gate_Sweep.gDrCtrlSwitch       = globalUserVariable->gDrCtrlSwitch;
    pVariable->gConfig_Gate_Sweep.gEdgTrigDely        = globalUserVariable->gEdgTrigDely;
    pVariable->gConfig_Gate_Sweep.gEdgTrigDoorWdth = globalUserVariable->gEdgTrigDoorWdth;
    pVariable->gConfig_Gate_Sweep.gEdgTrigPrvntStatus     = globalUserVariable->gEdgTrigPrvntStatus;
    pVariable->gConfig_Gate_Sweep.gEdgTrigPrvntTimes        = globalUserVariable->gEdgTrigPrvntTimes;
    pVariable->gConfig_Gate_Sweep.gRFBurstTrigLevel        = globalUserVariable->gRFBurstTrigLevel;
    pVariable->gConfig_Gate_Sweep.gPrdTrgPeriod    = globalUserVariable->gPrdTrgPeriod;
    pVariable->gConfig_Gate_Sweep.gDrCtrlRbw        = globalUserVariable->gDrCtrlRbw;
    pVariable->gConfig_Gate_Sweep.gGateViewStatus     = globalUserVariable->gGateViewStatus;
#endif

    //*******Trigger
    pVariable->gConfig_Trigger.gTriggerMode    = globalUserVariable->gTriggerMode;
    pVariable->gConfig_Trigger.gTriggerPerTimer = globalUserVariable->gTriggerPerTimer;
    memcpy(pVariable->gConfig_Trigger.gTriggerLevel,globalUserVariable->gTriggerLevel,sizeof(qreal) * TRIGGER_SOURCE_CNT);
    memcpy(pVariable->gConfig_Trigger.gTriggerSlope,globalUserVariable->gTriggerSlope,sizeof(qint32) * TRIGGER_SOURCE_CNT);
    memcpy(pVariable->gConfig_Trigger.gTriggerDelayStatus,globalUserVariable->gTriggerDelayStatus,sizeof(qint32) * TRIGGER_SOURCE_CNT);
    memcpy(pVariable->gConfig_Trigger.gTriggerDelayValue,globalUserVariable->gTriggerDelayValue,sizeof(qreal) * TRIGGER_SOURCE_CNT);
    pVariable->gConfig_Trigger.gCalData        = globalUserVariable->calData;

    //*******Marker
    pVariable->gConfig_Marker.gPeakTrack        = globalUserVariable->gPeakTrack;
    pVariable->gConfig_Marker.gMarkerSelect     = globalUserVariable->gMarkerSelect;
    pVariable->gConfig_Marker.gMarkerDisplay    = globalUserVariable->gMarkerDisplay;
    memcpy(pVariable->gConfig_Marker.gMarkerView,globalUserVariable->gMarkerView,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerType,globalUserVariable->gMarkerType,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerRefFreq,globalUserVariable->gMarkerRefFreq,sizeof(quint64)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerRefPos,globalUserVariable->gMarkerRefPos,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerDeltaFreq,globalUserVariable->gMarkerDeltaFreq,sizeof(quint64)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerDeltaPos,globalUserVariable->gMarkerDeltaPos,sizeof(qint32)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerNoise,globalUserVariable->gMarkerNoise,sizeof(qint32)*MARKER_TOTAL_CNT);
    pVariable->gConfig_Marker.gMarkerFreqCount = globalUserVariable->gMarkerFreqCount;
    memcpy(pVariable->gConfig_Marker.gMarkerTmpRefAmpt,globalUserVariable->gMarkerTmpRefAmpt,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerMarkerTmpRefPos,globalUserVariable->gMarkerMarkerTmpRefPos,sizeof(qreal)*MARKER_TOTAL_CNT);
#if PADD
    memcpy(pVariable->gConfig_Marker.gMarkerRefTime,globalUserVariable->gMarkerRefTime,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker.gMarkerDeltaTime,globalUserVariable->gMarkerDeltaTime,sizeof(qreal)*MARKER_TOTAL_CNT);
#endif
    //*******Peak


    //*******Limit
    for(qint32 i = 0;i<LIMIT_SELECTSUM;i++){
        pVariable->gConfig_Limit.gLimitLine[i]        = globalUserLimit->gLimitLine[i];
        pVariable->gConfig_Limit.gLimitEdge[i]        = globalUserLimit->gLimitEdge[i];
        pVariable->gConfig_Limit.gLimitEdgeValue[i]   = globalUserLimit->gLimitEdgeValue[i];
        pVariable->gConfig_Limit.gLatestLimitType[i]  = globalUserLimit->gLatestLimitType[i];
        pVariable->gConfig_Limit.gTotalDot[i]         = globalUserLimit->gTotalDot[i];

        pVariable->gConfig_Limit_Data.gLatestLimitTestResult[i]      = globalUserLimit->gLatestLimitTestResult[i];
        pVariable->gConfig_Limit_Data.gLatestLimitEdgeResult[i]      = globalUserLimit->gLatestLimitEdgeResult[i];

        memcpy(pVariable->gConfig_Limit.gXIndex[i],globalUserLimit->gXIndex[i],sizeof(qint32)*globalUserLimit->gTotalDot[i]);
        memcpy(pVariable->gConfig_Limit_Data.gXAxis[i],globalUserLimit->gXAxis[i],sizeof(qint32)*globalUserLimit->gTotalDot[i]);
        memcpy(pVariable->gConfig_Limit_Data.gYAxis[i],globalUserLimit->gYAxis[i],sizeof(qint32)*globalUserLimit->gTotalDot[i]);
        memcpy(pVariable->gConfig_Limit.gEdgeYAxis[i],globalUserLimit->gEdgeYAxis[i],sizeof(qint32)*globalUserLimit->gTotalDot[i]);
        memcpy(pVariable->gConfig_Limit.gFreq[i],globalUserLimit->gFreq[i],sizeof(qreal)*globalUserLimit->gTotalDot[i]);
        memcpy(pVariable->gConfig_Limit.gAmplitude[i],globalUserLimit->gAmplitude[i],sizeof(qreal)*globalUserLimit->gTotalDot[i]);


        memcpy(pVariable->gConfig_Limit_Data.gLatestLimitDrawPoint[i],globalUserLimit->gLatestLimitDrawPoint[i],sizeof(qint32)*NUM_SWEEP_POINT);
        memcpy(pVariable->gConfig_Limit_Data.gLatestLimitEdgeDrawPoint[i],globalUserLimit->gLatestLimitEdgeDrawPoint[i],sizeof(qint32)*NUM_SWEEP_POINT);
    }
    pVariable->gConfig_Limit.gLimitTest = globalUserLimit->gLimitTest;
    memcpy(pVariable->gConfig_Limit_Data.gLatestLimitUpperDrawPoint,globalUserLimit->gLatestLimitUpperDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);
    memcpy(pVariable->gConfig_Limit_Data.gLatestLimitLowerDrawPoint,globalUserLimit->gLatestLimitLowerDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);
    memcpy(pVariable->gConfig_Limit_Data.gLatestLimitUpperEdgeDrawPoint,globalUserLimit->gLatestLimitUpperEdgeDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);
    memcpy(pVariable->gConfig_Limit_Data.gLatestLimitLowerEdgeDrawPoint,globalUserLimit->gLatestLimitLowerEdgeDrawPoint,sizeof(qint32)*NUM_SWEEP_POINT);

    pVariable->gConfig_Limit.gLimitSelect                = globalUserLimit->gLimitSelect;

#ifdef SAMPLE_LIMIT
    //*******Upper & Lower Limit
    pVariable->gConfig_Limit.gUpperLimitAmpt                = globalUserLimit->gUpperLimit;
    pVariable->gConfig_Limit.gLowerLimitAmpt                = globalUserLimit->gLowerLimit;
    pVariable->gConfig_Limit.gUpperLimitStatus                = globalUserLimit->gUpperLimitStatus;
    pVariable->gConfig_Limit.gLowerLimitStatus                = globalUserLimit->gLowerLimitStatus;

    pVariable->gConfig_Limit.gAtlLimitdBc                   = globalUserLimit->gATLdBcLimit;
    pVariable->gConfig_Limit.gAtlLimitStatus                = globalUserLimit->gATLdBcLimitStatus;

    pVariable->gConfig_Limit.gUpperLimitAmpt                = globalUserLimit->gUpperLimit;
    pVariable->gConfig_Limit.gLowerLimitAmpt                = globalUserLimit->gLowerLimit;
#endif

    //*******Power Sensor
//    pVariable->gConfig_PowerSensor.gMenu                  = globalUserVariable->gMenu;
//    pVariable->gConfig_PowerSensor.gPowersensorFreq       = globalUserVariable->gPowersensorFreq;
//    pVariable->gConfig_PowerSensor.gPowersensorExtOffset  = globalUserVariable->gPowersensorExtOffset;

    //*******Preset


    //*******System

#if GUIDRAW_CONFIG
    //******GUI Draw Set
    pVariable->gConfig_GuiDrawSet.gridHorStep          = SA_guiDrawSet.gridHorStep;
    pVariable->gConfig_GuiDrawSet.gridVerStep          = SA_guiDrawSet.gridVerStep;
    pVariable->gConfig_GuiDrawSet.limitLineOnCount     = SA_guiDrawSet.limitLineOnCount;
    pVariable->gConfig_GuiDrawSet.markerOnCount        = SA_guiDrawSet.markerOnCount;
    pVariable->gConfig_GuiDrawSet.peakPos              = SA_guiDrawSet.peakPos;
#endif

    //*******Ext Para
    pVariable->gConfig_Ext.SecondaryAction             = globalUserVariable->SecondaryAction;

    //*******Current Work State
    pVariable->gCurrentWorkState                       = globalUserVariable->gCurrentWorkState;
    //Marker Data
    memcpy(pVariable->gConfig_Marker_Data.gMarkerRefAmpt,globalUserVariable->gMarkerRefAmpt,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker_Data.gMarkerDeltaAmpt,globalUserVariable->gMarkerDeltaAmpt,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker_Data.gMarkerTmpRefAmpt,globalUserVariable->gMarkerTmpRefAmpt,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker_Data.gMarkerMarkerTmpRefPos,globalUserVariable->gMarkerMarkerTmpRefPos,sizeof(qreal)*MARKER_TOTAL_CNT);
    memcpy(pVariable->gConfig_Marker_Data.gMarkerNoiseValue,globalUserVariable->gMarkerNoiseValue,sizeof(qreal)*MARKER_TOTAL_CNT);

}

//Tony 19-06-04
/**
 * @brief paraSaveLoad::saveStatefile
 * @note  save state
 */
bool paraSaveLoad::saveStatefile(QString FilePath)
{
    //_ALLMODE_STATE_ pAllModeFileSaveLoad;
    //********Save plugin parameters
    char *strPath =  FilePath.toLatin1().data();
    FILE *pFile;
    pFile = fopen(strPath,"wb");
    paraSave(globalUserVariable->currentMode);

    /*measureStateTofileSaveLoadPara(&pAllModeFileSaveLoad.pACPModeParam);
    measureStateTofileSaveLoadPara(&pAllModeFileSaveLoad.pChnlPowerModeParam);
    measureStateTofileSaveLoadPara(&pAllModeFileSaveLoad.pDemodulationModeParam);
    measureStateTofileSaveLoadPara(&pAllModeFileSaveLoad.pFieldStrengthModeParam);
    measureStateTofileSaveLoadPara(&pAllModeFileSaveLoad.pMultiACPModeParam);
    measureStateTofileSaveLoadPara(&pAllModeFileSaveLoad.pOccupiedModeParam);
    measureStateTofileSaveLoadPara(&pAllModeFileSaveLoad.pSpanModeParam);
    measureStateTofileSaveLoadPara(&pAllModeFileSaveLoad.pSpectrumEmissionMaskModeParam);
    measureStateTofileSaveLoadPara(&pAllModeFileSaveLoad.pSpuriousEmissionMaskModeParam);*/

    memcpy(&(gAllMode_State.pSpanModeParam),&gSpanModeState,sizeof(_CONFIG_STATE_));
    memcpy(&(gAllMode_State.pChnlPowerModeParam),&gChnlPowerModeState,sizeof(_CONFIG_STATE_));
    memcpy(&(gAllMode_State.pOccupiedModeParam),&gOccupiedModeState,sizeof(_CONFIG_STATE_));
    memcpy(&(gAllMode_State.pACPModeParam),&gACPModeState,sizeof(_CONFIG_STATE_));
    memcpy(&(gAllMode_State.pMultiACPModeParam),&gMultiACPModeState,sizeof(_CONFIG_STATE_));
    memcpy(&(gAllMode_State.pSpectrumEmissionMaskModeParam),&gSpectrumEmissionMaskModeState,sizeof(_CONFIG_STATE_));
    memcpy(&(gAllMode_State.pSpuriousEmissionMaskModeParam),&gSpuriousEmissionMaskModeState,sizeof(_CONFIG_STATE_));
    memcpy(&(gAllMode_State.pFieldStrengthModeParam),&gFieldStrengthModeState,sizeof(_CONFIG_STATE_));
    memcpy(&(gAllMode_State.pDemodulationModeParam),&gDemodulationModeState,sizeof(_CONFIG_STATE_));

    gAllMode_State.mSaveLoad_CurrentMode = globalUserVariable->currentMode;
    gAllMode_State.gCenterFreq           = globalUserVariable->gCenterFreq;
    gAllMode_State.gConfig_ShareMem.uAllSweepCompleteFlag = SA_sm_config_sweep->uAllSweepCompleteFlag;
    gAllMode_State.gConfig_ShareMem.uIFMode = globalUserVariable->uIFMode;

#if !RESERVE_0327
    gAllMode_State.gConfig_FreqSpan.gCFFreq = globalUserVariable->gCFFreq;
    gAllMode_State.gConfig_FreqSpan.gfreqOffset = globalUserVariable->gfreqOffset;
    gAllMode_State.gConfig_FreqSpan.gLastSpanFreq = globalUserVariable->gLastSpanFreq;
    gAllMode_State.gConfig_FreqSpan.gSpanFreq = globalUserVariable->gSpanFreq;
    gAllMode_State.gConfig_FreqSpan.gSpanMode = globalUserVariable->gSpanMode;
    gAllMode_State.gConfig_FreqSpan.gStepFreq = globalUserVariable->gStepFreq;
    gAllMode_State.gConfig_FreqSpan.gZeroSpanAction = globalUserVariable->gZeroSpanAction;

    gAllMode_State.gConfig_Amplitude.gAmptdUnit = globalUserVariable->gAmptdUnit;
    gAllMode_State.gConfig_Amplitude.gAtten = globalUserVariable->gAtten;
    gAllMode_State.gConfig_Amplitude.gAttenValue = globalUserVariable->gAttenValue;
    gAllMode_State.gConfig_Amplitude.gAutoAttenTrack = globalUserVariable->gAutoAttenTrack;
    gAllMode_State.gConfig_Amplitude.gPreamp = globalUserVariable->gPreamp;
    gAllMode_State.gConfig_Amplitude.gRefLevel = globalUserVariable->gRefLevel;
    gAllMode_State.gConfig_Amplitude.gRefOffset = globalUserVariable->gRefOffset;
    gAllMode_State.gConfig_Amplitude.gScaleDiv = globalUserVariable->gScaleDiv;

    gAllMode_State.gConfig_BW.gAutoRbw = globalUserVariable->gAutoRbw;
    gAllMode_State.gConfig_BW.gAutoVbw = globalUserVariable->gAutoVbw;
    gAllMode_State.gConfig_BW.gIFMode = globalUserVariable->uIFMode;
    gAllMode_State.gConfig_BW.gRbw = globalUserVariable->gRbw;
    gAllMode_State.gConfig_BW.gVbw = globalUserVariable->gVbw;
    gAllMode_State.gConfig_BW.gVbwtoRbw = globalUserVariable->gVbwtoRbw;

    memcpy(gAllMode_State.gConfig_Trace.gAverageCount,globalUserVariable->gAverageCount,sizeof(qint32)*NUM_TRACE);
    gAllMode_State.gConfig_Trace.gDetectorMode = globalUserVariable->gDetectorMode;
    gAllMode_State.gConfig_Trace.gTmpDetectorMode = globalUserVariable->gTmpDetectorMode;
    memcpy(gAllMode_State.gConfig_Trace.gTraceAverage,globalUserVariable->gTraceAverage,sizeof(qint32)*NUM_TRACE);
    gAllMode_State.gConfig_Trace.gTraceSelect = globalUserVariable->gTraceSelect;
    memcpy(gAllMode_State.gConfig_Trace.gTraceType,globalUserVariable->gTraceType,sizeof(qint32)*NUM_TRACE);
    memcpy(gAllMode_State.gConfig_Trace.gTraceView,globalUserVariable->gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(gAllMode_State.gConfig_Trace.gViewAction,globalUserVariable->gViewAction,sizeof(qint32)*NUM_TRACE);
#endif
#if USABLE
    gAllMode_State.gConfig_ShareMem.uMsCompleteFlag = SA_sm_config_sweep->uMsCompleteFlag;
#endif
    gAllMode_State.gConfig_ShareMem.uSweepCompleteFlag = SA_sm_config_sweep->uSweepCompleteFlag;
    if(!pFile){
        qDebug()<<"Open file fail!";
        setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_AppStateFile_Write);
        errorOutput();
        return false;
    }
    quint64 header = (quint64)SA_FILEHEADER_STATE;

    fwrite(&header,sizeof(header),1,pFile);
    qint32 a =fwrite(&gAllMode_State,sizeof(_ALLMODE_STATE_),1,pFile);
    fflush(pFile);
    fclose(pFile);
    qDebug()<<"Save state success!";
    return true;
}
/**
 * @brief paraSaveLoad::loadStatefile
 * @note  load state
 */
bool paraSaveLoad::loadStatefile( QString FilePath)
{
    quint64 header;
    //_ALLMODE_STATE_ pAllModeFileSaveLoad;
    char *strPath =  FilePath.toLatin1().data();
    FILE *pFile;
    //judge if the preStart module is current module(currentModule index is SA_MODULE(0))
    if(SA_MODULE != globalUserVariable->startMode) sm_startflag->startedflag = START_FLAG;

    pFile = fopen(strPath,"rb");
    if(!pFile){
        qDebug()<<"Open file fail!";
        setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_AppStateFile_Read);
        errorOutput();

        return false;
    }
    fseek(pFile,0,SEEK_END);
    if(!ftell(pFile)){
        qDebug()<<"The file is null!";
        setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_AppStateFile_Null);
        errorOutput();

        fclose(pFile);
        return false;
    }
    fseek(pFile,0,SEEK_SET);

    fread(&header,sizeof(header),1,pFile);
    if(header != (quint64)SA_FILEHEADER_STATE)
    {
        qDebug()<<"The file isn's sa file!";
        setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_AppStateFile_Judge);
        errorOutput();

        fclose(pFile);
        return false;
    }
    fread(&gAllMode_State,sizeof(_ALLMODE_STATE_),1,pFile);
    fclose(pFile);
    qDebug()<<"Load variable success!";

    globalUserVariable->currentMode = gAllMode_State.mSaveLoad_CurrentMode;
    globalUserVariable->gCenterFreq = gAllMode_State.gCenterFreq;
    SA_sm_config_sweep->uAllSweepCompleteFlag = gAllMode_State.gConfig_ShareMem.uAllSweepCompleteFlag ;
    globalUserVariable->uIFMode = gAllMode_State.gConfig_ShareMem.uIFMode;

#if !RESERVE_0327
    globalUserVariable->gCFFreq = gAllMode_State.gConfig_FreqSpan.gCFFreq;
    globalUserVariable->gfreqOffset = gAllMode_State.gConfig_FreqSpan.gfreqOffset;
    globalUserVariable->gLastSpanFreq = gAllMode_State.gConfig_FreqSpan.gLastSpanFreq;
    globalUserVariable->gSpanFreq = gAllMode_State.gConfig_FreqSpan.gSpanFreq;
    globalUserVariable->gSpanMode = gAllMode_State.gConfig_FreqSpan.gSpanMode;
    globalUserVariable->gStepFreq = gAllMode_State.gConfig_FreqSpan.gStepFreq;
    globalUserVariable->gZeroSpanAction = gAllMode_State.gConfig_FreqSpan.gZeroSpanAction;

    globalUserVariable->gAmptdUnit = gAllMode_State.gConfig_Amplitude.gAmptdUnit;
    globalUserVariable->gAtten = gAllMode_State.gConfig_Amplitude.gAtten;
    globalUserVariable->gAttenValue = gAllMode_State.gConfig_Amplitude.gAttenValue;
    globalUserVariable->gAutoAttenTrack = gAllMode_State.gConfig_Amplitude.gAutoAttenTrack;
    globalUserVariable->gPreamp = gAllMode_State.gConfig_Amplitude.gPreamp;
    globalUserVariable->gRefLevel = gAllMode_State.gConfig_Amplitude.gRefLevel;
    globalUserVariable->gRefOffset = gAllMode_State.gConfig_Amplitude.gRefOffset;
    globalUserVariable->gScaleDiv = gAllMode_State.gConfig_Amplitude.gScaleDiv;

    globalUserVariable->gAutoRbw = gAllMode_State.gConfig_BW.gAutoRbw;
    globalUserVariable->gAutoVbw = gAllMode_State.gConfig_BW.gAutoVbw;
    globalUserVariable->uIFMode = gAllMode_State.gConfig_BW.gIFMode;
    globalUserVariable->gRbw = gAllMode_State.gConfig_BW.gRbw;
    globalUserVariable->gVbw = gAllMode_State.gConfig_BW.gVbw;
    globalUserVariable->gVbwtoRbw = gAllMode_State.gConfig_BW.gVbwtoRbw;

    memcpy(globalUserVariable->gAverageCount,gAllMode_State.gConfig_Trace.gAverageCount,sizeof(qint32)*NUM_TRACE);
    globalUserVariable->gDetectorMode = gAllMode_State.gConfig_Trace.gDetectorMode;
    globalUserVariable->gTmpDetectorMode = gAllMode_State.gConfig_Trace.gTmpDetectorMode;
    memcpy(globalUserVariable->gTraceAverage,gAllMode_State.gConfig_Trace.gTraceAverage,sizeof(qint32)*NUM_TRACE);
    globalUserVariable->gTraceSelect = gAllMode_State.gConfig_Trace.gTraceSelect;
    memcpy(globalUserVariable->gTraceType,gAllMode_State.gConfig_Trace.gTraceType,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gTraceView,gAllMode_State.gConfig_Trace.gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gViewAction,gAllMode_State.gConfig_Trace.gViewAction,sizeof(qint32)*NUM_TRACE);
#endif
#if USABLE
    SA_sm_config_sweep->uMsCompleteFlag = gAllMode_State.gConfig_ShareMem.uMsCompleteFlag;
#endif
    SA_sm_config_sweep->uSweepCompleteFlag = gAllMode_State.gConfig_ShareMem.uSweepCompleteFlag;

    switch (globalUserVariable->currentMode) {
    case SA_SPAN_MODE:                   fileSaveLoadParaTomeasureState(&gAllMode_State.pSpanModeParam);                 break;
    case SA_CHNLPOWER_MEASURE_MODE:      fileSaveLoadParaTomeasureState(&gAllMode_State.pChnlPowerModeParam);            break;
    case SA_ACP_MEASURE_MODE:            fileSaveLoadParaTomeasureState(&gAllMode_State.pACPModeParam);                  break;
    case SA_OCCUPIED_BW_MEASURE_MODE:    fileSaveLoadParaTomeasureState(&gAllMode_State.pOccupiedModeParam);             break;
    case SA_SPECTRUM_EMISSION_MASK_MODE: fileSaveLoadParaTomeasureState(&gAllMode_State.pSpectrumEmissionMaskModeParam); break;
    case SA_MULTI_ACP_MODE:              fileSaveLoadParaTomeasureState(&gAllMode_State.pMultiACPModeParam);             break;
    case SA_SPURIOUS_EMISSION_MASK_MODE: fileSaveLoadParaTomeasureState(&gAllMode_State.pSpuriousEmissionMaskModeParam); break;
    case SA_FIELD_STRENGTH_MODE:         fileSaveLoadParaTomeasureState(&gAllMode_State.pFieldStrengthModeParam);        break;
    case SA_DEMODULATION_MODE:           fileSaveLoadParaTomeasureState(&gAllMode_State.pDemodulationModeParam);         break;
    default:                                                                                                             break;
    }

    //*********gAllMode_FileSaveLoadParam to local para and set every mode's flag
    memcpy(&gSpanModeState,&(gAllMode_State.pSpanModeParam),sizeof(_CONFIG_STATE_));
    memcpy(&gChnlPowerModeState,&(gAllMode_State.pChnlPowerModeParam),sizeof(_CONFIG_STATE_));
    memcpy(&gOccupiedModeState,&(gAllMode_State.pOccupiedModeParam),sizeof(_CONFIG_STATE_));
    memcpy(&gACPModeState,&(gAllMode_State.pACPModeParam),sizeof(_CONFIG_STATE_));
    memcpy(&gMultiACPModeState,&(gAllMode_State.pMultiACPModeParam),sizeof(_CONFIG_STATE_));
    memcpy(&gSpectrumEmissionMaskModeState,&(gAllMode_State.pSpectrumEmissionMaskModeParam),sizeof(_CONFIG_STATE_));
    memcpy(&gSpuriousEmissionMaskModeState,&(gAllMode_State.pSpuriousEmissionMaskModeParam),sizeof(_CONFIG_STATE_));
    memcpy(&gFieldStrengthModeState,&(gAllMode_State.pFieldStrengthModeParam),sizeof(_CONFIG_STATE_));
    memcpy(&gDemodulationModeState,&(gAllMode_State.pDemodulationModeParam),sizeof(_CONFIG_STATE_));

    return true;
}
//Tony 19-06-04
/**
 * @brief paraSaveLoad::paraSave
 * @note  save state and data
 */
bool paraSaveLoad::saveStateAndDataFile(QString FilePath)
{
    //_ALL_STATE_MSDATA_ pAllModeFileSaveLoad;
    //********Save plugin parameters
    char *strPath =  FilePath.toLatin1().data();
    FILE *pFile;

    pFile = fopen(strPath,"wb");

    paraSave(globalUserVariable->currentMode);

    gAllModeState_MsData.gConfig_ShareMem.uAllSweepCompleteFlag = SA_sm_config_sweep->uAllSweepCompleteFlag;
    gAllModeState_MsData.gConfig_ShareMem.uIFMode = globalUserVariable->uIFMode;
#if USABLE
    gAllModeState_MsData.gConfig_ShareMem.uMsCompleteFlag = SA_sm_config_sweep->uMsCompleteFlag;
#endif
    gAllModeState_MsData.gConfig_ShareMem.uSweepCompleteFlag = SA_sm_config_sweep->uSweepCompleteFlag;
    /*StataAndDataTofileSaveLoadPara(&pAllModeFileSaveLoad.pACPModeParam);
    StataAndDataTofileSaveLoadPara(&pAllModeFileSaveLoad.pChnlPowerModeParam);
    StataAndDataTofileSaveLoadPara(&pAllModeFileSaveLoad.pDemodulationModeParam);
    StataAndDataTofileSaveLoadPara(&pAllModeFileSaveLoad.pFieldStrengthModeParam);
    StataAndDataTofileSaveLoadPara(&pAllModeFileSaveLoad.pMultiACPModeParam);
    StataAndDataTofileSaveLoadPara(&pAllModeFileSaveLoad.pOccupiedModeParam);
    StataAndDataTofileSaveLoadPara(&pAllModeFileSaveLoad.pSpanModeParam);
    StataAndDataTofileSaveLoadPara(&pAllModeFileSaveLoad.pSpectrumEmissionMaskModeParam);
    StataAndDataTofileSaveLoadPara(&pAllModeFileSaveLoad.pSpuriousEmissionMaskModeParam);*/
    memcpy(&(gAllModeState_MsData.pSpanModeParam),&gSpanModeState_MsData,sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&(gAllModeState_MsData.pChnlPowerModeParam),&gChnlPowerModeState_MsData,sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&(gAllModeState_MsData.pOccupiedModeParam),&gOccupiedModeState_MsData,sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&(gAllModeState_MsData.pACPModeParam),&gACPModeState_MsData,sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&(gAllModeState_MsData.pMultiACPModeParam),&gMultiACPModeState_MsData,sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&(gAllModeState_MsData.pSpectrumEmissionMaskModeParam),&gSpectrumEmissionMaskModeState_MsData,sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&(gAllModeState_MsData.pSpuriousEmissionMaskModeParam),&gSpuriousEmissionMaskModeState_MsData,sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&(gAllModeState_MsData.pFieldStrengthModeParam),&gFieldStrengthModeState_MsData,sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&(gAllModeState_MsData.pDemodulationModeParam),&gDemodulationModeState_MsData,sizeof(_CONFIG_STATE_MSDATA_));

    gAllModeState_MsData.mSaveLoad_CurrentMode = globalUserVariable->currentMode;
    gAllModeState_MsData.gCenterFreq           = globalUserVariable->gCenterFreq;

#if !RESERVE_0327
    gAllModeState_MsData.gConfig_FreqSpan.gCFFreq = globalUserVariable->gCFFreq;
    gAllModeState_MsData.gConfig_FreqSpan.gfreqOffset = globalUserVariable->gfreqOffset;
    gAllModeState_MsData.gConfig_FreqSpan.gLastSpanFreq = globalUserVariable->gLastSpanFreq;
    gAllModeState_MsData.gConfig_FreqSpan.gSpanFreq = globalUserVariable->gSpanFreq;
    gAllModeState_MsData.gConfig_FreqSpan.gSpanMode = globalUserVariable->gSpanMode;
    gAllModeState_MsData.gConfig_FreqSpan.gStepFreq = globalUserVariable->gStepFreq;
    gAllModeState_MsData.gConfig_FreqSpan.gZeroSpanAction = globalUserVariable->gZeroSpanAction;

    gAllModeState_MsData.gConfig_Amplitude.gAmptdUnit = globalUserVariable->gAmptdUnit;
    gAllModeState_MsData.gConfig_Amplitude.gAtten = globalUserVariable->gAtten;
    gAllModeState_MsData.gConfig_Amplitude.gAttenValue = globalUserVariable->gAttenValue;
    gAllModeState_MsData.gConfig_Amplitude.gAutoAttenTrack = globalUserVariable->gAutoAttenTrack;
    gAllModeState_MsData.gConfig_Amplitude.gPreamp = globalUserVariable->gPreamp;
    gAllModeState_MsData.gConfig_Amplitude.gRefLevel = globalUserVariable->gRefLevel;
    gAllModeState_MsData.gConfig_Amplitude.gRefOffset = globalUserVariable->gRefOffset;
    gAllModeState_MsData.gConfig_Amplitude.gScaleDiv = globalUserVariable->gScaleDiv;

    gAllModeState_MsData.gConfig_BW.gAutoRbw = globalUserVariable->gAutoRbw;
    gAllModeState_MsData.gConfig_BW.gAutoVbw = globalUserVariable->gAutoVbw;
    gAllModeState_MsData.gConfig_BW.gIFMode = globalUserVariable->uIFMode;
    gAllModeState_MsData.gConfig_BW.gRbw = globalUserVariable->gRbw;
    gAllModeState_MsData.gConfig_BW.gVbw = globalUserVariable->gVbw;
    gAllModeState_MsData.gConfig_BW.gVbwtoRbw = globalUserVariable->gVbwtoRbw;

    memcpy(gAllModeState_MsData.gConfig_Trace.gAverageCount,globalUserVariable->gAverageCount,sizeof(qint32)*NUM_TRACE);
    gAllModeState_MsData.gConfig_Trace.gDetectorMode = globalUserVariable->gDetectorMode;
    gAllModeState_MsData.gConfig_Trace.gTmpDetectorMode = globalUserVariable->gTmpDetectorMode;
    memcpy(gAllModeState_MsData.gConfig_Trace.gTraceAverage,globalUserVariable->gTraceAverage,sizeof(qint32)*NUM_TRACE);
    gAllModeState_MsData.gConfig_Trace.gTraceSelect = globalUserVariable->gTraceSelect;
    memcpy(gAllModeState_MsData.gConfig_Trace.gTraceType,globalUserVariable->gTraceType,sizeof(qint32)*NUM_TRACE);
    memcpy(gAllModeState_MsData.gConfig_Trace.gTraceView,globalUserVariable->gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(gAllModeState_MsData.gConfig_Trace.gViewAction,globalUserVariable->gViewAction,sizeof(qint32)*NUM_TRACE);
#endif

    if(!pFile){
        qDebug()<<"Open file fail!";
        setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_AppStateAndDataFile_Write);
        errorOutput();

        return false;
    }
    quint64 header = (quint64)SA_FILEHEADER_STATE_DATA;

    fwrite(&header,sizeof(header),1,pFile);
    qint32 a =fwrite(&gAllModeState_MsData,sizeof(_ALL_STATE_MSDATA_),1,pFile);
    fflush(pFile);
    fclose(pFile);
    qDebug()<<"Save state success!";
    return true;
}
/**
 * @brief paraSaveLoad::paraSave
 * @note  load data
 */
bool paraSaveLoad::loadStateAndDataFile(QString FilePath)
{
    //_ALL_STATE_MSDATA_ pAllModeFileSaveLoad;
    quint64 header;
    char *strPath =  FilePath.toLatin1().data();
    FILE *pFile;
    //judge if the preStart module is current module(currentModule index is SA_MODULE(0))
    if(SA_MODULE != globalUserVariable->startMode) sm_startflag->startedflag = START_FLAG;

    pFile = fopen(strPath,"rb");
    if(!pFile){
        qDebug()<<"Open file fail!";
        setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_AppStateAndDataFile_Read);
        errorOutput();

        return false;
    }
    fseek(pFile,0,SEEK_END);
    if(!ftell(pFile)){
        qDebug()<<"The file is null!";
        setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_AppStateAndDataFile_Null);
        errorOutput();

        fclose(pFile);
        return false;
    }
    fseek(pFile,0,SEEK_SET);

    fread(&header,sizeof(header),1,pFile);
    if(header != (quint64)SA_FILEHEADER_STATE_DATA)
    {
        qDebug()<<"The file isn's sa file!";
        setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_AppStateAndDataFile_Judge);
        errorOutput();

        fclose(pFile);
        return false;
    }
    fread(&gAllModeState_MsData,sizeof(_ALL_STATE_MSDATA_),1,pFile);
    fclose(pFile);
    qDebug()<<"Load variable success!";


    globalUserVariable->currentMode = gAllModeState_MsData.mSaveLoad_CurrentMode;
    globalUserVariable->gCenterFreq = gAllModeState_MsData.gCenterFreq;
    SA_sm_config_sweep->uAllSweepCompleteFlag = gAllModeState_MsData.gConfig_ShareMem.uAllSweepCompleteFlag ;
    globalUserVariable->uIFMode = gAllModeState_MsData.gConfig_ShareMem.uIFMode;

#if !RESERVE_0327
    globalUserVariable->gCFFreq = gAllModeState_MsData.gConfig_FreqSpan.gCFFreq;
    globalUserVariable->gfreqOffset = gAllModeState_MsData.gConfig_FreqSpan.gfreqOffset;
    globalUserVariable->gLastSpanFreq = gAllModeState_MsData.gConfig_FreqSpan.gLastSpanFreq;
    globalUserVariable->gSpanFreq = gAllModeState_MsData.gConfig_FreqSpan.gSpanFreq;
    globalUserVariable->gSpanMode = gAllModeState_MsData.gConfig_FreqSpan.gSpanMode;
    globalUserVariable->gStepFreq = gAllModeState_MsData.gConfig_FreqSpan.gStepFreq;
    globalUserVariable->gZeroSpanAction = gAllModeState_MsData.gConfig_FreqSpan.gZeroSpanAction;

    globalUserVariable->gAmptdUnit = gAllModeState_MsData.gConfig_Amplitude.gAmptdUnit;
    globalUserVariable->gAtten = gAllModeState_MsData.gConfig_Amplitude.gAtten;
    globalUserVariable->gAttenValue = gAllModeState_MsData.gConfig_Amplitude.gAttenValue;
    globalUserVariable->gAutoAttenTrack = gAllModeState_MsData.gConfig_Amplitude.gAutoAttenTrack;
    globalUserVariable->gPreamp = gAllModeState_MsData.gConfig_Amplitude.gPreamp;
    globalUserVariable->gRefLevel = gAllModeState_MsData.gConfig_Amplitude.gRefLevel;
    globalUserVariable->gRefOffset = gAllModeState_MsData.gConfig_Amplitude.gRefOffset;
    globalUserVariable->gScaleDiv = gAllModeState_MsData.gConfig_Amplitude.gScaleDiv;

    globalUserVariable->gAutoRbw = gAllModeState_MsData.gConfig_BW.gAutoRbw;
    globalUserVariable->gAutoVbw = gAllModeState_MsData.gConfig_BW.gAutoVbw;
    globalUserVariable->uIFMode = gAllModeState_MsData.gConfig_BW.gIFMode;
    globalUserVariable->gRbw = gAllModeState_MsData.gConfig_BW.gRbw;
    globalUserVariable->gVbw = gAllModeState_MsData.gConfig_BW.gVbw;
    globalUserVariable->gVbwtoRbw = gAllModeState_MsData.gConfig_BW.gVbwtoRbw;

    memcpy(globalUserVariable->gAverageCount,gAllModeState_MsData.gConfig_Trace.gAverageCount,sizeof(qint32)*NUM_TRACE);
    globalUserVariable->gDetectorMode = gAllModeState_MsData.gConfig_Trace.gDetectorMode;
    globalUserVariable->gTmpDetectorMode = gAllModeState_MsData.gConfig_Trace.gTmpDetectorMode;
    memcpy(globalUserVariable->gTraceAverage,gAllModeState_MsData.gConfig_Trace.gTraceAverage,sizeof(qint32)*NUM_TRACE);
    globalUserVariable->gTraceSelect = gAllModeState_MsData.gConfig_Trace.gTraceSelect;
    memcpy(globalUserVariable->gTraceType,gAllModeState_MsData.gConfig_Trace.gTraceType,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gTraceView,gAllModeState_MsData.gConfig_Trace.gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gViewAction,gAllModeState_MsData.gConfig_Trace.gViewAction,sizeof(qint32)*NUM_TRACE);
#endif
#if USABLE
    SA_sm_config_sweep->uMsCompleteFlag = gAllModeState_MsData.gConfig_ShareMem.uMsCompleteFlag;
#endif
    SA_sm_config_sweep->uSweepCompleteFlag = gAllModeState_MsData.gConfig_ShareMem.uSweepCompleteFlag;

    switch (globalUserVariable->currentMode) {
    case SA_SPAN_MODE:                   fileSaveLoadParaToStataAndData(&gAllModeState_MsData.pSpanModeParam);                 break;
    case SA_CHNLPOWER_MEASURE_MODE:      fileSaveLoadParaToStataAndData(&gAllModeState_MsData.pChnlPowerModeParam);            break;
    case SA_ACP_MEASURE_MODE:            fileSaveLoadParaToStataAndData(&gAllModeState_MsData.pACPModeParam);                  break;
    case SA_OCCUPIED_BW_MEASURE_MODE:    fileSaveLoadParaToStataAndData(&gAllModeState_MsData.pOccupiedModeParam);             break;
    case SA_SPECTRUM_EMISSION_MASK_MODE: fileSaveLoadParaToStataAndData(&gAllModeState_MsData.pSpectrumEmissionMaskModeParam); break;
    case SA_MULTI_ACP_MODE:              fileSaveLoadParaToStataAndData(&gAllModeState_MsData.pMultiACPModeParam);             break;
    case SA_SPURIOUS_EMISSION_MASK_MODE: fileSaveLoadParaToStataAndData(&gAllModeState_MsData.pSpuriousEmissionMaskModeParam); break;
    case SA_FIELD_STRENGTH_MODE:         fileSaveLoadParaToStataAndData(&gAllModeState_MsData.pFieldStrengthModeParam);        break;
    case SA_DEMODULATION_MODE:           fileSaveLoadParaToStataAndData(&gAllModeState_MsData.pDemodulationModeParam);         break;
    default:                                                                                                                   break;
    }

    //*********gAllMode_FileSaveLoadParam to local para and set every mode's flag
    memcpy(&gSpanModeState_MsData,&(gAllModeState_MsData.pSpanModeParam),sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&gChnlPowerModeState,&(gAllModeState_MsData.pChnlPowerModeParam),sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&gOccupiedModeState,&(gAllModeState_MsData.pOccupiedModeParam),sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&gACPModeState,&(gAllModeState_MsData.pACPModeParam),sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&gMultiACPModeState,&(gAllModeState_MsData.pMultiACPModeParam),sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&gSpectrumEmissionMaskModeState,&(gAllModeState_MsData.pSpectrumEmissionMaskModeParam),sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&gSpuriousEmissionMaskModeState,&(gAllModeState_MsData.pSpuriousEmissionMaskModeParam),sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&gFieldStrengthModeState,&(gAllModeState_MsData.pFieldStrengthModeParam),sizeof(_CONFIG_STATE_MSDATA_));
    memcpy(&gDemodulationModeState,&(gAllModeState_MsData.pDemodulationModeParam),sizeof(_CONFIG_STATE_MSDATA_));

    return true;
}
void paraSaveLoad::refreshSAConfig(_SA_ALL_CONF_ &remoteConfigData)
{
    globalUserVariable->currentMode = remoteConfigData.mSaveLoad_CurrentMode;
    globalUserVariable->gCenterFreq = remoteConfigData.gCenterFreq;
    SA_sm_config_sweep->uAllSweepCompleteFlag = remoteConfigData.gConfig_ShareMem.uAllSweepCompleteFlag ;
    globalUserVariable->uIFMode = remoteConfigData.gConfig_ShareMem.uIFMode;

#if !RESERVE_0327
    globalUserVariable->gCFFreq = remoteConfigData.gConfig_FreqSpan.gCFFreq;
    globalUserVariable->gfreqOffset = remoteConfigData.gConfig_FreqSpan.gfreqOffset;
    globalUserVariable->gLastSpanFreq = remoteConfigData.gConfig_FreqSpan.gLastSpanFreq;
    globalUserVariable->gSpanFreq = remoteConfigData.gConfig_FreqSpan.gSpanFreq;
    globalUserVariable->gSpanMode = remoteConfigData.gConfig_FreqSpan.gSpanMode;
    globalUserVariable->gStepFreq = remoteConfigData.gConfig_FreqSpan.gStepFreq;
    globalUserVariable->gZeroSpanAction = remoteConfigData.gConfig_FreqSpan.gZeroSpanAction;

    globalUserVariable->gAmptdUnit = remoteConfigData.gConfig_Amplitude.gAmptdUnit;
    globalUserVariable->gAtten = remoteConfigData.gConfig_Amplitude.gAtten;
    globalUserVariable->gAttenValue = remoteConfigData.gConfig_Amplitude.gAttenValue;
    globalUserVariable->gAutoAttenTrack = remoteConfigData.gConfig_Amplitude.gAutoAttenTrack;
    globalUserVariable->gPreamp = remoteConfigData.gConfig_Amplitude.gPreamp;
    globalUserVariable->gRefLevel = remoteConfigData.gConfig_Amplitude.gRefLevel;
    globalUserVariable->gRefOffset = remoteConfigData.gConfig_Amplitude.gRefOffset;
    globalUserVariable->gScaleDiv = remoteConfigData.gConfig_Amplitude.gScaleDiv;

    globalUserVariable->gAutoRbw = remoteConfigData.gConfig_BW.gAutoRbw;
    globalUserVariable->gAutoVbw = remoteConfigData.gConfig_BW.gAutoVbw;
    globalUserVariable->uIFMode = remoteConfigData.gConfig_BW.gIFMode;
    globalUserVariable->gRbw = remoteConfigData.gConfig_BW.gRbw;
    globalUserVariable->gVbw = remoteConfigData.gConfig_BW.gVbw;
    globalUserVariable->gVbwtoRbw = remoteConfigData.gConfig_BW.gVbwtoRbw;

    memcpy(globalUserVariable->gAverageCount,remoteConfigData.gConfig_Trace.gAverageCount,sizeof(qint32)*NUM_TRACE);
    globalUserVariable->gDetectorMode = remoteConfigData.gConfig_Trace.gDetectorMode;
    globalUserVariable->gTmpDetectorMode = remoteConfigData.gConfig_Trace.gTmpDetectorMode;
    memcpy(globalUserVariable->gTraceAverage,remoteConfigData.gConfig_Trace.gTraceAverage,sizeof(qint32)*NUM_TRACE);
    globalUserVariable->gTraceSelect = remoteConfigData.gConfig_Trace.gTraceSelect;
    memcpy(globalUserVariable->gTraceType,remoteConfigData.gConfig_Trace.gTraceType,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gTraceView,remoteConfigData.gConfig_Trace.gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(globalUserVariable->gViewAction,remoteConfigData.gConfig_Trace.gViewAction,sizeof(qint32)*NUM_TRACE);
#endif
#if USABLE
    SA_sm_config_sweep->uMsCompleteFlag = remoteConfigData.gConfig_ShareMem.uMsCompleteFlag;
#endif
    SA_sm_config_sweep->uSweepCompleteFlag = remoteConfigData.gConfig_ShareMem.uSweepCompleteFlag;

    fileSaveLoadParaToStataAndData(&(remoteConfigData.measureModeParam));
}
void paraSaveLoad::getSAParam(_SA_ALL_CONF_ &remoteConfigData)
{
    remoteConfigData.mSaveLoad_CurrentMode = globalUserVariable->currentMode ;
    remoteConfigData.gCenterFreq = globalUserVariable->gCenterFreq;
    remoteConfigData.gConfig_ShareMem.uAllSweepCompleteFlag = SA_sm_config_sweep->uAllSweepCompleteFlag ;
    remoteConfigData.gConfig_ShareMem.uIFMode = globalUserVariable->uIFMode;

#if !RESERVE_0327
    remoteConfigData.gConfig_FreqSpan.gCFFreq = globalUserVariable->gCFFreq;
    remoteConfigData.gConfig_FreqSpan.gfreqOffset = globalUserVariable->gfreqOffset;
    remoteConfigData.gConfig_FreqSpan.gLastSpanFreq = globalUserVariable->gLastSpanFreq;
    remoteConfigData.gConfig_FreqSpan.gSpanFreq = globalUserVariable->gSpanFreq;
    remoteConfigData.gConfig_FreqSpan.gSpanMode = globalUserVariable->gSpanMode;
    remoteConfigData.gConfig_FreqSpan.gStepFreq = globalUserVariable->gStepFreq;
    remoteConfigData.gConfig_FreqSpan.gZeroSpanAction = globalUserVariable->gZeroSpanAction;

    remoteConfigData.gConfig_Amplitude.gAmptdUnit = globalUserVariable->gAmptdUnit;
    remoteConfigData.gConfig_Amplitude.gAtten = globalUserVariable->gAtten;
    remoteConfigData.gConfig_Amplitude.gAttenValue = globalUserVariable->gAttenValue;
    remoteConfigData.gConfig_Amplitude.gAutoAttenTrack = globalUserVariable->gAutoAttenTrack;
    remoteConfigData.gConfig_Amplitude.gPreamp = globalUserVariable->gPreamp;
    remoteConfigData.gConfig_Amplitude.gRefLevel = globalUserVariable->gRefLevel;
    remoteConfigData.gConfig_Amplitude.gRefOffset = globalUserVariable->gRefOffset;
    remoteConfigData.gConfig_Amplitude.gScaleDiv = globalUserVariable->gScaleDiv;

    remoteConfigData.gConfig_BW.gAutoRbw = globalUserVariable->gAutoRbw;
    remoteConfigData.gConfig_BW.gAutoVbw = globalUserVariable->gAutoVbw;
    remoteConfigData.gConfig_BW.gIFMode = globalUserVariable->uIFMode;
    remoteConfigData.gConfig_BW.gRbw = globalUserVariable->gRbw;
    remoteConfigData.gConfig_BW.gVbw = globalUserVariable->gVbw;
    remoteConfigData.gConfig_BW.gVbwtoRbw = globalUserVariable->gVbwtoRbw;

    memcpy(remoteConfigData.gConfig_Trace.gAverageCount,globalUserVariable->gAverageCount,sizeof(qint32)*NUM_TRACE);
    remoteConfigData.gConfig_Trace.gDetectorMode = globalUserVariable->gDetectorMode;
    remoteConfigData.gConfig_Trace.gTmpDetectorMode = globalUserVariable->gTmpDetectorMode;
    memcpy(remoteConfigData.gConfig_Trace.gTraceAverage,globalUserVariable->gTraceAverage,sizeof(qint32)*NUM_TRACE);
    remoteConfigData.gConfig_Trace.gTraceSelect = globalUserVariable->gTraceSelect;
    memcpy(remoteConfigData.gConfig_Trace.gTraceType,globalUserVariable->gTraceType,sizeof(qint32)*NUM_TRACE);
    memcpy(remoteConfigData.gConfig_Trace.gTraceView,globalUserVariable->gTraceView,sizeof(qint32)*NUM_TRACE);
    memcpy(remoteConfigData.gConfig_Trace.gViewAction,globalUserVariable->gViewAction,sizeof(qint32)*NUM_TRACE);
#endif
#if USABLE
    SA_sm_config_sweep->uMsCompleteFlag = remoteConfigData.gConfig_ShareMem.uMsCompleteFlag;
#endif
    remoteConfigData.gConfig_ShareMem.uSweepCompleteFlag = SA_sm_config_sweep->uSweepCompleteFlag;


    StataAndDataTofileSaveLoadPara(&(remoteConfigData.measureModeParam));
}


void paraSaveLoad::saveMeasureState(_MEASURE_STATE_ &measureState)
{
//    return;
    memset(&measureState,0,sizeof(measureState));
    measureState.gFreqSpan.gSpanFreq = globalUserVariable->gSpanFreq;
    measureState.gFreqSpan.gCFFreq = globalUserVariable->gCenterFreq;

    measureState.gSweep.gSweepType        = globalUserVariable->gSweepType;
    measureState.gSweep.gsweepAuto        = globalUserVariable->gsweepAuto;
    measureState.gSweep.gAutoSweepTime    = globalUserVariable->gAutoSweepTime;
    measureState.gSweep.gSweepTime        = globalUserVariable->gSweepTime;
    measureState.gSweep.gZeroSpanTime     = globalUserVariable->gZeroSpanTime;
    measureState.gSweep.gSweepmode        = globalUserVariable->ganamode;
    measureState.gSweep.gAutoDotSweepTime = globalUserVariable->gAutoDotSweepTime;
    measureState.gSweep.gDotSweepTime = globalUserVariable->gDotSweepTime;
    measureState.gSweep.gFixDotSweepTime = globalUserVariable->gFixDotSweepTime;

    measureState.gbw.gAutoRbw = globalUserVariable->gAutoRbw;
    measureState.gbw.gAutoVbw = globalUserVariable->gAutoVbw;
    measureState.gbw.gIFMode = globalUserVariable->uIFMode;
    measureState.gbw.gRbw = globalUserVariable->gRbw;
    measureState.gbw.gVbw = globalUserVariable->gVbw;
    measureState.gbw.gVbwtoRbw = globalUserVariable->gVbwtoRbw;
}

void paraSaveLoad::loadMeasureState(_MEASURE_STATE_ &measureState)
{
//     return;
    if(measureState.gbw.gRbw == 0)
    {
        return;
    }
    globalUserVariable->gCenterFreq = measureState.gFreqSpan.gCFFreq;
    globalUserVariable->gSpanFreq = measureState.gFreqSpan.gSpanFreq;
    globalUserVariable->gSweepType = measureState.gSweep.gSweepType;
    globalUserVariable->gsweepAuto = measureState.gSweep.gsweepAuto;
    globalUserVariable->gAutoSweepTime = measureState.gSweep.gAutoSweepTime;
    globalUserVariable->gSweepTime = measureState.gSweep.gSweepTime;
    globalUserVariable->gZeroSpanTime = measureState.gSweep.gZeroSpanTime;
    globalUserVariable->ganamode = measureState.gSweep.gSweepmode;
    globalUserVariable->gAutoDotSweepTime = measureState.gSweep.gAutoDotSweepTime;
    globalUserVariable->gDotSweepTime = measureState.gSweep.gDotSweepTime;
    globalUserVariable->gFixDotSweepTime = measureState.gSweep.gFixDotSweepTime;

    globalUserVariable->gAutoRbw = measureState.gbw.gAutoRbw;
    globalUserVariable->gAutoVbw = measureState.gbw.gAutoVbw;
    globalUserVariable->uIFMode = measureState.gbw.gIFMode;
    globalUserVariable->gRbw = measureState.gbw.gRbw;
    globalUserVariable->gVbw = measureState.gbw.gVbw;
    globalUserVariable->gVbwtoRbw = measureState.gbw.gVbwtoRbw;

}
