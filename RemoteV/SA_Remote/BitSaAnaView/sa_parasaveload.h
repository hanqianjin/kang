#ifndef SA_PARASAVELOAD_H
#define SA_PARASAVELOAD_H

#include "sa_user_limit.h"
#include "sa_user_variable.h"
#include "file_user_variable.h"

class paraSaveLoad
{
public:
    paraSaveLoad(user_limit &m_user_limit,user_variable &m_user_variable);
    user_limit *globalUserLimit;
    user_variable *globalUserVariable;
public://Johnson 190617
    _FILE_SAVE_LOAD_VARIABLE_ gSpanModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ gChnlPowerModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ gOccupiedModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ gACPModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ gMultiACPModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ gSpectrumEmissionMaskModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ gSpuriousEmissionMaskModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ gFieldStrengthModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ gDemodulationModeParam;

    _ALLMODE_FILE_SAVE_LOAD_ gAllMode_FileSaveLoadParam;
    _START_STATUS_FLAG_ StartStatusFlag;

    bool bSpanModeParamNull,bChnlPowerModeParamNull,bOccupiedModeParamNull,bACPModeParamNull,bMultiACPModeParamNull,
         bSpectrumEmissionMaskModeParamNull,bSpuriousEmissionMaskModeParamNull,bFieldStrengthModeParamNull,bDemodulationModeParamNull;
public://Johnson 0701
    _CONFIG_STATE_ gSpanModeState;
    _CONFIG_STATE_ gChnlPowerModeState;
    _CONFIG_STATE_ gOccupiedModeState;
    _CONFIG_STATE_ gACPModeState;
    _CONFIG_STATE_ gMultiACPModeState;
    _CONFIG_STATE_ gSpectrumEmissionMaskModeState;
    _CONFIG_STATE_ gSpuriousEmissionMaskModeState;
    _CONFIG_STATE_ gFieldStrengthModeState;
    _CONFIG_STATE_ gDemodulationModeState;
    _ALLMODE_STATE_ gAllMode_State;

    _CONFIG_STATE_MSDATA_ gSpanModeState_MsData;
    _CONFIG_STATE_MSDATA_ gChnlPowerModeState_MsData;
    _CONFIG_STATE_MSDATA_ gOccupiedModeState_MsData;
    _CONFIG_STATE_MSDATA_ gACPModeState_MsData;
    _CONFIG_STATE_MSDATA_ gMultiACPModeState_MsData;
    _CONFIG_STATE_MSDATA_ gSpectrumEmissionMaskModeState_MsData;
    _CONFIG_STATE_MSDATA_ gSpuriousEmissionMaskModeState_MsData;
    _CONFIG_STATE_MSDATA_ gFieldStrengthModeState_MsData;
    _CONFIG_STATE_MSDATA_ gDemodulationModeState_MsData;
    _ALL_STATE_MSDATA_ gAllModeState_MsData;
public://Johnson 0802
    bool setVariable(_FILE_SAVE_LOAD_VARIABLE_ *pVariable,uint workMode = SA_SPAN_MODE);
    bool loadVariable(_FILE_SAVE_LOAD_VARIABLE_ *pVariable,uint workMode = SA_SPAN_MODE);
    bool saveVariable(_FILE_SAVE_LOAD_VARIABLE_ *pVariable,uint workMode = SA_SPAN_MODE);
    void fileSaveLoadParaToglobalUserVariable(_FILE_SAVE_LOAD_VARIABLE_ *pVariable);
    void globalUserVariableTofileSaveLoadPara(_FILE_SAVE_LOAD_VARIABLE_ *pVariable);

    void measureStateTofileSaveLoadPara(_CONFIG_STATE_ *pVariable);
    void fileSaveLoadParaTomeasureState(_CONFIG_STATE_ *pVariable);

    void fileSaveLoadParaToStataAndData(_CONFIG_STATE_MSDATA_ *pVariable);
    void StataAndDataTofileSaveLoadPara(_CONFIG_STATE_MSDATA_ *pVariable);

    void paraInit_AllMode();
    void paraInit_MeasureMode();
    void paraSave(quint32 currentMode);
    void paraLoad(quint32 currentMode);
    bool getParaStatus(quint32 currentMode);

    bool allModeParaSave(quint32 currentMode,qint32 itype);
    bool allModeParaLoad(qint32 presetFlag = 0, qint32 itype = 0);
    bool preStateSave(qint32 itype = -1);

    bool paraInit_StateFile();
    bool saveStatefile(QString FilePath);
    bool loadStatefile(QString FilePath);

    bool paraInit_StateAndDataFile();
    bool saveStateAndDataFile(QString FilePath);
    bool loadStateAndDataFile(QString FilePath);
};

#endif // SA_PARASAVELOAD_H
